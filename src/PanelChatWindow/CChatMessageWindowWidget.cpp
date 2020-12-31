﻿
#include "CChatMessageWindowWidget.h"
#include <QDateTime>
#include <QDebug>
#include <QtWidgets/QVBoxLayout>
#include "CSplitContainer.h"
#include "CSendMsgTextEdit.h"
#include <User/CFlamingoClientCenter.h>
#include <ProtocolData/rpc_Enum.h>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QDir>
#include <utils/FileHelper.h>


CChatMessageWindowWidget::CChatMessageWindowWidget(QWidget *parent) :
    QWidget(parent)
    , m_pParent(parent)
{
    //resize(600, 800);
    createUi();
    connect(m_pSendTextEdit, SIGNAL(sigSendMsg(QString)), this, SLOT(slotSendMsg(QString)));
    connect(this, SIGNAL(sigHandleChatMsg(const net::CBuddyMessagePtr&)), this, SLOT(slotHandleChatMsg(const net::CBuddyMessagePtr&)));

    connect(CFlamingoClientCenter::instance(), SIGNAL(sigFileStatus(int, QString)),
        this, SLOT(onHandleErrorStatus(int, QString)));

    connect(this, SIGNAL(sigSendFile(const FileTransferStatus&, const QString&, const QString&)),
        this, SLOT(slotHandleSendFile(const FileTransferStatus&, const QString&, const QString&)));

    CFlamingoClientCenter::instance()->registCallBack(protocol::msg_type_chat, std::bind(&CChatMessageWindowWidget::handleChatMsg, this, std::placeholders::_1));
}

