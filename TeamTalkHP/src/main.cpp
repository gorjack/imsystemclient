#include "EventLoop.h"

#include <QtWidgets/QApplication>
#include <condition_variable>
#include <mutex>
#include <winlog/AsyncLog.h>
#include <winlog/IULog.h>
#include <QtCore/QDir>
#include <iostream>
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


Q_DECLARE_METATYPE(net::CBuddyMessagePtr);
Q_DECLARE_METATYPE(UserLoginStatus);
Q_DECLARE_METATYPE(FileTransferStatus);
Q_DECLARE_METATYPE(ImageTransferStatus);
Q_DECLARE_METATYPE(std::string);

int main(int argc, char *argv[])
{

    qRegisterMetaType<net::CBuddyMessagePtr>();
    qRegisterMetaType<UserLoginStatus>();
    qRegisterMetaType<FileTransferStatus>();
    qRegisterMetaType<ImageTransferStatus>();
    qRegisterMetaType<std::string>();

    QApplication a(argc, argv);


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
    CIULog::Init(true, true, "debug.log");

	UserLogin* w = new UserLogin;
	w->show();

    int nRet = a.exec();
    g_pEventLoop->quit();

    if (t.joinable())
    {
        t.join();
    }

    CConfig::instance()->save();
    CIULog::Uninit();
    return nRet;
}
