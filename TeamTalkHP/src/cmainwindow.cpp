#include "cmainwindow.h"
#include "contactitem.h"
#include "rootcontatitem.h"
#include "skinwindow.h"
#include "notifymanager.h"
#include "talkwindowshell.h"
#include "windowmanager.h"
#include "systray.h"

#include <QPainter>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QProxyStyle>
#include <QTimer>
#include <QUuid>
#include "UserClientCenter/CUserClientCenter.h"
#include "UserClientCenter/CUserManager.h"
#include "UserClientCenter/CUserBusinessCenter.h"
#include <ProtocolData/rpc_structs.h>

#include "CQueryForAddDialog.h"
#include "CConfirmAddFriendDG.h"

#include "CUiResource.h"
#include "utils/IULog.h"

class CustomProxyStyle : public QProxyStyle
{
public:
	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption * option,
        QPainter * painter, const QWidget * widget = nullptr) const
	{
		if (PE_FrameFocusRect == element)
		{
			return;
		}
		else
		{
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};

CMainWindow::CMainWindow(QString userName, QWidget *parent)
	: BasicWindow(parent)
	, m_strUserName(userName)
{
	ui.setupUi(this);
	//setWindowFlags(windowFlags() | Qt::Tool);
    loadStyleSheet("MainWindow");
    initControl();

	QTimer* timer = new QTimer(this);
	timer->setInterval(500);
	connect(timer, &QTimer::timeout, [this](){
		static int level = 0;
		if (level == 99)
		{
			level = 0;
		}
		setLevelPixmap(level);
		level++;
	});
    timer->start();

	CUserClientCenter::instance()->registCallBack(protocol::msg_type_operatefriend, std::bind(&CMainWindow::onOperateFriends, this, std::placeholders::_1));
}

CMainWindow::~CMainWindow()
{
	
}

void CMainWindow::initControl()
{
	ui.treeWidget->setStyle(new CustomProxyStyle);

	setLevelPixmap(0);
	setUserName(m_strUserName);
	setHeadPixmap();
	setStatusMenuIcon();

	QHBoxLayout *flowLayout = new QHBoxLayout();
	flowLayout->setContentsMargins(0, 0, 0, 0);
	flowLayout->setSpacing(2);
	flowLayout->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_7.png", "app_7"));
	flowLayout->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_2.png", "app_2"));
	flowLayout->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_3.png", "app_3"));
	flowLayout->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_4.png", "app_4"));
	flowLayout->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_5.png", "app_5"));
	flowLayout->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_6.png", "app_6"));
	flowLayout->addStretch();
	flowLayout->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/skin.png", "app_skin"));
	ui.appWidget->setLayout(flowLayout);

	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_10.png", "app_10"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_8.png", "app_8"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_11.png", "app_11"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/TeamTalkHP/Resources/MainWindow/app/app_9.png", "app_9"));
	ui.bottomLayout_up->addStretch();

	ui.lineEdit->installEventFilter(this);
	ui.searchLineEdit->installEventFilter(this);

	initContactTree();
	initStrangerTree();

	connect(ui.sysmin, SIGNAL(clicked(bool)), this, SLOT(onShowHide(bool)));
	connect(ui.sysclose, SIGNAL(clicked(bool)), this, SLOT(onShowClose(bool)));
	connect(NotifyManager::getInstance(), &NotifyManager::signalSkinChanged, [this](const QColor& color){
		updateSeachStyle();
	});

	connect(this, SIGNAL(sigOnAddFirendCB(const std::string&)), this, SLOT(slotOnAddFirendCB(const std::string&)));
	connect(ui.addFriendsBtn, SIGNAL(clicked(bool)), this, SLOT(slotOnAddFirendBtnClicked(bool)));
	SysTray* systray = new SysTray(this);
}

void CMainWindow::updateSeachStyle()
{
	ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget {background-color:rgba(%1,%2,%3,50);border-bottom: 1px solid rgba(%1,%2,%3,30);}\
								QPushButton#searchBtn {border-image:url(:/TeamTalkHP/Resources/MainWindow/search/search_icon.png);}").arg(m_colorBackGround.red()).arg(m_colorBackGround.green()).arg(m_colorBackGround.blue()));
}

