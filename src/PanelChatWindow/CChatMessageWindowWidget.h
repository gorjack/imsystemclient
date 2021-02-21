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
    void updatePercent(const QString& percent, const int& per);
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
    void updateTransferFileItem(const FileTransferProgress& progress);
    void updatePercent(const QString& percent, const QString& fileName, const int& per);
    void removeItem(const QString& key);
    int fileWidgetCount();
protected:
    void resizeEvent(QResizeEvent *event);
    void createUi();

    using map_type = QMap<QString, QPair<QListWidgetItem *, CTransferFileItemWidget *>>;

    QLabel         *m_pTitleWidget = NULL;
    QListWidget    *m_pContent = NULL;
    map_type        m_mapTransforFileItem;
    bool            m_bShowMsgHistorhy;
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
    void sigSendFile(const FileTransferStatus& status, const QString& msgInfo, const QString& fileName, const int&);
public  Q_SLOTS:
    void slotSendMsg(QString);
    void slotHandleChatMsg(const net::CBuddyMessagePtr& pData);

    void slotHandleSendFile(const QString&);  //获取发送文件路径
    //处理分批发送文件回调数据
    void slotHandleSendFile(const FileTransferStatus& status, const QString& msgInfo, const QString& fileName, const int&);
    
    void slotHandleErrorStatus(int, QString);

    void slotShowRightWidget();

protected:
    void resizeEvent(QResizeEvent *event);
    void onHandleSendFile(const FileTransferStatus& status, const QString& msgInfo, const QString& fileName, const int& persent);
    void sendFileFinishHandle(const FileDataItem& data, const ChatFileDirection& type);

private:
    void createUi();
    void dealMessage(CShowMsgListItemWidget *messageW, QListWidgetItem *item, QString text, QString time, CShowMsgListItemWidget::User_Type type);
    void dealFileMsg(CShowTransferFileItemWidget *messageW, QListWidgetItem *item);
    void dealMessageTime(QString curMsgTime);

    void handleChatMsg(const std::string& str);  //废弃不用

    XP::CSplitContainer             *m_pSlit = NULL;
    QListWidget                     *m_pShowMsgListWidget;
    CSendMsgTextEdit                *m_pSendTextEdit;
    CRightMssageInfoWidget          *m_pRightWidget = NULL;

    int                              m_nTargetId = -1;
    QWidget                         *m_pParent = NULL;
};
