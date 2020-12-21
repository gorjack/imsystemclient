#include "CBuddyItem.h"
#include <QEvent>
#include <QPainter>
#include <QPixmap>

CBuddyItem::CBuddyItem(QWidget *parent /*= 0*/)
    :QWidget(parent)
{
    initUi();
}

void CBuddyItem::initUi()
{
    m_pHead = new QWidget(this);
    m_pName = new QLabel(this);
    m_pSign = new QLabel(this);

    m_pHead->setFixedSize(40, 40);

    QPalette color;
    color.setColor(QPalette::Text, Qt::gray);
    m_pSign->setPalette(color);
  
    m_pHead->move(7, 7);
    m_pName->move(54, 10);
    m_pSign->move(54, 27);
    m_pHead->installEventFilter(this);
}

bool CBuddyItem::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_pHead)
    {
        if (event->type() == QEvent::Paint)
        {
            QPainter painter(m_pHead);
            painter.drawPixmap(m_pHead->rect(), QPixmap(m_pHeadPath));
        }
    }
    return QWidget::eventFilter(obj, event);
}