void CChatMessageWindowWidget::createUi()
{
    QHBoxLayout *pHMainLayout = new QHBoxLayout(this);
    pHMainLayout->setMargin(0);
    pHMainLayout->setSpacing(0);
    {
        m_pShowMsgListWidget = new QListWidget(this);
        m_pSendTextEdit = new CSendMsgTextEdit(this);


        connect(m_pSendTextEdit, SIGNAL(sigSendFile(const QString&)),
            this, SLOT(slotHandleSendFile(const QString&)));
        connect(m_pSendTextEdit, SIGNAL(sigShowRightWidget()),
            this, SLOT(slotShowRightWidget()));

        m_pSlit = new XP::CSplitContainer(Qt::Vertical, 1, this);
        m_pSlit->setWidgets(m_pShowMsgListWidget, m_pSendTextEdit, true, 480);
        m_pSlit->setFirstMinLength(150);

        pHMainLayout->addWidget(m_pSlit);
    }
    {
        m_pRightWidget = new CRightMssageInfoWidget(this);
        m_pRightWidget->setVisible(false);
        pHMainLayout->addWidget(m_pRightWidget);
    }


    setLayout(pHMainLayout);

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


void CChatMessageWindowWidget::slotHandleSendFile(const FileTransferStatus& status, const QString& msg, const QString& fileName)
{
    if (status == FILE_STATUS_CONNECTED)
    {
        FileTransferProgress data;
        data.m_strPullFileName = fileName;
        data.m_strFileName = fileName.mid(fileName.lastIndexOf("/") + 1);
        data.m_strFileSize = QString::number(utils::FileHelper::getFileSize(fileName.toStdString()) / 1024) + QString("k");
        data.m_nPercent = 0;
        data.m_strFileState = "传输连接中";
        m_pRightWidget->updateTransferFileItem(data);
    }
    else if(status == FILE_STATUS_TRANSFERING)
    {
        m_pRightWidget->updatePercent(msg, fileName);
        if (msg == "100")
        {
            CFlamingoClientCenter::instance()->disconnectToFileServer();
        }
    }
    else if (status == FILE_STATUS_ERROR)
    {
        QMessageBox::information(this, "error", msg);
        CFlamingoClientCenter::instance()->disconnectToFileServer();
    }
}

void CChatMessageWindowWidget::slotHandleSendFile(const QString& fileName)
{
    if (fileName.isEmpty())
    {
        return;
    }

    if (!m_pRightWidget->isVisible())
    {
        m_pParent->resize(m_pParent->width() + m_pRightWidget->width(), m_pParent->height());
        m_pRightWidget->setVisible(true);
        m_pRightWidget->setMsgHistory(false);
    }

    CFlamingoClientCenter::instance()->sendFileToServer(fileName, std::bind(&CChatMessageWindowWidget::onHandleSendFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void CChatMessageWindowWidget::slotShowRightWidget()
{
    if (!m_pRightWidget->isVisible())
    {
        m_pParent->resize(m_pParent->width() + m_pRightWidget->width(), m_pParent->height());
        m_pRightWidget->setVisible(true);
        m_pRightWidget->setMsgHistory(true);
    }
    else
    {
        m_pParent->resize(m_pParent->width() - m_pRightWidget->width(), m_pParent->height());
        m_pRightWidget->setVisible(false);
    }
}

void CChatMessageWindowWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void CChatMessageWindowWidget::onHandleSendFile(const FileTransferStatus& status, const QString& msgInfo, const QString& fileName)
{
    emit sigSendFile(status, msgInfo, fileName);
}

void CChatMessageWindowWidget::onHandleErrorStatus(int, QString msg)
{
    if (!msg.isEmpty())
    {
        QMessageBox::information(this, "info", msg);
    }
}

CRightMssageInfoWidget::CRightMssageInfoWidget(QWidget*parent /*= NULL*/)
    :QWidget(parent)
{
    createUi();
    setFixedWidth(280);
}

void CRightMssageInfoWidget::setMsgHistory(bool b)
{
    m_bShowMsgHistorhy = b;
    if (b)
    {
        m_pTitleWidget->setText("消息记录");
    }
    else
    {
        m_pTitleWidget->setText("传输文件");
    }
}

void CRightMssageInfoWidget::updateTransferFileItem(const FileTransferProgress& progress)
{
    auto iter = m_mapTransforFileItem.find(progress.m_strPullFileName);
    if (iter != m_mapTransforFileItem.end())
    {
        iter.value()->updataData(progress);
    }
    else
    {
        CTransferFileItemWidget *pItemWidget = new CTransferFileItemWidget(this);
        pItemWidget->updataData(progress);
        m_mapTransforFileItem[progress.m_strPullFileName] = pItemWidget;

        QListWidgetItem *pListItem = new QListWidgetItem(m_pContent);
        m_pContent->setItemWidget(pListItem, pItemWidget);
    }
}

void CRightMssageInfoWidget::updatePercent(const QString& percent, const QString& fileName)
{
    auto iter = m_mapTransforFileItem.find(fileName);
    if (iter != m_mapTransforFileItem.end())
    {
        iter.value()->updatePercent(percent);
    }
}

void CRightMssageInfoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void CRightMssageInfoWidget::createUi()
{
    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->setContentsMargins(0, 2, 0, 0);
    pLayout->setSpacing(0);

    m_pTitleWidget = new QLabel(this);
    m_pTitleWidget->setText("消息记录");
    m_pTitleWidget->setStyleSheet("border:1px solid green;");
    m_pTitleWidget->setFixedSize(100, 30);

    m_pContent = new QListWidget(this);

    pLayout->addWidget(m_pTitleWidget);
    pLayout->addWidget(m_pContent);

    setLayout(pLayout);
}

CTransferFileItemWidget::CTransferFileItemWidget(QWidget *parent)
    :QWidget(parent)
{
    createUi();
}

void CTransferFileItemWidget::updataData(const FileTransferProgress& progress)
{
    m_pFileInfo->setText(QString("%1 (%2)").arg(progress.m_strFileName).arg(progress.m_strFileSize));
    m_pFileProgress->setValue(progress.m_nPercent);
    m_pFileMsgInfo->setText(progress.m_strFileState);
}

void CTransferFileItemWidget::updatePercent(const QString& percent)
{
    //m_pFileProgress->setValue(percent.toInt());
    if (percent != "100")
    {
        m_pFileMsgInfo->setText(QString("传输中...%1").arg(percent));
    }
    else
    {
        m_pFileMsgInfo->setText("传输中完成");
    }
}

void CTransferFileItemWidget::createUi()
{
    QVBoxLayout   *pVLayout = new QVBoxLayout(this);
    pVLayout->setMargin(0);
    pVLayout->setSpacing(0);
    {
        QHBoxLayout  *pHLayout = new QHBoxLayout;
        pHLayout->setMargin(0);
        pHLayout->setSpacing(0);
        m_pFileTypeImage = new QLabel;
        m_pFileTypeImage->setText("file type");
        m_pFileTypeImage->setFixedSize(70, 70);
        pHLayout->addWidget(m_pFileTypeImage, 1);

        {
            QVBoxLayout *pVLayoutSub = new QVBoxLayout;
            pVLayoutSub->setMargin(0);
            pVLayoutSub->setSpacing(5);

            m_pFileInfo = new QLabel;
            m_pFileProgress = new QProgressBar;
            m_pFileProgress->setRange(0, 100);
            m_pFileMsgInfo = new QLabel;

            pVLayoutSub->addWidget(m_pFileInfo);
            pVLayoutSub->addWidget(m_pFileProgress);
            pVLayoutSub->addWidget(m_pFileMsgInfo);
            pHLayout->addLayout(pVLayoutSub);
        }

        pVLayout->addLayout(pHLayout);
        setLayout(pVLayout);
    }
}
