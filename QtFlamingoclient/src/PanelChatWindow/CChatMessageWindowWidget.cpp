
#include "CChatMessageWindowWidget.h"
#include <QDateTime>
#include <QDebug>
#include <QtWidgets/QVBoxLayout>
#include "CSplitContainer.h"
#include "CSendMsgTextEdit.h"
#include <User/CFlamingoClientCenter.h>
#include <ProtocolData/rpc_Enum.h>

CChatMessageWindowWidget::CChatMessageWindowWidget(QWidget *parent) :
    QWidget(parent)
{
    //resize(600, 800);
    createUi();
    connect(m_pSendTextEdit, SIGNAL(sigSendMsg(QString)), this, SLOT(slotSendMsg(QString)));
    connect(this, SIGNAL(sigHandleChatMsg(const net::CBuddyMessagePtr&)), this, SLOT(slotHandleChatMsg(const net::CBuddyMessagePtr&)));

    CFlamingoClientCenter::instance()->registCallBack(protocol::msg_type_chat, std::bind(&CChatMessageWindowWidget::handleChatMsg, this, std::placeholders::_1));
}

void CChatMessageWindowWidget::createUi()
{
    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->setSpacing(0);

    m_pShowMsgListWidget = new QListWidget(this);
    //m_pShowMsgListWidget->setStyleSheet("background-color: rgba(255, 255, 255, 40%); border-left-width:0;border-style:outset");
   // m_pShowMsgListWidget->setStyleSheet("background-color: transparent; border-left-width:0;border-style:outset");

    m_pSendTextEdit = new CSendMsgTextEdit(this);

    m_pSlit = new XP::CSplitContainer(Qt::Vertical, 1, this);
    m_pSlit->setWidgets(m_pShowMsgListWidget, m_pSendTextEdit, true, 480);
    m_pSlit->setFirstMinLength(150);

    pLayout->addWidget(m_pSlit, 1);

    setLayout(pLayout);

}


void CChatMessageWindowWidget::dealMessage(CShowMsgListItemWidget *messageW, QListWidgetItem *item, QString text, QString time, CShowMsgListItemWidget::User_Type type)
{
    messageW->setFixedWidth(this->width() - 40);

    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    m_pShowMsgListWidget->setItemWidget(item, messageW);
}

void CChatMessageWindowWidget::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if (m_pShowMsgListWidget->count() > 0) {
        QListWidgetItem* lastItem = m_pShowMsgListWidget->item(m_pShowMsgListWidget->count() - 1);
        CShowMsgListItemWidget* messageW = (CShowMsgListItemWidget*)m_pShowMsgListWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
    }
    else {
        isShowTime = true;
    }
    if (isShowTime) {
        CShowMsgListItemWidget* messageTime = new CShowMsgListItemWidget(m_pShowMsgListWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(m_pShowMsgListWidget);

        QSize size = QSize(this->width() - 40, 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, CShowMsgListItemWidget::User_Time);
        m_pShowMsgListWidget->setItemWidget(itemTime, messageTime);
    }
}


void CChatMessageWindowWidget::handleChatMsg(const std::string& strMsg)
{
    net::CBuddyMessagePtr pData = boost::make_shared<net::CBuddyMessage>();
    pData->decodePackage(strMsg);
    emit sigHandleChatMsg(pData);
}

void CChatMessageWindowWidget::slotSendMsg(QString msg)
{
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    bool isSending = true; // 发送中
    m_pSendTextEdit->setText("");

    //这里unique_ptr 有没有问题
    net::CBuddyMessagePtr pData = boost::make_shared<net::CBuddyMessage>();
    pData->m_msgMesText = msg.toStdString();
    pData->m_nTargetId = m_nTargetId;
    bool isSend = CFlamingoClientCenter::instance()->request_async(pData);
    if (isSend)
    {
        dealMessageTime(time);
        CShowMsgListItemWidget* messageW = new CShowMsgListItemWidget(m_pShowMsgListWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(m_pShowMsgListWidget);
        dealMessage(messageW, item, msg, time, CShowMsgListItemWidget::User_Me);
    }

    m_pShowMsgListWidget->setCurrentRow(m_pShowMsgListWidget->count() - 1);
}

void CChatMessageWindowWidget::slotHandleChatMsg(const net::CBuddyMessagePtr& pData)
{
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    bool isSending = true; // 发送中
    m_pSendTextEdit->setText("");

    dealMessageTime(time);

    CShowMsgListItemWidget* messageW = new CShowMsgListItemWidget(m_pShowMsgListWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(m_pShowMsgListWidget);
    dealMessage(messageW, item, QString::fromStdString(pData->m_msgMesText), time, CShowMsgListItemWidget::User_She);

    m_pShowMsgListWidget->setCurrentRow(m_pShowMsgListWidget->count() - 1);
}
