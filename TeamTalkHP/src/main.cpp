#include <QtWidgets/QApplication>
#include <EventLoop.h>
#include <condition_variable>
#include <mutex>
#include <winlog/AsyncLog.h>
#include <winlog/IULog.h>
#include <QtCore/QDir>
#include <iostream>
//#include <Env/appUtil.h>
//#include <User/userdatas.h>
//#include <Env/CConfig.h>
//#include <Env/directory.h>
//#include <UiResources/CUiResource.h>
//#include <PanelChatWindow/UserDataInfo.h>
#include "UserClientCenter/userdatas.h"
#include "ProtocolData/rpc_structs.h"
#include "utils/CConfig.h"
#include "UserClientCenter/CUserClientCenter.h"
#include "UserLogin.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

net::EventLoop *g_pEventLoop = NULL;
std::condition_variable g_cvForLoop;
std::mutex              g_mtForLoop;

void startEventLoop()
{
    {
        std::unique_lock<std::mutex>  guardLock(g_mtForLoop);
        g_pEventLoop = new net::EventLoop();
        g_cvForLoop.notify_one();
    }

    g_pEventLoop->loop();
}

void UnInitSocket()
{
    ::WSACleanup();
}

BOOL InitSocket()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int nErrorID = ::WSAStartup(wVersionRequested, &wsaData);
    if (nErrorID != 0)
        return FALSE;

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        UnInitSocket();
        return FALSE;
    }

    return TRUE;
}

Q_DECLARE_METATYPE(net::CBuddyMessagePtr);
Q_DECLARE_METATYPE(UserLoginStatus);
Q_DECLARE_METATYPE(FileTransferStatus);
Q_DECLARE_METATYPE(ImageTransferStatus);
Q_DECLARE_METATYPE(std::string);
//Q_DECLARE_METATYPE(UC::CUserDataInfoPtr);
//Q_DECLARE_METATYPE(const net::CBuddyMessagePtr&);

int main(int argc, char *argv[])
{
    qRegisterMetaType<net::CBuddyMessagePtr>();
    qRegisterMetaType<UserLoginStatus>();
    qRegisterMetaType<FileTransferStatus>();
    qRegisterMetaType<ImageTransferStatus>();
    qRegisterMetaType<std::string>();
   // qRegisterMetaType<UC::CUserDataInfoPtr>();


    QApplication a(argc, argv);


    if (!InitSocket())
        return 0;

    std::thread t(startEventLoop);

    {
        std::unique_lock<std::mutex>  guardLock(g_mtForLoop);
        while (NULL == g_pEventLoop)
        {
            g_cvForLoop.wait(guardLock);
        }
    }

    CConfig::instance()->loadData();

    CUserClientCenter::instance()->init(g_pEventLoop);

	UserLogin* w = new UserLogin;
	w->show();

    int nRet = a.exec();
    UnInitSocket();
    g_pEventLoop->quit();

    if (t.joinable())
    {
        t.join();
    }

    CConfig::instance()->save();
    return nRet;
}
