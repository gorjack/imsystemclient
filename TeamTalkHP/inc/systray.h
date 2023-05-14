#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QWidget>
#include <QSystemTrayIcon>

class SysTray : public QSystemTrayIcon
{
	Q_OBJECT

public:
	SysTray(QWidget *parent);
	~SysTray();

public Q_SLOTS:
	void onIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
	void initSysTemTray();
	void addSysTrayMenu();

private:
	QWidget* m_parent;
};

#endif // SYSTRAY_H
