#include "systray.h"
#include "custommenu.h"

#define TRAY_ICON	      ":/TeamTalkHP/Resources/MainWindow/app/logo.ico"

SysTray::SysTray(QWidget *parent)
		: m_parent(parent)
		, QSystemTrayIcon(parent)
{
	initSysTemTray();
	show();
}

SysTray::~SysTray()
{

}

void SysTray::initSysTemTray()
{
	setToolTip(QStringLiteral("QQ-ÓêÌï¸ç"));
	setIcon(QIcon(TRAY_ICON));
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}

void SysTray::onIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger)
	{
		m_parent->show();
		m_parent->activateWindow();
	}
	else if (reason == QSystemTrayIcon::Context)
	{
		addSysTrayMenu();
	}
}

void SysTray::addSysTrayMenu()
{
	CustomMenu* customMenu = new CustomMenu(m_parent);
	customMenu->addCustomMenu("onShow", TRAY_ICON, QStringLiteral("ÏÔÊ¾"));
	customMenu->addCustomMenu("onShow", ":/TeamTalkHP/Resources/MainWindow/app/face_setting_btn_normal.png", QStringLiteral("ÉèÖÃ"));
	customMenu->addSeparator();
	customMenu->addCustomMenu("onQuit", ":/TeamTalkHP/Resources/MainWindow/app/page_close_btn_hover.png", QStringLiteral("ÍË³ö"));

	connect(customMenu->getAction("onShow"), SIGNAL(triggered(bool)), m_parent, SLOT(onShowNormal(bool)));
	connect(customMenu->getAction("onQuit"), SIGNAL(triggered(bool)), m_parent, SLOT(onShowQuit(bool)));
	customMenu->exec(QCursor::pos());
	delete customMenu;
	customMenu = nullptr;
}