#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QPainter>
#include <QMovie>
#include <QHBoxLayout>
#include <QCursor>
#include <QMenu>
#include <QDebug>
#include <QTime>
#include "accountitem.h"
#include <QPropertyAnimation>
#include "CRegistDialog.h"
#include <PanelMainWindow/CMainWindow.h>
#include <User/CFlamingoClientCenter.h>
#include <ProtocolData/rpc_structs.h>
#include <ProtocolData/rpc_proEnum.h>
#include <ProtocolData/rpc_Enum.h>
#include <QtWidgets/QMessageBox>
#include <User/CUserManager.h>
#include <utils/Configuration.h>
#include <utils/commonFunc.h>
#include <Env/directory.h>
#include <Env/CConfig.h>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#define TRANSLATE_WIDTH 80
static const char * const c_szAccountFile = "user.ini";

LoginWindow::LoginWindow(QWidget *parent)
	: BaseWindow(parent)
	, ui(new Ui::LoginWindow)
	, m_loginState(ONLINE)
	, m_view(&m_scene)
	, m_isPressed(false)
	, m_graphicsWidget(NULL)
{
	ui->setupUi(this);
	initWindow();
	initMyTitle();
	initAccountList();
	this->loadStyleSheet(":/Resources/LoginWindow/gg.css");

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), SLOT(slot_timeout()));
    loadUsers();
    connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SIGNAL(hideWindow()));
    connect(CFlamingoClientCenter::instance(), SIGNAL(sigLogindStatus(UserLoginStatus, QString)),
        this, SLOT(onLoginsStatus(UserLoginStatus, QString)));

    CFlamingoClientCenter::instance()->resetClient();
    CFlamingoClientCenter::instance()->connect_async(CHAT_SERVER);
    //CFlamingoClientCenter::instance()->connect_async(FILE_SERVER);
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

void LoginWindow::initMyTitle()
{
	// 因为这里有控件层叠了，所以要注意控件raise()方法的调用顺序;
	m_titleBar->move(0, 0);
	m_titleBar->raise();
	m_titleBar->setBackgroundColor(0, 0, 0, true);
	m_titleBar->setButtonType(MIN_BUTTON);
	m_titleBar->setTitleWidth(this->width());
	// 这里需要设置成false，不允许通过标题栏拖动来移动窗口位置,否则会造成窗口位置错误;
	m_titleBar->setMoveParentWindowFlag(false);
	ui->pButtonArrow->raise();
}

void LoginWindow::initWindow()
{
    QMovie *movie = new QMovie();
    movie->setFileName(QString("%1/back.gif").arg(QF::getCurrentResourceDir()));
    movie->setCacheMode(QMovie::CacheAll);
    movie->setScaledSize(ui->backLabel->size());
    ui->backLabel->setMovie(movie);
    movie->start();

	ui->accountComboBox->setEditable(true);
	QLineEdit* lineEdit = ui->accountComboBox->lineEdit();
	lineEdit->setPlaceholderText(("QQ号码/手机/邮箱"));
	ui->passwordEdit->setPlaceholderText(("密码"));

	m_keyboardButton = new QPushButton();
	m_keyboardButton->setObjectName("pButtonKeyboard");
	m_keyboardButton->setFixedSize(QSize(16, 16));
	m_keyboardButton->setCursor(QCursor(Qt::PointingHandCursor));

	QHBoxLayout* passwordEditLayout = new QHBoxLayout();
	passwordEditLayout->addStretch();
	passwordEditLayout->addWidget(m_keyboardButton);
	passwordEditLayout->setSpacing(0);
	passwordEditLayout->setContentsMargins(0, 0, 8, 0);

	ui->passwordEdit->setLayout(passwordEditLayout);
	ui->passwordEdit->setTextMargins(0, 0, m_keyboardButton->width() + 12, 0);

	ui->userHead->setPixmap(QPixmap(":/Resources/LoginWindow/HeadImage.png"));
	ui->loginState->setIcon(QIcon(":/Resources/LoginWindow/LoginState/state_online.png"));
	ui->loginState->setIconSize(QSize(13, 13));

	connect(ui->loginState, SIGNAL(clicked()), this, SLOT(onLoginStateClicked()));
    connect(ui->pButtonArrow, SIGNAL(clicked()), this, SLOT(onNetWorkSet()));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(onLogin()));
    connect(ui->pButtonRegistAccount, SIGNAL(clicked()), this, SLOT(onRegist()));
}

void LoginWindow::initAccountList()
{
	// 设置代理;
	m_Accountlist = new QListWidget(this);
	ui->accountComboBox->setModel(m_Accountlist->model());
	ui->accountComboBox->setView(m_Accountlist);
}

