#pragma once

#include "BasicWindow.h"
#include "ui_UserLogin.h"
#include "UserClientCenter/userdatas.h"

class UserLogin : public BasicWindow
{
	Q_OBJECT

public:
	UserLogin(QWidget *parent = Q_NULLPTR);
	~UserLogin();

private slots:
	void onLoginBtnClicked();
	void onRegistBtnClicked();
	void onRegistStatus(int status, QString msg);
	void onLogindStatus(UserLoginStatus, QString);

	void onFriendList();
private:
	void initControl();

private:
	Ui::UserLogin ui;

};
