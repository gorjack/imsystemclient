#include "emotionlabelitem.h"

#include <QMovie>

EmotionLabelItem::EmotionLabelItem(QWidget *parent)
	: QClickLabel(parent)
{
	initControl();
	connect(this, &QClickLabel::clicked, [this](){
		emit emotionClicked(m_emotionName);
	});
}

void EmotionLabelItem::initControl()
{
	setAlignment(Qt::AlignCenter);
	setObjectName("emotionLabelItem");
	setFixedSize(32, 32);
}

EmotionLabelItem::~EmotionLabelItem()
{

}

void EmotionLabelItem::setEmotionName(int emotionName)
{
	m_emotionName = emotionName;
	QString imageName = QString(":/TeamTalkHP/Resources/MainWindow/emotion/%1.png").arg(emotionName);
	m_apngMovie = new QMovie(imageName, "apng", this);
	m_apngMovie->start();
	m_apngMovie->stop();
	setMovie(m_apngMovie);
}

void EmotionLabelItem::enterEvent(QEvent *event)
{
	m_apngMovie->start();
	__super::enterEvent(event);
}

void EmotionLabelItem::leaveEvent(QEvent *event)
{
	m_apngMovie->jumpToFrame(0);
	m_apngMovie->stop();
	__super::leaveEvent(event);
}
