#include "skinwindow.h"
#include "UserLogin.h"
#include "cmainwindow.h"

UserLogin::UserLogin(QWidget *parent)
	: BasicWindow(parent)
{
    ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	initTitleBar();
	setTitleBarTitle("", ":/TeamTalkHP/Resources/MainWindow/qqlogoclassic.png");
    loadStyleSheet("UserLogin");
	initControl();
}

UserLogin::~UserLogin()
{
}

void UserLogin::initControl()
{
	QLabel* headlabel = new QLabel(this);
	headlabel->setFixedSize(68, 68);
	QPixmap pix(":/TeamTalkHP/Resources/MainWindow/head_mask.png");
	headlabel->setPixmap(getRoundImage(QPixmap(":/TeamTalkHP/Resources/MainWindow/yutiange.jpg"), pix, headlabel->size()));
	headlabel->move(width()/2 - 34, ui.titleWidget->height() - 34);

	connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);
}

void UserLogin::onLoginBtnClicked()
{
	close();
	CMainWindow* mainwindow = new CMainWindow;
	mainwindow->show();
}