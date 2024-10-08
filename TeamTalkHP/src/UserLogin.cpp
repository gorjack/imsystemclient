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
#include "CUiResource.h"

static const char* const c_szAccountFile = "user.ini";
UserLogin::UserLogin(QWidget *parent)
	: BasicWindow(parent)
{
    ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	initTitleBar();

	QString strLoginDir = QApplication::applicationDirPath() + QDir::separator() + 
		QString("..") + QDir::separator() + QString("resource") + QDir::separator() + QString("login") + QDir::separator();
	CUiResource::instance()->parseImage(strLoginDir);

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

	headlabel->setPixmap(getRoundImage((*TT_PIXMAP("login")), const_cast<QPixmap&>((*TT_PIXMAP("head_mask"))), headlabel->size()));
	headlabel->move(width()/2 - 34, ui.titleWidget->height() - 34);

	connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);
	connect(ui.registBtn, &QPushButton::clicked, this, &UserLogin::onRegistBtnClicked);
	connect(CUserClientCenter::instance(), SIGNAL(sigStatus(int, QString)), this, SLOT(onRegistStatus(int, QString)));
	connect(CUserClientCenter::instance(), SIGNAL(sigLogindStatus(UserLoginStatus, QString)), this, SLOT(onLogindStatus(UserLoginStatus, QString)));

	connect(this, SIGNAL(sigEmitToLogin()), this, SLOT(onFriendList()));
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
		QMessageBox::information(this, QObject::tr("Hint"), QObject::tr("The mobile phone number you registered has already been registered. It is recommended to change the number."));
	}
	else if (status == protocol::REGISTER_SUCCESS)
	{
		QMessageBox::information(this, QObject::tr("Hint"), QObject::tr("Congratulations, your registration is successful"));
	}
	else
	{
		QMessageBox::information(this, QObject::tr("Hint"), QObject::tr("Network failure, registration failed, please try again later!"));
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
		ui.loginBtn->setText(QObject::tr("Logining...."));
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

		emit sigEmitToLogin();
		break;
	}
	case STATUS_ERROR:
	{
		ui.loginBtn->setText(QObject::tr("Login"));
		ui.loginBtn->setEnabled(true);
		QMessageBox::information(this, QObject::tr("Hint"), strError );
		break;
	}
	case STATUS_CONNECTING:
	{
		ui.loginBtn->setText(QObject::tr("connecting"));
		ui.loginBtn->setEnabled(false);
		break;
	}
	case STATUS_CONNECTED:
	{
		ui.loginBtn->setText(QObject::tr("Login"));
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
	close();

	//先初始化资源
	QString strUserDir = QApplication::applicationDirPath() + QDir::separator() +
		QString("..") + QDir::separator() + QString("userdata") + QDir::separator() + 
		QString("users") + QDir::separator() + 
		ui.editUserAccount->text() + QDir::separator() + 
		QString("resource") + QDir::separator();
	
	CUiResource::instance()->parseImage(strUserDir);

	strUserDir = QApplication::applicationDirPath() + QDir::separator() +
		QString("..") + QDir::separator() + QString("resource");
	CUiResource::instance()->parseImage(strUserDir);

	CMainWindow* pMainwindow = new CMainWindow(ui.editUserAccount->text());


	pMainwindow->show();
}