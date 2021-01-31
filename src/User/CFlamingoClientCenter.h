#ifndef __CFLAMINGOCLIENTCENTER__
#define __CFLAMINGOCLIENTCENTER__


#include <utils/CSingletonT.h>
#include <ProtocolData/rpc_structs.h>
#include <memory>
#include <condition_variable>
#include <map>
#include <unordered_map>
#include "userdatas.h"
#include <QObject>
#include <Callbacks.h>

namespace net
{
    class TcpClient;
    class InetAddress;
    class EventLoop;
}

typedef std::function<void(const std::string&)>    RequestCallBack;
typedef std::function<void(const FileTransferStatus& status, const QString& msgInfo, const QString& fileName, const int& person)>    SendFileCallBack;

class USER_EXPORT CFlamingoClientCenter : public QObject, public utils::CSingletonT<CFlamingoClientCenter>
{
    Q_OBJECT
public:
    CFlamingoClientCenter();
    ~CFlamingoClientCenter();

    void resetClient();
    void resetAddress();
    void init(net::EventLoop* loopObj);
    void setRequestCallBack(RequestCallBack func);
   
    void login_async(const net::CLoginRequest &req);
    void connect_async(int nType);
    void regist_async(const net::CRegisterRequest &req);

    void sendFileToServer(const QString& strFileName, SendFileCallBack cb);
    void disconnectToFileServer();

    bool request_async(const net::IDataPtr& req, RequestCallBack _func = RequestCallBack());
    void registCallBack(int id, RequestCallBack cb);

Q_SIGNALS:
    void sigLogindStatus(UserLoginStatus, QString);
    void sigFileStatus(int, QString);
    void sigStatus(int, QString);
    void sigChatMessageComming(const net::CBuddyMessagePtr&);

private:
    CFlamingoClientCenter(const CFlamingoClientCenter&) = delete;
    CFlamingoClientCenter& operator=(const CFlamingoClientCenter&) = delete;

    void onHandleLogin(const std::string &data);
    void onHandleUserInfo(const std::string &data);
    void onRegist(const std::string &resp);

    void onRequest(const std::string &resp);


    bool dispatchHandle(const net::TcpConnectionPtr& conn, const char* inbuf, size_t buflength);
    void onConnect(const net::TcpConnectionPtr& pData);
    void onPackageDecode(const net::TcpConnectionPtr&, net::Buffer*, Timestamp);
    void onErrorCB(const std::string &msg);

    void onConnectFile(const net::TcpConnectionPtr& pData);
    void onPackageDecodeFile(const net::TcpConnectionPtr&, net::Buffer*, Timestamp);
    bool processFileDatas(const char* inbuf, size_t buflength, net::FileSendResult& errorCode);
    void onErrorCBFile(const std::string &msg);


    std::map<int, net::TcpClient*>     m_pClients;     //没用智能指针需要析构的地方手动delete目前没有给delete
    std::map<std::string, std::pair<std::string, int>>           m_mapKey2FileName; 
    net::InetAddress*                         m_pAddress = NULL;
    net::EventLoop*                           m_loopObj;

    //std::mutex						          m_mtRegist;
    //std::mutex						          m_mtLogin;
    //std::condition_variable			          m_cvRegist;
    //std::condition_variable			          m_cvLogin;

    net::CRegisterResult *                    m_pRegistPtr = NULL;
    net::CLoginResult *                       m_pLoginRespPtr = NULL;
    RequestCallBack                           _requestfunc;       //这个基本上用不到了

    std::map<int, RequestCallBack>            m_mapId2CB;
    std::map<int, string>                     m_mapCacheNotify;   //缓存通知的回调 防止界面没刷新数据就回来了
    static int32_t                            m_seq;

    std::list<string>                         m_strSendFiles;
   // unsigned                                  m_offReadFile = 0;
    const unsigned                            m_sendMaxFileSize = 5 * 1024;

    string                                    m_loginParam;
    bool                                      m_bLoginEnable = true;

    SendFileCallBack                          m_sendFileCB;
    QString                                   m_strFileName;
};
#endif