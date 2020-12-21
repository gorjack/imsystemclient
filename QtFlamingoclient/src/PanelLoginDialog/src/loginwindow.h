#ifndef LoginWindow_H
#define LoginWindow_H

#include "basewindow.h"
#include <QListWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <User/userdatas.h>

namespace Ui {
	class LoginWindow;
}


typedef enum
{
	ONLINE = 1,     //在线;
	ACTIVE,         //活跃;
	AWAY,           //离开;
	BUSY,           //忙碌;
	NOT_DISTURB,    //请勿打扰; 
	HIDE,           //隐身;
	OFFLINE         //离线;
}LoginState;

class CRegistDialog;
class CMainWindow;
class LoginWindow : public BaseWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = 0);
	~LoginWindow();

signals:
	void rotateWindow();
	void closeWindow();
	void hideWindow();

private:
	void initMyTitle();
	void initWindow();
	void initAccountList();
    QString userFile(QString qsUserName) const;

    void loadUsers();
    void loadUser(QString qsUserName);
    void saveUser(const QString& strUser);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	

private slots:
	void onLoginStateClicked();
	void onMenuClicked(QAction * action);
	void onShowAccountInfo(int index, QString accountName);
	void onNetWorkSet();
	void onRemoveAccount(int index);

    void onLoginsStatus(UserLoginStatus status, QString msg);
    void onLogin();
    void onRegist();
    void slot_timeout();
private:
	Ui::LoginWindow           *ui;
	QPushButton               *m_keyboardButton = NULL;
	QMenu                     *m_loginStateMemu = NULL;
	QListWidget               *m_Accountlist;

	// 翻转;
	QGraphicsScene             m_scene;
    QGraphicsView              m_view;
	QGraphicsWidget           *m_graphicsWidget = NULL;

	bool                       m_isPressed;
	QPoint                     m_startMovePos;

    CRegistDialog             *m_pRegistDialog = NULL;
    CMainWindow               *m_pMainWindow = NULL;
    QTimer                    *m_timer = NULL;
    LoginState                 m_loginState;
    int                        m_remainSecond = 3;
};

#endif // LoginWindow_H