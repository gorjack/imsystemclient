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

CMainWindow::CMainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::Tool);
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
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::initControl()
{
	ui.treeWidget->setStyle(new CustomProxyStyle);

	setLevelPixmap(0);
    setUserName(QString::fromLocal8Bit("雨田哥-工作号"));
	setHeadPixmap(":/TeamTalkHP/Resources/MainWindow/yutiange.jpg");
	setStatusMenuIcon(":/TeamTalkHP/Resources/MainWindow/StatusSucceeded.png");

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

	SysTray* systray = new SysTray(this);
}

void CMainWindow::updateSeachStyle()
{
	ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget {background-color:rgba(%1,%2,%3,50);border-bottom: 1px solid rgba(%1,%2,%3,30);}\
								QPushButton#searchBtn {border-image:url(:/TeamTalkHP/Resources/MainWindow/search/search_icon.png);}").arg(m_colorBackGround.red()).arg(m_colorBackGround.green()).arg(m_colorBackGround.blue()));
}

void CMainWindow::setHeadPixmap(const QString& headPath)
{
    QPixmap pix1;
    pix1.load(":/TeamTalkHP/Resources/MainWindow/head_mask.png");
    ui.headLabel->setPixmap(getRoundImage(QPixmap(headPath), pix1, ui.headLabel->size()));
}

void CMainWindow::setUserName(const QString& username)
{
	ui.nameLabel->adjustSize();
	QString name = ui.nameLabel->fontMetrics().elidedText(username, Qt::ElideRight, ui.nameLabel->width());
	ui.nameLabel->setText(name);
}

void CMainWindow::setStatusMenuIcon(const QString& statusPath)
{
	QPixmap statusBtnPixmap(ui.statusBtn->size());
	statusBtnPixmap.fill(Qt::transparent);
	QPainter painter(&statusBtnPixmap);
	painter.drawPixmap(4, 4, QPixmap(statusPath));
	painter.drawPixmap(16, 3, QPixmap(":/TeamTalkHP/Resources/MainWindow/arrow_normal.gft.png"));
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
	//分组节点
	QTreeWidgetItem *pRootFriendItem = new QTreeWidgetItem();
	pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	//设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
	pRootFriendItem->setData(0, Qt::UserRole, 0);
	RootContatItem *pItemName = new RootContatItem(ui.treeWidget);
	
	int nMyFriendNum = 6;
	QString qsGroupName = QString::fromLocal8Bit("我的好友 %1/%2").arg(0).arg(nMyFriendNum);
	pItemName->setText(qsGroupName);
	//擦入分组节点
	ui.treeWidget->addTopLevelItem(pRootFriendItem);
	ui.treeWidget->setItemWidget(pRootFriendItem, 0, pItemName);

	for (int nIndex = 0; nIndex < nMyFriendNum; ++nIndex)
	{
		//添加子节点
		addMyFriendInfo(pRootFriendItem);
	}
}

void CMainWindow::addMyFriendInfo(QTreeWidgetItem* pRootGroupItem)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
    QPixmap pix1;
    pix1.load(":/TeamTalkHP/Resources/MainWindow/head_mask.png");
	//添加子节点
	pChild->setData(0, Qt::UserRole, 1);
	pChild->setData(0, Qt::UserRole + 1, QString::number((int)pChild));
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);
    pContactItem->setHeadPixmap(getRoundImage(QPixmap(":/TeamTalkHP/Resources/MainWindow/yutiange.jpg"), pix1, pContactItem->getHeadLabelSize()));
	pContactItem->setUserName(QString::fromLocal8Bit("雨田哥-工作号"));
	pContactItem->setSignName(QString::fromLocal8Bit("欢迎访问雨田哥工作号"));
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
	QString qsGroupName = QString::fromLocal8Bit("陌生人 %1/%2").arg(0).arg(nMyFriendNum);
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
	pContactItem->setUserName(QString::fromLocal8Bit("雨田哥-工作号-陌生人"));
	pContactItem->setSignName(QString::fromLocal8Bit("欢迎访问雨田哥工作号-陌生人"));
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
