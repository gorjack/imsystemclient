#include "CUserClientCenter.h"
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
#include "CUserManager.h"
#include <utils/FileHelper.h>
#include <ProtocolData/rpc_Enum.h>
#include <utils/File2.h>
#include <EventLoop.h>
#include <memory>

#if 1
//包最大字节数限制为10M
#define MAX_PACKAGE_SIZE    10 * 1024 * 1024
IMPL_SINGLETON_CLASS(CUserClientCenter);



int32_t CUserClientCenter::m_seq = 0;
CUserClientCenter::CUserClientCenter()
{
}

CUserClientCenter::~CUserClientCenter()
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

void CUserClientCenter::resetClient()
{
    std::map<SERVERTYPE, QString>& servers = CConfig::instance()->getServers();
    std::map<SERVERTYPE, QString>::const_iterator iter = servers.begin();
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
            pClient->setConnectionCallback(std::bind(&CUserClientCenter::onConnect, this, std::placeholders::_1));
            pClient->setMessageCallback(std::bind(&CUserClientCenter::onPackageDecode, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            pClient->setErrorMegCallBack(std::bind(&CUserClientCenter::onErrorCB, this, std::placeholders::_1));
        }
            break;
        case FILE_SERVER:
        {
            pClient->setConnectionCallback(std::bind(&CUserClientCenter::onConnectFile, this, std::placeholders::_1));
            pClient->setMessageCallback(std::bind(&CUserClientCenter::onPackageDecodeFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            pClient->setErrorMegCallBack(std::bind(&CUserClientCenter::onErrorCBFile, this, std::placeholders::_1));
        }
        break;
        }
        m_pClients[iter->first] = pClient;
    }
}

void CUserClientCenter::resetAddress()
{
    std::map<SERVERTYPE, QString>& servers = CConfig::instance()->getServers();
    std::map<SERVERTYPE, QString>::const_iterator iter = servers.begin();
    for (; iter != servers.end(); ++iter)
    {
        std::string ip;
        unsigned short port;
        utils::getIpPort(iter->second.toStdString(), ip, port);
        SERVERTYPE typeS = iter->first;

        auto iterT = m_pClients.find(iter->first);
        if (iterT != m_pClients.end())
        {
            net::TcpClient *pclient = iterT->second;
            if (NULL != pclient->connection() && pclient->connection()->connected()
                && (iter->second.toStdString() != pclient->getAddress()))
            {
                pclient->connection()->forceClose();
            }

            iterT->second->setAddress(ip, port);
        }
    }

    //connect_async(CHAT_SERVER);  这里感觉不用连吧
    m_bLoginEnable = false;
}

void CUserClientCenter::init(net::EventLoop* loopObj)
{
    m_loopObj = loopObj;
}

void CUserClientCenter::setRequestCallBack(RequestCallBack func)
{
    _requestfunc = func;
}

void CUserClientCenter::regist_async(const net::CRegisterRequest &req)
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

bool CUserClientCenter::request_async(const net::IDataPtr& req, RequestCallBack _func /*= RequestCallBack()*/)
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
        //LOGI(pConn->key().c_str());
        pConn->send(reqData);
        return true;
    }
    else
    {
        LOGI("connect faild, please connect again");
        return false;
    }
}

void CUserClientCenter::onRegist(const std::string &resp)
{
    //std::unique_lock<std::mutex> lockGuard(m_mtRegist);
    m_pRegistPtr = (new net::CRegisterResult());
    m_pRegistPtr->decodePackage(resp);
    emit sigStatus(m_pRegistPtr->m_nResultCode, "");
    //m_cvRegist.notify_one();
}


void CUserClientCenter::onRequest(const std::string &resp)
{
    _requestfunc(resp);
}

void CUserClientCenter::registCallBack(int id, RequestCallBack cb)
{
    auto iter = m_mapCacheNotify.find(id);
    if (iter != m_mapCacheNotify.end())
    {
        cb(iter->second);
        m_mapCacheNotify.erase(iter);
    }
    m_mapId2CB[id] = cb;
}

void CUserClientCenter::login_async(const net::CLoginRequest &req)
{
    m_bLoginEnable = true;
    net::TcpClient *pClient = m_pClients[CHAT_SERVER];
    if (pClient == NULL)
    {
        return;
    }

    req.encodePackage(m_loginParam);
    if (!m_pClients[CHAT_SERVER]->isConnected())
    {
        m_pClients[CHAT_SERVER]->connect();
        emit sigLogindStatus(STATUS_CONNECTING, "");
        return;
    }

    net::TcpConnectionPtr pConn = m_pClients[CHAT_SERVER]->connection();
    if (NULL != pConn)
    {
        pConn->send(m_loginParam);
        emit sigLogindStatus(STATUS_LOGINING, "");
    }

    return;
}

