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
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QMessageBox>

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

    // ���࿪����
		// ����Ψһ��ʶ��
	const QString uniqueKey = "MyUniqueAppIdentifier";

	// �����ź���
	//QSystemSemaphore semaphore(uniqueKey, 1, QSystemSemaphore::Open);
	//semaphore.acquire(); // ����

	// �����ڴ�
	QSharedMemory sharedMemory(uniqueKey);
	bool isAlreadyRunning = false;

	if (sharedMemory.attach()) {
		// ������Ը��ӹ����ڴ棬˵������һ��ʵ��������
		isAlreadyRunning = true;
	}
	else {
		if (sharedMemory.create(1)) {
			// ���������ڴ棬��ʾû������ʵ��������
			isAlreadyRunning = false;
		}
		else {
			QMessageBox::critical(nullptr, "Error", "Unable to create shared memory.");
			//semaphore.release(); // �ͷ���
			return 1;
		}
	}

	//semaphore.release(); // �ͷ���

	if (isAlreadyRunning) {
		QMessageBox::warning(nullptr, "Warning", "An instance of this application is already running.");
		return 1;
	}


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