void CMainWindow::setHeadPixmap()
{
	LOG_INFO("m_strUserName:%s", m_strUserName.toStdString().c_str());
	ui.headLabel->setPixmap(getRoundImage((*TT_PIXMAP(m_strUserName)), 
		const_cast<QPixmap&>((*TT_PIXMAP("head_mask"))), ui.headLabel->size()));
}

void CMainWindow::setUserName(const QString& username)
{
	ui.nameLabel->adjustSize();
	QString name = ui.nameLabel->fontMetrics().elidedText(username, Qt::ElideRight, ui.nameLabel->width());
	ui.nameLabel->setText(name);
}

void CMainWindow::setStatusMenuIcon()
{
	QPixmap statusBtnPixmap(ui.statusBtn->size());
	statusBtnPixmap.fill(Qt::transparent);
	QPainter painter(&statusBtnPixmap);
	painter.drawPixmap(4, 4, (*TT_PIXMAP("StatusSucceeded")));
	painter.drawPixmap(16, 3, (*TT_PIXMAP("arrow_normal_down")));
	ui.statusBtn->setIcon(statusBtnPixmap);
	ui.statusBtn->setIconSize(ui.statusBtn->size());
}

void CMainWindow::setLevelPixmap(int level)
{
	QPixmap levelPixmap(ui.levelBtn->size());
	levelPixmap.fill(Qt::transparent);
	QPainter painter(&levelPixmap);
	painter.drawPixmap(0, 4, QPixmap(":/TeamTalkHP/Resources/MainWindow/lv.png"));
	int unitNum = level / 1 % 10;//取个位数字
	int tenNum = level / 10 % 10;//取十位数字
	//十位
	painter.drawPixmap(10, 4, QPixmap(":/TeamTalkHP/Resources/MainWindow/levelvalue.png"), tenNum * 6, 0, 6, 7);
	//个位
	painter.drawPixmap(16, 4, QPixmap(":/TeamTalkHP/Resources/MainWindow/levelvalue.png"), unitNum * 6, 0, 6, 7);
	ui.levelBtn->setIcon(levelPixmap);
	ui.levelBtn->setIconSize(ui.levelBtn->size());
}

QWidget* CMainWindow::addOtherAppExtension(const QString& apppath, const QString& appName)
{
	QPushButton* btn = new QPushButton(this);
	btn->setFixedSize(20, 20);
	QPixmap pixmap(btn->size());
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	QPixmap appPixmap(apppath);
	painter.drawPixmap((btn->width() - appPixmap.width()) / 2, (btn->height() - appPixmap.height())/2, appPixmap);
	btn->setIcon(pixmap);
	btn->setIconSize(btn->size());
	btn->setProperty("hasborder", true);
	btn->setObjectName(appName);
	connect(btn, &QPushButton::clicked, this, &CMainWindow::onAppIconCliked);
	return btn;
}

void CMainWindow::onAppIconCliked()
{
	if (sender()->objectName() == "app_skin")
	{
		SkinWindow* skinWindow = new SkinWindow();
		skinWindow->show();
    }
    else
    {

    }
}

void CMainWindow::resizeEvent(QResizeEvent *event)
{
	setUserName(QString::fromLocal8Bit("雨田哥-工作号"));
    BasicWindow::resizeEvent(event);
}

bool CMainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (ui.searchLineEdit == obj)
	{
		if (event->type() == QEvent::FocusIn)
		{
			ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget {background-color:rgb(255, 255, 255);border-bottom: 1px solid rgba(%1,%2,%3,100);}\
										   	QPushButton#searchBtn {border-image:url(:/TeamTalkHP/Resources/MainWindow/search/main_search_deldown.png);}\
											QPushButton#searchBtn:hover {border-image:url(:/TeamTalkHP/Resources/MainWindow/search/main_search_delhighlight.png);}\
											QPushButton#searchBtn:pressed{ border-image:url(:/TeamTalkHP/Resources/MainWindow/search/main_search_delhighdown.png);}").arg(m_colorBackGround.red()).arg(m_colorBackGround.green()).arg(m_colorBackGround.blue()));
										   	
		}
		else if (event->type() == QEvent::FocusOut)
		{
			updateSeachStyle();
		}
	}
    return BasicWindow::eventFilter(obj, event);
}

