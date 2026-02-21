#include "emotionwindow.h"
#include "commonutils.h"
#include "emotionlabelitem.h"

#include <QPainter>
#include <QFocusEvent>
#include <QMovie>
#include <QScrollBar>
#include <QStyleOption>
#include <math.h>

const int emotionColumn = 14;
const int emotionRow = ceil(170 / 14);

EmotionWindow::EmotionWindow(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_DeleteOnClose);

	ui.setupUi(this);
	initControl();
}

EmotionWindow::~EmotionWindow()
{

}

void EmotionWindow::initControl()
{
	ui.scrollArea->verticalScrollBar()->setSingleStep(32);

	CommonUtils::loadStyleSheet(this, "EmotionWindow");
	for (int row = 0; row < emotionRow; row++)
	{
		for (int column = 0; column < emotionColumn; column++)
		{
			EmotionLabelItem* label = new EmotionLabelItem(this);
			label->setEmotionName(row * emotionColumn + column);
			connect(label, &EmotionLabelItem::emotionClicked, this, &EmotionWindow::addEmotion);
			ui.gridLayout->addWidget(label, row, column);
		}
	}
}

void EmotionWindow::addEmotion(int emotionNum)
{
	hide();
	emit signalEmotionWindowHide();
	emit signalEmotionItemClicked(emotionNum);
}

void EmotionWindow::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	__super::paintEvent(event);
}

void EmotionWindow::showEvent(QShowEvent *event)
{
	setFocus();
	__super::showEvent(event);
}

void EmotionWindow::focusOutEvent(QFocusEvent *event)
{
	QWidget* widget = qApp->widgetAt(QCursor::pos());
	if (widget != this && widget != ui.emotionWidget && widget != ui.topWidget)
	{
		hide();
		emit signalEmotionWindowHide();
	}

	__super::focusOutEvent(event);
}