void CUserClientCenter::connect_async(int nType)
{
    if (NULL != m_pClients[nType] && !m_pClients[nType]->isConnected())
    {
        m_pClients[nType]->connect();
        emit sigLogindStatus(STATUS_CONNECTING, "");
        return;
    }
}

void CUserClientCenter::onHandleLogin(const std::string &data)
{
    m_pLoginRespPtr = (new net::CLoginResult());
    m_pLoginRespPtr->decodePackage(data);

    CUserManager::instance()->setUserId(m_pLoginRespPtr->m_uAccountID);
    long nLoginResultCode = m_pLoginRespPtr->m_LoginResultCode;
    switch (nLoginResultCode)
    {
    case protocol::LOGIN_UNREGISTERED:
        emit sigLogindStatus(STATUS_ERROR, QString::fromLocal8Bit("用户未注册"));
        break;
    case protocol::LOGIN_PASSWORD_ERROR:
        emit sigLogindStatus(STATUS_ERROR, QString::fromLocal8Bit("用户名密码错误"));
        break;
    case protocol::LOGIN_SUCCESS:
    {
        CConfig::instance()->setNickName(m_pLoginRespPtr->m_szNickName);
        net::CUserBasicInfoRequestPtr pData(new net::CUserBasicInfoRequest);
        request_async(pData, std::bind(&CUserClientCenter::onHandleUserInfo, this, std::placeholders::_1));
        QString s = QString::fromLocal8Bit("获取联系人列表");
        emit sigLogindStatus(STATUS_GET_USER_LIST, s);
    }
    break;
    }
}

void CUserClientCenter::onHandleUserInfo(const std::string &data)
{
    CUserManager::instance()->onGetFirendListCallBack(data);
    emit sigLogindStatus(STATUS_LOGIN_FINISHED, "");

}

bool CUserClientCenter::dispatchHandle(const net::TcpConnectionPtr& conn, const char* inbuf, size_t buflength)
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

    LOGI("recv data from server cmd = %d, data : %s", cmd, data.c_str());
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
        case msg_type_chat:
        {
            net::CBuddyMessagePtr pData( new net::CBuddyMessage);
            if (pData->decodePackage(data))
            {
                emit sigChatMessageComming(pData);
            }
            break;
        }
        default:
        {
            if (m_mapId2CB[cmd] != NULL)
            {
                (m_mapId2CB[cmd])(data);
            }
            else
            {
                m_mapCacheNotify[cmd] = data;
                LOGI("cmd = %d not to handle", cmd);
            }
        }
    }

    return true;
}

void CUserClientCenter::onConnect(const net::TcpConnectionPtr& pData)
{
    if (pData->connected())
    {
        if (m_bLoginEnable && !m_loginParam.empty())
        {
            pData->send(m_loginParam);
            emit sigLogindStatus(STATUS_LOGINING, "");
        }
        else
        {
            emit sigLogindStatus(STATUS_CONNECTED, "");
        }
    }
}

void CUserClientCenter::onPackageDecode(const net::TcpConnectionPtr& conn, net::Buffer* pBuffer, Timestamp time)
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

void CUserClientCenter::sendFileToServer(const QString& strFileName, SendFileCallBack cb)
{
    m_strFileName = strFileName;
    m_sendFileCB = cb;

    if (NULL != m_pClients[FILE_SERVER] && !m_pClients[FILE_SERVER]->isConnected())
    {
        m_pClients[FILE_SERVER]->connect();
        cb(FILE_STATUS_CONNECTED, "", m_strFileName, 0);
    }
    else {
        //gaojie: 这里我打算处理暂停继续发文件逻辑， 也就是断点续传。
    }

}

void CUserClientCenter::disconnectToFileServer()
{
    if (NULL != m_pClients[FILE_SERVER] && m_pClients[FILE_SERVER]->isConnected())
    {
        m_pClients[FILE_SERVER]->disconnectFull();
    }
}

void CUserClientCenter::onErrorCB(const std::string &msg)
{
    emit sigLogindStatus(STATUS_ERROR, utils::sToQs(msg));
}