void CMainWindow::mousePressEvent(QMouseEvent *event)
{
	if (qApp->widgetAt(event->pos()) != ui.lineEdit && ui.lineEdit->hasFocus())
	{
		ui.lineEdit->clearFocus();
	}
	else if (qApp->widgetAt(event->pos()) != ui.searchLineEdit && ui.searchLineEdit->hasFocus())
	{
		ui.searchLineEdit->clearFocus();
	}
    BasicWindow::mousePressEvent(event);
}

void CMainWindow::initContactTree()
{
	//展开和收缩时信号，以达到变更我三角图片；
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(onItemClicked(QTreeWidgetItem *, int)));
	connect(ui.treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(onItemExpanded(QTreeWidgetItem *)));
	connect(ui.treeWidget, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(onItemCollapsed(QTreeWidgetItem *)));
	connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));


	const PC::CBuddyList& buddyList = CUserManager::instance()->getFirendList();
	std::vector<PC::CBuddyTeamInfo*> teamFriendList = buddyList.m_arrBuddyTeamInfo;
	for (const auto& iter : teamFriendList)
	{
		//分组节点
		QTreeWidgetItem* pRootFriendItem = new QTreeWidgetItem();
		pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
		//设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
		pRootFriendItem->setData(0, Qt::UserRole, 0);

		RootContatItem* pItemName = new RootContatItem(ui.treeWidget);
		pItemName->setText(QString::fromStdString(iter->m_strName));
		//擦入分组节点
		ui.treeWidget->addTopLevelItem(pRootFriendItem);
		ui.treeWidget->setItemWidget(pRootFriendItem, 0, pItemName);

		for (int nIndex = 0; nIndex < iter->GetBuddyCount(); ++nIndex)
		{
			//添加子节点
			PC::CBuddyInfo* pFriendInfo = iter->GetBuddy(nIndex);
			addMyFriendInfo(pRootFriendItem, pFriendInfo);
		}

		onItemClicked(pRootFriendItem, 0);
	}
}

void CMainWindow::addMyFriendInfo(QTreeWidgetItem* pRootGroupItem, PC::CBuddyInfo* pFriendInfo)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();

	//添加子节点
	pChild->setData(0, Qt::UserRole, 1);
	pChild->setData(0, Qt::UserRole + 1, QString::fromStdString(pFriendInfo->m_strAccount));

	ContactItem* pContactItem = new ContactItem(ui.treeWidget);
    pContactItem->setHeadPixmap(getRoundImage( (*TT_PIXMAP(QString::fromStdString(pFriendInfo->m_strAccount))), 
		(*TT_PIXMAP("head_mask")), pContactItem->getHeadLabelSize()) );

	pContactItem->setUserName(QString::fromStdString(pFriendInfo->m_strNickName));
	pContactItem->setSignName(QString::fromStdString(pFriendInfo->m_strMarkName));
	pRootGroupItem->addChild(pChild);
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);
}

void CMainWindow::initStrangerTree()
{
	//分组节点
	QTreeWidgetItem *pRootFriendItem = new QTreeWidgetItem();
	pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	//设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
	pRootFriendItem->setData(0, Qt::UserRole, 0);
	RootContatItem *pItemName = new RootContatItem(ui.treeWidget);

	int nMyFriendNum = 8;
	QString qsGroupName = QString::fromLocal8Bit("我的好友 %1/%2").arg(0).arg(nMyFriendNum);
	pItemName->setText(qsGroupName);
	//擦入分组节点
	ui.treeWidget->addTopLevelItem(pRootFriendItem);
	ui.treeWidget->setItemWidget(pRootFriendItem, 0, pItemName);

	for (int nIndex = 0; nIndex < nMyFriendNum; ++nIndex)
	{
		//添加子节点
		addStarngerInfo(pRootFriendItem);
	}
}

