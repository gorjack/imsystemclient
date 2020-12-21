#pragma once

//https://www.yuque.com/lengyuezuixue/togedc/dxfpgb#95m7vh
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidgetItem>
#include "CShowMsgListItemWidget.h"
#include <ProtocolData/rpc_structs.h>


class QListWidgetItem;
class QListWidget;
class CSendMsgTextEdit;

namespace XP
{
    class CSplitContainer;
}
class CChatMessageWindowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CChatMessageWindowWidget(QWidget *parent = 0);

    int id() { return m_nTargetId; }
    void setTargetId(const int& nId) { m_nTargetId = nId; }
Q_SIGNALS:
    void sigHandleChatMsg(const net::CBuddyMessagePtr&);

protected  Q_SLOTS:
    void slotSendMsg(QString);
    void slotHandleChatMsg(const net::CBuddyMessagePtr& pData);

private:
    void createUi();
    void dealMessage(CShowMsgListItemWidget *messageW, QListWidgetItem *item, QString text, QString time, CShowMsgListItemWidget::User_Type type);
    void dealMessageTime(QString curMsgTime);

    void handleChatMsg(const std::string& str);

    XP::CSplitContainer             *m_pSlit = NULL;
    QListWidget                     *m_pShowMsgListWidget;
    CSendMsgTextEdit                *m_pSendTextEdit;
    int                              m_nTargetId = -1;
};