void CUserClientCenter::onConnectFile(const net::TcpConnectionPtr& pData)
{
    if (pData->connected())
    {
        //链接失败报告给用户 目前只有链接成功会回来，失败的处理都写在日志里了。
        stringstream sstr;
        sstr << pData->key();

        net::TcpConnection* pc = pData.get();
        sstr << "connecter addr: " << to_string(reinterpret_cast<int>(pc));
        LOGI(sstr.str().c_str());

        using namespace protocol;
        using namespace utils;
        //文件md5值
        int64_t nFileSize = 0;
        char szMd5[64] = { 0 };
        //const wchar_t* pszFileName = strFileName.toStdWString().c_str();   //直接这么写就不行 得像下面那样拆开才可以
        std::wstring ss = m_strFileName.toStdWString();
        const wchar_t* ssw = ss.c_str();
        //long nRetCode = utils::GetFileMd5ValueA(ssw, szMd5, ARRAYSIZE(szMd5), nFileSize);
        //if (nRetCode == utils::GET_FILE_MD5_FAILED)
        //{
        //    m_sendFileCB(FILE_STATUS_ERROR, QString("Failed to upload file:%1 as unable to get file md5.").arg(m_strFileName), m_strFileName, 0);
        //}
        //else if (nRetCode == GET_FILE_MD5_USERCANCEL)
        //{
        //    //gaojie: 用户取消传输该走怎样的逻辑
        //}
        //if (nFileSize == 0)
        //{
        //    m_sendFileCB(FILE_STATUS_ERROR, QString("Failed to upload file:%s as file size is 0.").arg(m_strFileName), m_strFileName, 0);
        //}

        string content;
        unsigned eachSize = nFileSize > m_sendMaxFileSize ? m_sendMaxFileSize : nFileSize;
        if (!utils::FileHelper::open(utils::qsToS(m_strFileName), content, 0, eachSize))
        {
            m_sendFileCB(FILE_STATUS_ERROR, QString("read file %s error").arg(m_strFileName), m_strFileName, 0);
        }

        net::CUpLoadFileRequestPtr pData(new net::CUpLoadFileRequest);
        pData->m_offsetX = 0;
        pData->m_nFileSize = nFileSize;
        pData->m_strContent = content;
        pData->m_strMd5.append(szMd5, 32);

        m_mapKey2FileName[std::string(szMd5)] = std::make_pair(qsToS(m_strFileName), eachSize);

        LOG_INFO("will send to server filesize=%d, filemd5=%s", nFileSize, szMd5);

        request_async(pData);

        return;
    }
}

void CUserClientCenter::onPackageDecodeFile(const net::TcpConnectionPtr& conn, net::Buffer* pBuffer, Timestamp time)
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
        memcpy(&header, pBuffer->peek(), sizeof(header));
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
                int totalSize = res.fileSize;
                QString centontStr = QString::number(totalSize / 1024) + QString("k");

                //emit sigFileStatus(FILE_STATUS_SUCCESS, "");
                m_sendFileCB(FILE_STATUS_TRANSFERING, centontStr, m_strFileName, 100);
            }
            else
            {
                auto iter = m_mapKey2FileName.find(res.fileMd5);
                if (iter == m_mapKey2FileName.end())
                {
                    m_sendFileCB(FILE_STATUS_ERROR, "", QString("read file md5 error"), 0);
                    return;
                }
                std::string strFileName = iter->second.first;
                int nReadSize = iter->second.second;
                int totalSize = res.fileSize;

                int nPercent = ((long)((__int64)nReadSize * 100 / totalSize));

                QString centontStr = QString::number(nReadSize / 1024) + QString("k");
                m_sendFileCB(FILE_STATUS_TRANSFERING, centontStr, QString::fromStdString(strFileName), nPercent);

                string content;
                unsigned nSize = (totalSize - nReadSize) > m_sendMaxFileSize ? m_sendMaxFileSize : (totalSize - nReadSize);
                if (!utils::FileHelper::open(strFileName, content, nReadSize, nSize))
                {
                    m_sendFileCB(FILE_STATUS_ERROR, QString("read file %s error").arg(QString::fromStdString(strFileName)), QString::fromStdString(strFileName), 0);
                    //emit sigFileStatus(FILE_STATUS_ERROR, "读取文件失败");
                }

                net::CUpLoadFileRequestPtr pData(new net::CUpLoadFileRequest);
                pData->m_offsetX = nReadSize;
                pData->m_nFileSize = res.fileSize;
                pData->m_strContent = content;
                pData->m_strMd5 = res.fileMd5;

                auto &valueData = m_mapKey2FileName[std::string(res.fileMd5)];
                valueData.second += nSize;

                request_async(pData);
            }
        }
    }
}

bool CUserClientCenter::processFileDatas(const char* inbuf, size_t buflength, net::FileSendResult& errorCode)
{
    return net::CUpLoadFileRequest::decodePackage(inbuf, buflength, errorCode);
}

void CUserClientCenter::onErrorCBFile(const std::string &msg)
{
    //这里处理的是网络错误消息 
    emit sigFileStatus(FILE_STATUS_ERROR, utils::sToQs(msg));
}

#endif
