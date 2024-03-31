#include "talkwindowshell.h"
#include "talkwindow.h"
#include "talkwindowitem.h"
#include "commonutils.h"
#include "emotionwindow.h"

#include <QDebug>
#include <QPainter>

TalkWindowShell::TalkWindowShell(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	initControl();
}

TalkWindowShell::~TalkWindowShell()
{
	delete m_emotionWindow;
	m_emotionWindow = nullptr;
}

void TalkWindowShell::initControl()
{
	loadStyleSheet("TalkWindow");
	setWindowIcon(QIcon(":/TeamTalkHP/Resources/MainWindow/yutiange.jpg"));
	setWindowTitle(QString::fromLocal8Bit("¸ß¸ç-ÁÄÌì´°¿Ú"));

	m_emotionWindow = new EmotionWindow;
	m_emotionWindow->hide();

	QList<int> leftWidgetSize;
	leftWidgetSize << 154 << width() - 154;
	ui.splitter->setSizes(leftWidgetSize);

	ui.listWidget->setStyle(new CustomProxyStyle(this));

	connect(ui.listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
	connect(m_emotionWindow, SIGNAL(signalEmotionItemClicked(int)), this, SLOT(onEmotionItemClicked(int)));
}

void TalkWindowShell::onEmotionBtnClicked(bool)
{
	m_emotionWindow->setVisible(!m_emotionWindow->isVisible());
	QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));
	emotionPoint.setX(emotionPoint.x() + 170);
	emotionPoint.setY(emotionPoint.y() + 220);
	m_emotionWindow->move(emotionPoint);
}

void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem *item)
{
	QWidget* talkwindowWidget = m_talkwindowItemMap.find(item).value();
	ui.rightStackedWidget->setCurrentWidget(talkwindowWidget);
}

void TalkWindowShell::setCurrentWidget(QWidget* widget)
{
	ui.rightStackedWidget->setCurrentWidget(widget);
}

void TalkWindowShell::addTalkWindow(TalkWindow* talkwindow, TalkWindowItem* talkwindowitem)
{
	ui.rightStackedWidget->addWidget(talkwindow);
	connect(m_emotionWindow, SIGNAL(signalEmotionWindowHide()), talkwindow, SLOT(onSetEmotionBtnStatus()));

	QListWidgetItem *aItem = new QListWidgetItem(ui.listWidget);
	m_talkwindowItemMap.insert(aItem, talkwindow);

	aItem->setSelected(true);
	talkwindowitem->setHeadPixmap("");
	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem, talkwindowitem);

	onTalkWindowItemClicked(aItem);

	connect(talkwindowitem, &TalkWindowItem::signalCloseClicked, [talkwindowitem, talkwindow, aItem, this](){
		m_talkwindowItemMap.remove(aItem);
		talkwindow->close();
		ui.listWidget->takeItem(ui.listWidget->row(aItem));
		delete talkwindowitem;
		ui.rightStackedWidget->removeWidget(talkwindow);
		if (ui.rightStackedWidget->count() < 1)
			close();
	});
}

void TalkWindowShell::onEmotionItemClicked(int emotionNum)
{
	TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget());
	if (curTalkWindow)
	{
		curTalkWindow->addEmotionImage(emotionNum);
	}
}
