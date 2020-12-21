#include "CFlamingoClientCenter.h"
#include <Env/CConfig.h>
#include <TcpClient.h>
#include <Callbacks.h>
#include <Msg.h>
#include <winlog/IULog.h>
#include <winlog/AsyncLog.h>
#include <utils/ZlibUtil.h>
#include <ProtocolStream.h>
#include <utils/CSingletonT.hpp>
#include <winlog/AsyncLog.h>
#include <utils/strings.h>
#include <utils/commonFunc.h>
#include <user/CUserManager.h>
#include <utils/FileHelper.h>
#include <ProtocolData/rpc_Enum.h>
#include <utils/File2.h>
#include <EventLoop.h>


#if 1
//包最大字节数限制为10M
#define MAX_PACKAGE_SIZE    10 * 1024 * 1024
IMPL_SINGLETON_CLASS(CFlamingoClientCenter);



int32_t CFlamingoClientCenter::m_seq = 0;
CFlamingoClientCenter::CFlamingoClientCenter()
    :m_readMaxFileSize(5*1024)
{
    int p = m_seq;
}

CFlamingoClientCenter::~CFlamingoClientCenter()
{
    if (NULL != m_pAddress)
    {
        delete m_pAddress;
        m_pAddress = NULL;
    }
    if (NULL != m_pRegistPtr)
    {
        delete m_pRegistPtr;
        m_pRegistPtr = NULL;
    }

    if (NULL != m_pLoginRespPtr)
    {
        delete m_pLoginRespPtr;
        m_pLoginRespPtr = NULL;
    }
}

