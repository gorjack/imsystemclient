#pragma once

//https://www.yuque.com/lengyuezuixue/togedc/dxfpgb#95m7vh
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidgetItem>
#include "CShowMsgListItemWidget.h"
#include <ProtocolData/rpc_structs.h>
#include <user/userdatas.h>

class QListWidgetItem;
class QListWidget;
class CSendMsgTextEdit;
class CRightMssageInfoWidget;
class QProgressBar;
class QLabel;

namespace XP
{
    class CSplitContainer;
}

class CTransferFileItemWidget : public QWidget
{
public:
    CTransferFileItemWidget(QWidget *parent);

    void updataData(const FileTransferProgress& progress);
protected:
    void createUi();
    QLabel               *m_pFileTypeImage;
    QLabel               *m_pFileInfo;
    QLabel               *m_pFileMsgInfo;
    QProgressBar         *m_pFileProgress;
};

class CRightMssageInfoWidget : public QWidget
{
public:
    CRightMssageInfoWidget(QWidget*parent = NULL);

    void setMsgHistory(bool b);
    void addTransferFileItem(const FileTransferProgress& progress);
protected:
    void resizeEvent(QResizeEvent *event);
    void createUi();

    QLabel           *m_pTitleWidget = NULL;
    QListWidget      *m_pContent = NULL;
    bool              m_bShowMsgHistorhy;
};

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
    void slotHandleSendFile(const FileTransferStatus& status, const QString& msg);
    void slotShowRightWidget();

protected:
    void resizeEvent(QResizeEvent *event);
private:
    void createUi();
    void dealMessage(CShowMsgListItemWidget *messageW, QListWidgetItem *item, QString text, QString time, CShowMsgListItemWidget::User_Type type);
    void dealMessageTime(QString curMsgTime);

    void handleChatMsg(const std::string& str);

    XP::CSplitContainer             *m_pSlit = NULL;
    QListWidget                     *m_pShowMsgListWidget;
    CSendMsgTextEdit                *m_pSendTextEdit;
    CRightMssageInfoWidget          *m_pRightWidget = NULL;

    int                              m_nTargetId = -1;
    QWidget                         *m_pParent = NULL;
};