void CMainWindow::addStarngerInfo(QTreeWidgetItem* pRootGroupItem)
{
    QPixmap pix1,pix2;
    pix1.load(":/TeamTalkHP/Resources/MainWindow/yutiange.jpg");
    pix2.load(":/TeamTalkHP/Resources/MainWindow/head_mask.png");
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	//添加子节点
	pChild->setData(0, Qt::UserRole, 1);
	pChild->setData(0, Qt::UserRole + 1, QString::number((int)pChild));
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);
    pContactItem->setHeadPixmap(getRoundImage(pix1, pix2, pContactItem->getHeadLabelSize()));
	pContactItem->setUserName(QString::fromLocal8Bit("雨田哥-工作号-陌生人2"));
	pContactItem->setSignName(QString::fromLocal8Bit("欢迎访问雨田哥工作号-陌生人1"));
	pRootGroupItem->addChild(pChild);
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);
}

void CMainWindow::onItemClicked(QTreeWidgetItem * item, int column)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		item->setExpanded(!item->isExpanded());
	}
}

void CMainWindow::onItemDoubleClicked(QTreeWidgetItem * item, int column)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (bIsChild)
	{
		WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString());
	}
}

void CMainWindow::onItemExpanded(QTreeWidgetItem * item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		RootContatItem *prootItem = dynamic_cast<RootContatItem*>(ui.treeWidget->itemWidget(item, 0));
		if (prootItem)
		{
			prootItem->setExpanded(true);
		}
	}
}

void CMainWindow::onItemCollapsed(QTreeWidgetItem * item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		RootContatItem *prootItem = dynamic_cast<RootContatItem*>(ui.treeWidget->itemWidget(item, 0));
		if (prootItem)
		{																																																																																						
			prootItem->setExpanded(false);
		}
	}
}

void CMainWindow::onOperateFriends(const std::string& req)
{
	emit sigOnAddFirendCB(req);
}

void CMainWindow::slotOnAddFirendCB(const std::string& param)
{
	net::COperateFriendResultPtr pAddFriendInfo = std::make_shared<net::COperateFriendResult>();
	pAddFriendInfo->decodePackage(param);

	CConfirmAddFriendDG confirmAddFriendDg;
	//别人加自己
	if (pAddFriendInfo->m_uCmd == protocol::Apply)
	{
		confirmAddFriendDg.setWindowTitle(QObject::tr("Add friend"));
		QString msg = QString(QObject::tr("%1 requests to add you as a friend, do you agree?")).arg(pAddFriendInfo->m_szAccountName);

		confirmAddFriendDg.setInfoMsg(msg);
		int nRet = confirmAddFriendDg.exec();
		{
			net::COperateFriendRequestPtr pData = std::make_shared<net::COperateFriendRequest>();
			pData->m_uCmd = (nRet == QDialog::Accepted) ? protocol::Agree : protocol::Refuse;
			pData->m_uAccountID = pAddFriendInfo->m_uAccountID;

			CUserClientCenter::instance()->request_async(pData, NULL);
		}
	}
	else if (pAddFriendInfo->m_uCmd == protocol::Refuse)
	{
		QString msg = QString(QObject::tr("%1 declined the friend request")).arg(pAddFriendInfo->m_szAccountName);
		confirmAddFriendDg.setWindowTitle(QObject::tr("Decline friend request"));
		confirmAddFriendDg.setInfoMsg(msg);
		confirmAddFriendDg.exec();
	}
	else if (pAddFriendInfo->m_uCmd == protocol::Agree)
	{
		QString msg = QString(QObject::tr("You and %1 are already friends, let's start chatting")).arg(pAddFriendInfo->m_szAccountName);
		confirmAddFriendDg.setWindowTitle(QObject::tr("Added friend successfully"));
		confirmAddFriendDg.setInfoMsg(msg);
		confirmAddFriendDg.exec();
	}
}

void CMainWindow::slotOnAddFirendBtnClicked(bool)
{
	CQueryForAddDialog addDlg;

	addDlg.exec();

}
