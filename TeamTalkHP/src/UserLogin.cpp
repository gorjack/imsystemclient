#include "skinwindow.h"
#include "UserLogin.h"
#include "cmainwindow.h"
#include "CRegistDialog.h"
#include "UserClientCenter/CUserClientCenter.h"
#include <QMessageBox>
#include "utils/CConfig.h"
#include "utils/Configuration.h"
#include "utils/commonFunc.h"
#include "utils/directory.h"
#include "UserClientCenter/CUserManager.h"
#include "cmainwindow.h"

static const char* const c_szAccountFile = "user.ini";
UserLogin::UserLogin(QWidget *parent)
	: BasicWindow(parent)
{
    ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	initTitleBar();
	setTitleBarTitle("", ":/TeamTalkHP/Resources/MainWindow/qqlogoclassic.png");
    loadStyleSheet("UserLogin");
	initControl();

	CUserClientCenter::instance()->resetClient();
	CUserClientCenter::instance()->resetAddress();
	CUserClientCenter::instance()->connect_async(0);
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
	connect(ui.registBtn, &QPushButton::clicked, this, &UserLogin::onRegistBtnClicked);
	connect(CUserClientCenter::instance(), SIGNAL(sigStatus(int, QString)), this, SLOT(onRegistStatus(int, QString)));
	connect(CUserClientCenter::instance(), SIGNAL(sigLogindStatus(UserLoginStatus, QString)), this, SLOT(onLogindStatus(UserLoginStatus, QString)));

	connect(CUserManager::instance(), SIGNAL(sigFinishGetFriendListReq()), this, SLOT(onFriendList()));
}

void UserLogin::onLoginBtnClicked()
{
	QString strAccountId = ui.editUserAccount->text();
	QString strPassWd = ui.editPassword->text();

	net::CLoginRequest req(strAccountId.toLatin1(), strPassWd.toLatin1(), 1, protocol::online_type_pc_online);
	CUserClientCenter::instance()->login_async(req);
}

void UserLogin::onRegistBtnClicked()
{
	CRegistDialog regist;
	int nRet = regist.exec();
	if (nRet == QDialog::Accepted)
	{
		CUserClientCenter::instance()->regist_async(regist.getRegistData());
	}
}

void UserLogin::onRegistStatus(int status, QString msg)
{
	if (status == protocol::REGISTER_EXIST)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("您注册的手机号已经被注册, 建议更换号码"));
	}
	else if (status == protocol::REGISTER_SUCCESS)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("恭喜您，注册成功"));
	}
	else
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网络故障，注册失败，请稍后重试！"));
	}
}

void UserLogin::onLogindStatus(UserLoginStatus status, QString strError)
{
	if (status == STATUS_CONNECTED_ERROR)
	{
		QMessageBox::warning(this, "error", strError);
	}

	switch (status)
	{
	case STATUS_LOGINING:
	{
		ui.loginBtn->setText("登录中...");
		ui.loginBtn->setEnabled(false);
		break;
	}
	case STATUS_LOGIN_FINISHED:
	{
		CConfig::instance()->setUserName(ui.editUserAccount->text());
		{
			//保存用户登录配置
			QString strFile = PATH::getUserDir(ui.editUserAccount->text()) + QDir::separator() + c_szAccountFile;

			std::string strPath = utils::qsToS(strFile);
			utils::Configuration configTool(strPath);
			configTool.write("user", "user", utils::qsToS(ui.editUserAccount->text()));
			if (ui.rememberPsd->isChecked())
			{
				configTool.write("user", "pass", utils::qsToS(ui.editPassword->text().trimmed()));
			}
			else
			{
				configTool.write("user", "pass", "");
			}

			configTool.write("user", "remPass", ui.rememberPsd->isChecked() ? 1 : 0);
			configTool.write("user", "autoLogin", ui.autoLogin->isChecked() ? 1 : 0);
			configTool.save();
		}

		CUserManager::instance()->queryFirendList();
		break;
	}
	case STATUS_ERROR:
	{
		ui.loginBtn->setText("登录");
		ui.loginBtn->setEnabled(true);
		QMessageBox::information(this, "提示", strError );
		break;
	}
	case STATUS_CONNECTING:
	{
		ui.loginBtn->setText("连接中...");
		ui.loginBtn->setEnabled(false);
		break;
	}
	case STATUS_CONNECTED:
	{
		ui.loginBtn->setText("登录");
		ui.loginBtn->setEnabled(true);
		break;
	}
	case STATUS_GET_USER_LIST:
	{
		ui.loginBtn->setText(strError);
		ui.loginBtn->setEnabled(false);
		break;
	}
	}
}

void UserLogin::onFriendList()
{
	CMainWindow* pMainwindow = new CMainWindow(ui.editUserAccount->text(), this);
	pMainwindow->show();

	CUserClientCenter::instance()->registCallBack(protocol::msg_type_operatefriend, std::bind(&CMainWindow::onOperateFriends, pMainwindow, std::placeholders::_1));

	close();
}