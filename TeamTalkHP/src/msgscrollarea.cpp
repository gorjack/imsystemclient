#include "msgscrollarea.h"
#include <QPushButton>
#include <QEvent>
#include <QScrollBar>

MsgScrollArea::MsgScrollArea(QWidget *parent)
	: QScrollArea(parent)
	, m_skinWidget(nullptr)
{
	verticalScrollBar()->setSingleStep(32);

	m_spliterBtn = new QPushButton(this);
	m_spliterBtn->setObjectName("rightSpliterBtn");
	m_spliterBtn->setVisible(false);
	m_spliterBtn->setFixedSize(13, 90);

	this->installEventFilter(this);
	m_spliterBtn->installEventFilter(this);

	connect(m_spliterBtn, &QPushButton::clicked, this, &MsgScrollArea::onSpliterBtnClicked);
}

MsgScrollArea::~MsgScrollArea()
{

}

void MsgScrollArea::scrollToBottom(QWidget* widget)
{
	widget->updateGeometry();
	verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

QWidget* MsgScrollArea::getTalkWindowSpliterButton() const
{
	return m_spliterBtn;
}

void MsgScrollArea::setShowSkinControl(QWidget* skinWidget)
{
	m_skinWidget = skinWidget;
}

void MsgScrollArea::onSpliterBtnClicked(bool)
{
	if (m_skinWidget && m_skinWidget->isVisible())
	{
		m_skinWidget->setVisible(false);
		m_spliterBtn->setStyleSheet("QPushButton#rightSpliterBtn{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_left_normal.png);"
			"	border-width:0px;}"
			"	QPushButton#rightSpliterBtn:hover{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_left_hover.png);"
			"	border-width:0px;}"
			"	QPushButton#rightSpliterBtn : pressed{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_left_down.png);"
			"	border-width:0px;}");
	}
	else if (m_skinWidget && !m_skinWidget->isVisible())
	{
		m_skinWidget->setVisible(true);
		m_spliterBtn->setStyleSheet("QPushButton#rightSpliterBtn{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_right_normal.png);"
			"	border-width:0px;}"
			"	QPushButton#rightSpliterBtn:hover{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_right_hover.png);"
			"	border - width:0px;}"
			"	QPushButton#rightSpliterBtn : pressed{"
			"	border - image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_right_down.png);"
			"	border - width:0px;}");
	}
}

void MsgScrollArea::resizeEvent(QResizeEvent *event)
{
	m_spliterBtn->move(width() - m_spliterBtn->width(), (height() - m_spliterBtn->height()) / 2);
	__super::resizeEvent(event);
}

bool MsgScrollArea::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == this)
	{
		if (event->type() == QEvent::Enter)
		{
			this->verticalScrollBar()->setVisible(true);
			this->horizontalScrollBar()->setVisible(true);
			return true;
		}
		else if (event->type() == QEvent::Leave)
		{
			this->verticalScrollBar()->setVisible(false);
			this->horizontalScrollBar()->setVisible(false);
			return true;
		}
	}
	else if (watched == m_spliterBtn)
	{
		if (event->type() == QEvent::Enter)
		{
			this->verticalScrollBar()->setVisible(false);
			return true;
		}
		else if (event->type() == QEvent::Leave)
		{
			this->verticalScrollBar()->setVisible(true);
			return true;
		}
	}
	return __super::eventFilter(watched, event);
}