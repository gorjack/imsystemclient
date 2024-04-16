#include "windowmanager.h"
#include "talkwindowshell.h"
#include "talkwindow.h"
#include "talkwindowitem.h"

Q_GLOBAL_STATIC(WindowManager, theInstance)
WindowManager::WindowManager()
	: QObject(nullptr)
	, m_talkwindowshell(nullptr)
{

}

WindowManager::~WindowManager()
{

}

WindowManager* WindowManager::getInstance()
{
	return theInstance();
}

void WindowManager::addWindowName(const QString& qsWindowName, QWidget* qWidget)
{
	if (!m_windowMap.contains(qsWindowName))
	{
		m_windowMap.insert(qsWindowName, qWidget);
	}
}

void WindowManager::deleteWindowName(const QString& qsWindowName)
{
	m_windowMap.remove(qsWindowName);
}

QWidget* WindowManager::findWindowName(const QString& qsWindowName)
{
	if (m_windowMap.contains(qsWindowName))
	{
		return m_windowMap.value(qsWindowName);
	}
	return nullptr;
}

void WindowManager::addNewTalkWindow(const QString& uid)
{
	if (m_talkwindowshell == nullptr)
	{
		m_talkwindowshell = new TalkWindowShell;
		connect(m_talkwindowshell, &TalkWindowShell::destroyed, [this](QObject* obj){
			m_talkwindowshell = nullptr;
		});
	}

	QWidget* widget = findWindowName(uid);
	if (widget == nullptr)
	{
		TalkWindow* talkwindow1 = new TalkWindow(m_talkwindowshell, uid);
		TalkWindowItem* talkwindowItem1 = new TalkWindowItem(talkwindow1);
		talkwindow1->setWindowName(uid);
		talkwindowItem1->setMsgLabelContent(uid);
		talkwindow1->setWindowSignName(uid + QString("hello"));
		m_talkwindowshell->addTalkWindow(talkwindow1, talkwindowItem1);
	}
	else
	{
		m_talkwindowshell->setCurrentWidget(widget);
	}
	m_talkwindowshell->show();
	m_talkwindowshell->activateWindow();
}