void CFlamingoClientCenter::resetClient()
{
    std::map<SERVERTYPE, QString>& servers = CConfig::instance()->getServers();
    std::map<SERVERTYPE, QString>::const_iterator iter = servers.find(CHAT_SERVER);
    for (; iter != servers.end(); ++iter)
    {
        std::string ip;
        unsigned short port;
        utils::getIpPort(iter->second.toStdString(), ip, port);
        net::InetAddress* pAddress = new net::InetAddress(ip, port);
        net::TcpClient* pClient = new net::TcpClient(m_loopObj, *pAddress, "");
        switch (iter->first)
        {
        case CHAT_SERVER:
        {
            pClient->setConnectionCallback(std::bind(&CFlamingoClientCenter::onConnect, this, std::placeholders::_1));
            pClient->setMessageCallback(std::bind(&CFlamingoClientCenter::onPackageDecode, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            pClient->setErrorMegCallBack(std::bind(&CFlamingoClientCenter::onErrorCB, this, std::placeholders::_1));
        }
            break;
        case FILE_SERVER:
        {
            pClient->setConnectionCallback(std::bind(&CFlamingoClientCenter::onConnectFile, this, std::placeholders::_1));
            pClient->setMessageCallback(std::bind(&CFlamingoClientCenter::onPackageDecodeFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            pClient->setErrorMegCallBack(std::bind(&CFlamingoClientCenter::onErrorCBFile, this, std::placeholders::_1));
        }
        break;
        }
        m_pClients[iter->first] = pClient;
    }
}

void CFlamingoClientCenter::init(net::EventLoop* loopObj)
{
    m_loopObj = loopObj;
}

void CFlamingoClientCenter::setRequestCallBack(RequestCallBack func)
{
    _requestfunc = func;
}

void CFlamingoClientCenter::regist_async(const net::CRegisterRequest &req)
{
    net::TcpClient *pClient = m_pClients[CHAT_SERVER];
    if (pClient == NULL)
    {
        return;
    }

    if (!m_pClients[CHAT_SERVER]->isConnected())
    {
        // socket 还没连接上
        return;
    }

    std::string registReq;
    req.encodePackage(registReq);
    net::TcpConnectionPtr pConn = m_pClients[CHAT_SERVER]->connection();
    if (NULL != pConn)
    {
        pConn->send(registReq);
    }

    //{
    //    std::unique_lock<std::mutex> lockGuard(m_mtRegist);
    //    while (NULL == m_pRegistPtr)
    //    {
    //        m_cvRegist.wait(lockGuard);
    //    }

    //    return m_pRegistPtr;
    //}
}

bool CFlamingoClientCenter::request_async(const net::IDataPtr& req, RequestCallBack _func /*= RequestCallBack()*/)
{
    net::TcpClient *pClient = m_pClients[req->m_nType];
    if (pClient == NULL)
    {
        return false;
    }

    std::string reqData;
    req->encodePackage(reqData, m_seq++);
    _requestfunc = _func;

    net::TcpConnectionPtr pConn = m_pClients[req->m_nType]->connection();
    if (NULL != pConn)
    {
        pConn->send(reqData);
        //_requestfunc = _func;
        return true;
    }
    else
    {
        LOGI("connect faild, please connect again");
        return false;
    }
}

void CFlamingoClientCenter::onRegist(const std::string &resp)
{
    //std::unique_lock<std::mutex> lockGuard(m_mtRegist);
    m_pRegistPtr = (new net::CRegisterResult());
    m_pRegistPtr->decodePackage(resp);
    emit sigStatus(m_pRegistPtr->m_nResultCode, "");
    //m_cvRegist.notify_one();
}


void CFlamingoClientCenter::onRequest(const std::string &resp)
{
    _requestfunc(resp);
}

void CFlamingoClientCenter::registCallBack(int id, RequestCallBack cb)
{
    m_mapId2CB[id] = cb;
}

void CFlamingoClientCenter::login_async(const net::CLoginRequest &req)
{
    net::TcpClient *pClient = m_pClients[CHAT_SERVER];
    if (pClient == NULL)
    {
        return;
    }

    if (!m_pClients[CHAT_SERVER]->isConnected())
    {
        m_pClients[CHAT_SERVER]->connect();
        emit sigLogindStatus(STATUS_CONNECTING, "");
        return;
    }


    std::string loginReq;
    req.encodePackage(loginReq);

    net::TcpConnectionPtr pConn = m_pClients[CHAT_SERVER]->connection();
    if (NULL != pConn)
    {
        pConn->send(loginReq);
        emit sigLogindStatus(STATUS_LOGINING, "");
    }

    return;
}

void CFlamingoClientCenter::connect_async(int nType)
{
    if (NULL != m_pClients[nType] && !m_pClients[nType]->isConnected())
    {
        m_pClients[nType]->connect();
        emit sigLogindStatus(STATUS_CONNECTING, "");
        return;
    }
}

void CFlamingoClientCenter::onHandleLogin(const std::string &data)
{
    m_pLoginRespPtr = (new net::CLoginResult());
    m_pLoginRespPtr->decodePackage(data);

    long nLoginResultCode = m_pLoginRespPtr->m_LoginResultCode;
    switch (nLoginResultCode)
    {
    case protocol::LOGIN_UNREGISTERED:
        emit sigLogindStatus(STATUS_ERROR, "用户未注册");
        break;
    case protocol::LOGIN_PASSWORD_ERROR:
        emit sigLogindStatus(STATUS_ERROR, "用户名密码错误");
        break;
    case protocol::LOGIN_SUCCESS:
    {
        net::CUserBasicInfoRequestPtr pData(new net::CUserBasicInfoRequest);
        request_async(pData, std::bind(&CFlamingoClientCenter::onHandleUserInfo, this, std::placeholders::_1));
        QString s = QString::fromLocal8Bit("获取联系人列表");
        emit sigLogindStatus(STATUS_GET_USER_LIST, s);
    }
    break;
    }
}

void CFlamingoClientCenter::onHandleUserInfo(const std::string &data)
{
    CUserManager::instance()->onGetFirendListCallBack(data);
    emit sigLogindStatus(STATUS_LOGIN_FINISHED, "");

}

bool CFlamingoClientCenter::dispatchHandle(const net::TcpConnectionPtr& conn, const char* inbuf, size_t buflength)
{
    net::BinaryStreamReader readStream(inbuf, buflength);
    int32_t cmd;
    if (!readStream.ReadInt32(cmd))
    {
        LOGE("read cmd error, client: %s", conn->peerAddress().toIpPort().c_str());
        return false;
    }

    int seq;
    if (!readStream.ReadInt32(seq))
    {
        LOGE("read seq error, client: %s", conn->peerAddress().toIpPort().c_str());
        return false;
    }

    std::string data;
    size_t datalength;
    if (!readStream.ReadString(&data, 0, datalength))
    {
        LOGE("read data error, client: %s", conn->peerAddress().toIpPort().c_str());
        return false;
    }

    switch (cmd)
    {
        case msg_type_login:
            onHandleLogin(data);
            break;
        case msg_type_register:
            onRegist(data);
            break;
        case msg_type_getofriendlist:
            onHandleUserInfo(data);
            break;
        //case msg_type_finduser:
        //case msg_type_getofriendlist:
        //case msg_type_operatefriend:                        //加好友申请或删除好友或加群或退群
        //{
        //    if (m_mapId2CB[cmd] != NULL)
        //    {
        //        (m_mapId2CB[cmd])(data);
        //    }
        //}
        //    //onRequest(data);
        //    break;

         //   break;
        default:
        {
            if (m_mapId2CB[cmd] != NULL)
            {
                (m_mapId2CB[cmd])(data);
            }
        }
    }

    return true;
}

void CFlamingoClientCenter::onConnect(const net::TcpConnectionPtr& pData)
{
    if (pData->connected())
    {
        //链接失败报告给用户 目前只有链接成功会回来，失败的处理都写在日志里了。
        emit sigLogindStatus(STATUS_CONNECTED, "");
    }
}

void CFlamingoClientCenter::onPackageDecode(const net::TcpConnectionPtr& conn, net::Buffer* pBuffer, Timestamp time)
{
    while (true)
    {
        //不够一个包头大小
        if (pBuffer->readableBytes() < (size_t)sizeof(msg))
        {
            //LOGI("buffer is not enough for a package header, pBuffer->readableBytes()=%d, sizeof(msg)=%d", pBuffer->readableBytes(), sizeof(msg));
            return;
        }

        //取包头信息
        msg header;
        memcpy(&header, pBuffer->peek(), sizeof(msg));
        if (header.compressflag == PACKAGE_COMPRESSED)
        {
            //包头有错误，立即关闭连接
            if (header.compresssize <= 0 || header.compresssize > MAX_PACKAGE_SIZE ||
                header.originsize <= 0 || header.originsize > MAX_PACKAGE_SIZE)
            {
                //客户端发非法数据包，服务器主动关闭之
                LOG_INFO("Illegal package, compresssize: %lld, originsize: %lld, close TcpConnection, client: %s", header.compresssize, header.originsize, conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            //收到的数据不够一个完整的包
            if (pBuffer->readableBytes() < (size_t)header.compresssize + sizeof(msg))
                return;

            pBuffer->retrieve(sizeof(msg));
            std::string inbuf;
            inbuf.append(pBuffer->peek(), header.compresssize);
            pBuffer->retrieve(header.compresssize);
            std::string destbuf;
            if (!ZlibUtil::UncompressBuf(inbuf, destbuf, header.originsize))
            {
                LOG_ERROR("uncompress error, client: %s", conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            if (!dispatchHandle(conn, destbuf.c_str(), destbuf.length()))
            {
                //客户端发非法数据包，服务器主动关闭之
                LOGE("Process error, close TcpConnection, client: %s", conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

        }
        else
        {
            //包头有错误，立即关闭连接
            if (header.originsize <= 0 || header.originsize > MAX_PACKAGE_SIZE)
            {
                //客户端发非法数据包，服务器主动关闭之
                LOG_ERROR("Illegal package, compresssize: %lld, originsize: %lld, close TcpConnection, client: %s", header.compresssize, header.originsize, conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            //收到的数据不够一个完整的包
            if (pBuffer->readableBytes() < (size_t)header.originsize + sizeof(msg))
                return;

            pBuffer->retrieve(sizeof(msg));
            std::string inbuf;
            inbuf.append(pBuffer->peek(), header.originsize);
            pBuffer->retrieve(header.originsize);

            if (!dispatchHandle(conn, inbuf.c_str(), inbuf.length()))
            {
                //客户端发非法数据包，服务器主动关闭之
                LOGE("Process error, close TcpConnection, client: %s", conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

        }// end else

    }// end while-loop
}

const QString CFlamingoClientCenter::sendFileToServer(const QString& strFileName)
{
    if (NULL != m_pClients[FILE_SERVER] && !m_pClients[FILE_SERVER]->isConnected())
    {
        m_pClients[FILE_SERVER]->connect();
        //在连接的地方发送
    }

    using namespace protocol;
    using namespace utils;
    //文件md5值
    int64_t nFileSize;
    char szMd5[64] = { 0 };
    //const wchar_t* pszFileName = strFileName.toStdWString().c_str();   //直接这么写就不行 得像下面那样拆开才可以
    std::wstring ss = strFileName.toStdWString();
    const wchar_t* ssw = ss.c_str();
    long nRetCode = utils::GetFileMd5ValueA(ssw, szMd5, ARRAYSIZE(szMd5), nFileSize);
    if (nRetCode == utils::GET_FILE_MD5_FAILED)
    {
        return QString("Failed to upload file:%1 as unable to get file md5.").arg(strFileName);
    }
    else if (nRetCode == GET_FILE_MD5_USERCANCEL)
    {
        return QString("User cancel to upload file:%s.").arg(strFileName);
    }
    if (nFileSize == 0)
    {
        return QString("Failed to upload file:%s as file size is 0.").arg(strFileName);
    }


    //nFileSize 就是全部尺寸 这里可以判断一下 nFileSize跟m_nTotolFileSize 谁大谁小
    string content;
    m_nTotolFileSize = utils::FileHelper::getFileSize(utils::qsToS(strFileName));
    unsigned eachSize = m_nTotolFileSize > m_readMaxFileSize ? m_readMaxFileSize : m_nTotolFileSize;
    if (!utils::FileHelper::open(utils::qsToS(strFileName), content, 0, eachSize))
    {
        return QString("读取文件 %s 失败").arg(strFileName);
        //emit sigLogindStatus(FILE_STATUS_ERROR, "读取文件失败");
    }

    net::CUpLoadFileRequestPtr pData(new net::CUpLoadFileRequest);
    pData->m_offsetX = 0;
    pData->m_nFileSize = m_nTotolFileSize;
    pData->m_strContent = content;
    pData->m_strMd5.append(szMd5, 32);

    m_mapKey2FileName[std::string(szMd5)] = std::make_pair(qsToS(strFileName), eachSize);
    request_async(pData);

    return QString("");
}

void CFlamingoClientCenter::onErrorCB(const std::string &msg)
{
    emit sigLogindStatus(STATUS_ERROR, utils::sToQs(msg));
}

void CFlamingoClientCenter::onConnectFile(const net::TcpConnectionPtr& pData)
{
    if (pData->connected())
    {
        //链接失败报告给用户 目前只有链接成功会回来，失败的处理都写在日志里了。
        emit sigLogindStatus(STATUS_CONNECTED, "");
    }
}

void CFlamingoClientCenter::onPackageDecodeFile(const net::TcpConnectionPtr& conn, net::Buffer* pBuffer, Timestamp time)
{
    protocol::file_msg header;
    while (true)
    {
        //不够一个包头大小
        if (pBuffer->readableBytes() < (size_t)sizeof(header))
        {
            //LOGI("buffer is not enough for a package header, pBuffer->readableBytes()=%d, sizeof(msg)=%d", pBuffer->readableBytes(), sizeof(msg));
            return;
        }

        //取包头信息
        //msg header;
        memcpy(&header, pBuffer->peek(), sizeof(msg));
        {
            //收到的数据不够一个完整的包
            if (pBuffer->readableBytes() < (size_t)header.packagesize + sizeof(header))
                return;

            pBuffer->retrieve(sizeof(header));
            std::string inbuf;
            inbuf.append(pBuffer->peek(), header.packagesize);
            pBuffer->retrieve(header.packagesize);

            net::FileSendResult res;
            if (!processFileDatas( inbuf.c_str(), inbuf.length(), res))
            {
                //客户端发非法数据包，服务器主动关闭之
                LOGE("Process error, close TcpConnection, client: %s", conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            if (res.errorCode == protocol::file_msg_error_complete)
            {
                emit sigLogindStatus(FILE_STATUS_SUCCESS, "");
            }
            else
            {
                auto iter = m_mapKey2FileName.find(res.fileMd5);
                std::string strFileName = iter->second.first;
                int nReadSize = iter->second.second;
                int totalSize = res.fileSize;

                string content;
                unsigned nSize = (totalSize - nReadSize) > m_readMaxFileSize ? m_readMaxFileSize : (totalSize - nReadSize);
                if (!utils::FileHelper::open(res.fileName, content, nReadSize, nSize))
                {
                    emit sigLogindStatus(FILE_STATUS_ERROR, "读取文件失败");
                }

                net::CUpLoadFileRequestPtr pData(new net::CUpLoadFileRequest);
                pData->m_offsetX = nReadSize;
                pData->m_nFileSize = res.fileSize;
                pData->m_strContent = content;
                pData->m_strMd5.append(res.fileMd5, 32);

                auto &valueData = m_mapKey2FileName[std::string(res.fileMd5)];
                valueData.second = nReadSize + nSize;

                request_async(pData);
            }
        }
    }
}

bool CFlamingoClientCenter::processFileDatas(const char* inbuf, size_t buflength, net::FileSendResult& errorCode)
{
    return net::CUpLoadFileRequest::decodePackage(inbuf, buflength, errorCode);
}

void CFlamingoClientCenter::onErrorCBFile(const std::string &msg)
{
    emit sigLogindStatus(FILE_STATUS_ERROR, utils::sToQs(msg));
}

#endif