QString LoginWindow::userFile(QString qsUserName) const
{
    return QF::getUserDir(qsUserName) + QDir::separator() + c_szAccountFile;
}

struct FileCompare
{
    bool operator()(const QFileInfo & left, const QFileInfo & right) const
    {
        return left.lastModified() > right.lastModified();
    }
};

void LoginWindow::loadUsers()
{
    QDir dir(QF::getUserRootDir());
    if (!dir.exists())
    {
        return;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    QString qsLastUser;
    QFileInfoList list = dir.entryInfoList();
    std::map<QFileInfo, QString, FileCompare> validInfos;
    for (int i = 0; i < list.size(); ++i)
    {
        QString qsUser = list[i].baseName();
        QString qsPath = userFile(qsUser);
        QFileInfo finfo(qsPath);
        if (finfo.exists())
        {
            validInfos.insert(make_pair(finfo, qsUser));
        }
    }

    if (validInfos.empty())
    {
        return;
    }

    size_t pos = 0;
    ui->accountComboBox->clear();
    QString qsFirstUser;
    int nIndex = 0;
    for (std::map<QFileInfo, QString, FileCompare>::iterator iter = validInfos.begin(); iter != validInfos.end(); ++iter, ++pos)
    {
        QString path = iter->first.filePath();
        utils::Configuration config;
        string strPath = utils::qsToS(path);
        config.load(strPath);
        string strUser = config.read("user", "user");
        QString qsUser = utils::sToQs(strUser);
        {
            AccountItem *account_item = new AccountItem();
            account_item->setAccountInfo(nIndex++, qsUser, QString(""));
            connect(account_item, SIGNAL(signalShowAccountInfo(int, QString)), this, SLOT(onShowAccountInfo(int, QString)));
            connect(account_item, SIGNAL(signalRemoveAccount(int)), this, SLOT(onRemoveAccount(int)));
            QListWidgetItem *list_item = new QListWidgetItem(m_Accountlist);
            m_Accountlist->setItemWidget(list_item, account_item);
        }
        if (qsFirstUser.isEmpty())
        {
            qsFirstUser = qsUser;
        }
    }

    if (!qsFirstUser.isEmpty())
    {
        ui->accountComboBox->setCurrentIndex(0);
        ui->accountComboBox->setEditText(qsFirstUser);
        loadUser(qsFirstUser);
    }

    if (NULL != ui->loginButton)
    {
        ui->loginButton->setFocus();
    }

    if (ui->autoLogin->isChecked())
    {
        m_timer->start(1 * 1000);
    }
}

void LoginWindow::loadUser(QString qsUserName)
{
    QString qsPath = userFile(qsUserName);
    utils::Configuration config;
    string strPath = utils::qsToS(qsPath);
    config.load(strPath);

    ui->passwordEdit->setText(utils::sToQs(config.read("user", "pass")));
    bool bRemPass = config.readInt("user", "remPass", 0) == 1;
    ui->rememberPsd->setChecked(bRemPass);
    bool autoLogin = config.readInt("user", "autoLogin", 0) == 1;
    ui->autoLogin->setChecked(autoLogin);
}

void LoginWindow::saveUser(const QString& strUser)
{
    std::string strPath = utils::qsToS(userFile(strUser));
    utils::Configuration configTool(strPath);
    configTool.write("user", "user", utils::qsToS(strUser));
    if (ui->rememberPsd->isChecked())
    {
        configTool.write("user", "pass", utils::qsToS(ui->passwordEdit->text().trimmed()));
    }
    else
    {
        configTool.write("user", "pass", "");
    }

    configTool.write("user", "remPass", ui->rememberPsd->isChecked() ? 1 : 0);
    configTool.write("user", "autoLogin", ui->autoLogin->isChecked() ? 1 : 0);
    configTool.save();
}


void LoginWindow::onLoginStateClicked()
{
	m_loginStateMemu = new QMenu();
	QAction *pActionOnline = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_online.png"), ("我在线上"));
	QAction *pActionActive = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_Qme.png"), ("Q我吧"));
	m_loginStateMemu->addSeparator();
	QAction *pActionAway = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_away.png"), ("离开"));
	QAction *pActionBusy = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_busy.png"), ("忙碌"));
	QAction *pActionNoDisturb = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_notdisturb.png"), ("请勿打扰"));
	m_loginStateMemu->addSeparator();
	QAction *pActionHide = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_hide.png"), ("隐身"));
	// 设置状态值;
	pActionOnline->setData(ONLINE);
	pActionActive->setData(ACTIVE);
	pActionAway->setData(AWAY);
	pActionBusy->setData(BUSY);
	pActionNoDisturb->setData(NOT_DISTURB);
	pActionHide->setData(HIDE);


	connect(m_loginStateMemu, SIGNAL(triggered(QAction *)), this, SLOT(onMenuClicked(QAction*)));

	QPoint pos = ui->loginState->mapToGlobal(QPoint(0, 0)) + QPoint(0, 20);
	m_loginStateMemu->exec(pos);
}


void LoginWindow::onMenuClicked(QAction * action)
{
	ui->loginState->setIcon(action->icon());
	// 获取状态值;
	m_loginState = (LoginState)action->data().toInt();
	qDebug() << "onMenuClicked" << m_loginState;
}


void LoginWindow::onShowAccountInfo(int index, QString accountName)
{
	ui->accountComboBox->setEditText(accountName);
	ui->accountComboBox->hidePopup();

	// 更换用户头像;
	QString fileName = QString(":/Resources/LoginWindow/headImage/head_%1.png").arg(index);
	ui->userHead->setPixmap(QPixmap(fileName).scaled(ui->userHead->width(), ui->userHead->height()));
}

void LoginWindow::onNetWorkSet()
{
	emit rotateWindow();
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果;
void LoginWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (m_isPressed)
	{
		QPoint movePoint = event->globalPos() - m_startMovePos;
		QPoint widgetPos = this->parentWidget()->pos() + movePoint;
		m_startMovePos = event->globalPos();
		this->parentWidget()->move(widgetPos.x(), widgetPos.y());
	}
	return QWidget::mouseMoveEvent(event);
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
	emit closeWindow();
	return __super::closeEvent(event);
}

void LoginWindow::onRemoveAccount(int index)
{
	for (int row = 0; row < m_Accountlist->count(); row++)
	{
		AccountItem* itemWidget = (AccountItem*)m_Accountlist->itemWidget(m_Accountlist->item(row));
		if (itemWidget != NULL && itemWidget->getItemWidgetIndex() == index)
		{
			m_Accountlist->takeItem(row);
			itemWidget->deleteLater();
		}
	}
}

void LoginWindow::onLoginsStatus(UserLoginStatus status, QString msg)
{
    switch (status)
    {
    case STATUS_LOGINING:
    {
        ui->loginButton->setText("登录中...");
        ui->loginButton->setEnabled(false);
        break;
    }
    case STATUS_LOGIN_FINISHED:
    {
        CConfig::instance()->setUserName(ui->accountComboBox->lineEdit()->text());
        saveUser(ui->accountComboBox->lineEdit()->text());

        if (NULL == m_pMainWindow)
        {
            m_pMainWindow = new CMainWindow(NULL);
        }

        m_pMainWindow->show();
        emit closeWindow();

        break;
    }
    case STATUS_ERROR:
    {
        ui->loginButton->setText("登录");
        ui->loginButton->setEnabled(true);
        QMessageBox::information(this, "提示", msg);
        break;
    }
    case STATUS_CONNECTING:
    {
        ui->loginButton->setText("连接中...");
        ui->loginButton->setEnabled(false);
        break;
    }
    case STATUS_CONNECTED:
    {
        ui->loginButton->setText("登录");
        ui->loginButton->setEnabled(true);
        break;
    }
    case STATUS_GET_USER_LIST:
    {
        ui->loginButton->setText(msg);
        ui->loginButton->setEnabled(false);
        break;
    }
    }
}

void LoginWindow::onLogin()
{
    if (m_timer)
    {
        m_timer->stop();
    }

    if (ui->loginButton->text().contains("取消"))
    {
        ui->loginButton->setText("登录");
        return;
    }

    QString pAccountId = ui->accountComboBox->lineEdit()->text();
    QString pNickName = ui->passwordEdit->text();

    net::CLoginRequest req(pAccountId.toLatin1(), pNickName.toLatin1(), 1, protocol::online_type_pc_online);
    CFlamingoClientCenter::instance()->login_async(req);
}

void LoginWindow::onRegist()
{
    if (NULL == m_pRegistDialog)
    {
        m_pRegistDialog = new CRegistDialog(this);
    }

    m_pRegistDialog->exec();
}

void LoginWindow::slot_timeout()
{
    if (m_remainSecond == 0)
    {
        if (NULL != m_timer)
        {
            m_timer->stop();
        }
        if (NULL != ui->loginButton)
        {
            ui->loginButton->click();
        }
    }
    else
    {
        if (NULL != ui->loginButton)
        {
            ui->loginButton->setText(QString("取消") + "(" + QString::number(m_remainSecond) + ")");
        }
        --m_remainSecond;
    }
}
