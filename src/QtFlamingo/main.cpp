#include <QtWidgets/QApplication>
#include <PanelLoginDialog/src/rotatewidget.h>
#include <EventLoop.h>
#include <condition_variable>
#include <mutex>
#include <user/CFlamingoClientCenter.h>
#include <winlog/AsyncLog.h>
#include <winlog/IULog.h>
#include <QtCore/QDir>
#include <iostream>
#include <Env/appUtil.h>
#include <User/userdatas.h>
#include <Env/CConfig.h>
#include <Env/directory.h>
#include <UiResources/CUiResource.h>


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

void initResources()
{
    QString qsThemeDir = QF::getCurrentResourceDir() + QDir::separator() + "status" + QDir::separator();
    XP::CUiResource::instance()->parseImage(qsThemeDir);
}

Q_DECLARE_METATYPE(net::CBuddyMessagePtr);
Q_DECLARE_METATYPE(UserLoginStatus);
Q_DECLARE_METATYPE(FileTransferStatus);
Q_DECLARE_METATYPE(ImageTransferStatus);
Q_DECLARE_METATYPE(std::string);
//Q_DECLARE_METATYPE(const net::CBuddyMessagePtr&);

int main(int argc, char *argv[])
{
    qRegisterMetaType<net::CBuddyMessagePtr>();
    qRegisterMetaType<UserLoginStatus>();
    qRegisterMetaType<FileTransferStatus>();
    qRegisterMetaType<ImageTransferStatus>();
    qRegisterMetaType<std::string>();
    qRegisterMetaType<const net::CBuddyMessagePtr&>();


    LOGI("%sstart client%s", "==========", "==========");

    QApplication a(argc, argv);

    QFile qss(":/BuddyList/Resources/buddy.qss");
    if (!qss.open(QFile::ReadOnly))
    {
        //error
        std::cout << "error";
    }
    qApp->setStyleSheet(qss.readAll());
    qss.close();


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

    QString fileName = QF::getLogDir();
    CAsyncLog::init(fileName.toStdString().c_str());

    fileName += QDir::separator() + QString("logs.txt");
    CIULog::Init(true, false, fileName.toStdString().c_str());


    CFlamingoClientCenter::instance()->init(g_pEventLoop);
    initResources();

    RotateWidget *pLoginD = new RotateWidget(NULL);
    pLoginD->show();

    int nRet = a.exec();
    UnInitSocket();
    g_pEventLoop->quit();
    CAsyncLog::uninit();
    CIULog::Uninit();

    if (t.joinable())
    {
        t.join();
    }

    CConfig::instance()->save();

    return nRet;
}
