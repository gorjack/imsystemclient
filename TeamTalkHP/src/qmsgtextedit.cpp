#include "qmsgtextedit.h"

#include <QMovie>
#include <QFont>
#include <QScrollBar>
#include <QMimeData>

QMsgTextEdit::QMsgTextEdit(QWidget *parent)
	: QTextEdit(parent)
{
	
}

QMsgTextEdit::~QMsgTextEdit()
{
	delteAllEmotionImage();
}

void QMsgTextEdit::delteAllEmotionImage()
{
	for (auto itor = m_emotionMap.constBegin(); itor != m_emotionMap.constEnd(); ++itor)
	{
		delete itor.key();
	}
	m_emotionMap.clear();
}

void QMsgTextEdit::addEmotionUrl(int emotionNum)
{
	const QString&& imageName = QString("qrc:/TeamTalkHP/Resources/MainWindow/emotion/%1.png").arg(emotionNum);
	const QString&& flagName = QString("%1").arg(imageName);
	insertHtml(QString("<img src='%1'/>").arg(flagName));
	if (m_listEmotionUrl.contains(imageName))
		return;
	else
		m_listEmotionUrl.append(imageName);

	QMovie* apngMovie = new QMovie(imageName, "apng", this);
	apngMovie->setCacheMode(QMovie::CacheNone);
	m_emotionMap.insert(apngMovie, flagName);

	connect(apngMovie, SIGNAL(frameChanged(int)), this, SLOT(onEmotionImageFrameChange(int)));
	apngMovie->start();

	updateGeometry();
	verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

void QMsgTextEdit::onEmotionImageFrameChange(int frame)
{
	QMovie* movie = qobject_cast<QMovie*>(sender());
	document()->addResource(QTextDocument::ImageResource, QUrl(m_emotionMap.value(movie)), movie->currentPixmap());
	setLineWrapColumnOrWidth(lineWrapColumnOrWidth());
}

void QMsgTextEdit::insertFromMimeData(const QMimeData *source)
{
	__super::insertFromMimeData(source);
}
