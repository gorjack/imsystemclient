#include "CUserDataWidgetItem.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPainterPath>

CUserDataWidgetItem::CUserDataWidgetItem(QWidget *parent /*= nullptr*/)
{
    setMouseTracking(true);

    m_delPng = QPixmap(":/QQChatMessage/Resources/delete.png");
}

void CUserDataWidgetItem::setMessageText(const QString& msg)
{
    m_strText = msg;
}

void CUserDataWidgetItem::setHeadIcon(const QString& strHead)
{
    m_headPng = QPixmap(strHead);
}

void CUserDataWidgetItem::setDelIcon(const QString& strDel)
{
    m_delPng = QPixmap(strDel);
}

void CUserDataWidgetItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//Ïû¾â³Ý
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    QPainterPath path;
    path.addEllipse(5, 5, 50, 50);
    painter.setClipPath(path);
    painter.drawPixmap(5, 5, 50, 50, m_headPng);

    if (m_bShowDel)
    {
        painter.drawPixmap(m_delIcon, m_delPng);
    }

    painter.restore();
    QPen penText;
    penText.setColor(Qt::black);
    painter.setPen(penText);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    painter.setFont(this->font());
    painter.drawText(m_textRect, m_strText, option);
}

void CUserDataWidgetItem::resizeEvent(QResizeEvent *e)
{
    //m_headIcon.setRect(5, 5, 60, 60);
    m_delIcon.setRect(e->size().width() - 25, 13, 20, e->size().height() - 19);
    m_textRect.setRect(72, 5, e->size().width() - 97, e->size().height() - 3);
}

void CUserDataWidgetItem::mouseMoveEvent(QMouseEvent *e)
{
    if (m_delIcon.contains(e->pos()))
    {
        m_bShowDel = true;
    }
    else
        m_bShowDel = false;
    update();
    QWidget::mouseMoveEvent(e);

    //
}

void CUserDataWidgetItem::mousePressEvent(QMouseEvent *e)
{
    if (m_delIcon.contains(e->pos()))
    {
        emit sigClose();
    }
    QWidget::mousePressEvent(e);
}
