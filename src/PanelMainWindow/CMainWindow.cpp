#include "CMainWindow.h"
#include <User/CFlamingoClientCenter.h>
#include <User/CUserManager.h>
#include <CQueryForAddDialog.h>
#include "CBuddyListWidget.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtGui/QtEvents>
#include <PanelBaseWidget/CPushButton.h>
#include <Env/CConfig.h>
#include <CConfirmAddFriendDG.h>
#include <UiResources/CUiResource.h>
#include <PanelChatWindow/UserDataInfo.h>

//#ifdef WIN32  
//#pragma execution_character_set("utf-8")  
//#endif

enum 
{
    ID_HEAD_IMAGE_BTN = 0,
    ID_MESSAGE_LIST_BTN,
    ID_CONTACK_PERSSION_BTN,
    ID_GROUPS_BTN,
};

CMainWindow::CMainWindow(QWidget *parent /*= Q_NULLPTR*/)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    createUi();
    this->setWindowIcon(QIcon(*TT_PIXMAP("imonline")));

    m_pSystemIcon = new QSystemTrayIcon(this);
    m_pSystemIcon->setIcon(QIcon(*TT_PIXMAP("imonline")));
    m_pSystemIcon->show();
    connect(m_pSystemIcon, &QSystemTrayIcon::activated, this, &CMainWindow::slotIconActivated);
    bool s = connect(CFlamingoClientCenter::instance(), SIGNAL(sigChatMessageComming(const net::CBuddyMessagePtr&)),
        this, SLOT(slotHandleCacheChatMsg(const CBuddyMessagePtr&)));

    bool sr = connect(this, SIGNAL(sigTestMsg(const net::CBuddyMessagePtr&)),
        this, SLOT(slotTestMsg(const net::CBuddyMessagePtr&)));

    resize(430, 835);

    ui.statusbar->addPermanentWidget(ui.m_pAddFriend);
    connect(ui.m_pAddFriend, SIGNAL(clicked()), this, SLOT(slotEmitAddFirend()));
    connect(CUserManager::instance(), SIGNAL(sigFinishGetFriendListReq()), this, SLOT(slotRefreshFriendList()));
    connect(this, SIGNAL(sigOnAddFirendCB(const std::string&)), this, SLOT(slotOnAddFirendCB(const std::string&)));

    slotRefreshFriendList();
}

void CMainWindow::createUi()
{
    m_pTopDisPlayWidget = new QLabel(this);

    QPalette label_palette;
    label_palette.setColor(QPalette::Background, QColor(180, 225, 229));
    m_pTopDisPlayWidget->setAutoFillBackground(true);
    m_pTopDisPlayWidget->setPalette(label_palette);
    //m_pTopDisPlayWidget->setStyleSheet("QLabel{"
    //    "border-image:url(:/BuddyList/Resources/headlabel.png) 4 4 4 4 stretch stretch;"
    //    "}");

    m_pHeadPhotoBtn = new QF::CPushButton(ID_HEAD_IMAGE_BTN, this);
    m_pHeadPhotoBtn->setCursor(QCursor(Qt::PointingHandCursor));
    m_pHeadPhotoBtn->setFixedSize(70, 70);
    m_pHeadPhotoBtn->setImageKey("head1.png");
    m_pHeadPhotoBtn->setMask(QRegion(0, 0, 70, 70, QRegion::Ellipse));

    m_pUserInfoName = new QLabel(this);
    m_pUserInfoSign = new QLabel(this);
    m_pSeekWidget = new QLineEdit(this);
    m_pSeekWidget->setStyleSheet("background-color: rgba(255, 255, 255, 30%); border-width:0;border-style:outset");
    {
        m_pUserInfoName->setText(QString::fromStdString(CConfig::instance()->nickName()));
        m_pUserInfoSign->setText("风雨同舟");
    }

    m_pMessageListBtn = new QF::CPushButton(ID_MESSAGE_LIST_BTN, this);
    m_pMessageListBtn->setText("消息列表");

    m_pContackPersionBtn = new QF::CPushButton(ID_CONTACK_PERSSION_BTN, this);
    m_pContackPersionBtn->setText("联系人");

    m_pGroupsBtn = new QF::CPushButton(ID_GROUPS_BTN, this);
    m_pGroupsBtn->setText("群组");

    m_pBuddyListWidget = new CBuddyListWidget(this);
}

void CMainWindow::slotEmitAddFirend()
{
    if (NULL == m_pAddFriendDialog)
    {
        m_pAddFriendDialog = new CQueryForAddDialog(this);
    }
    m_pAddFriendDialog->exec();

}

void CMainWindow::slotRefreshFriendList()
{
    const PC::CBuddyList& buddyList = CUserManager::instance()->getFirendList();
    if (NULL != m_pBuddyListWidget)
    {
        m_pBuddyListWidget->updateUi(buddyList);
    }
}

void CMainWindow::slotDoRefreshFriendList()
{
    CUserManager::instance()->queryFirendList();
}

void CMainWindow::slotHandleCacheChatMsg(const CBuddyMessagePtr& pData)
{
    m_pSystemIcon->setIcon(QIcon(*TT_PIXMAP("msg_16")));
    //{
    //    PC::CBuddyInfo* pUser = CUserManager::instance()->getBuddyInfoById(pData->m_nSendId);
    //    if (NULL == pUser)
    //    {
    //        if (NULL == m_pChatWindow)
    //        {
    //            m_pChatWindow = new CChatMainWindowDialog(this);
    //        }

    //        UC::CUserDataInfo user;
    //        user.m_strName = pUser->m_strNickName;
    //        user.m_strSign = pUser->m_strSign;
    //        user.m_nTargetId = pUser->m_uUserID;

    //        m_pChatWindow->addBuddyChatWindow(user);
    //    }
    //}
}

void CMainWindow::resizeEvent(QResizeEvent *e)
{
    const QSize& sz = e->size();
    m_pTopDisPlayWidget->setGeometry(0, 0, sz.width(), 135);
    m_pHeadPhotoBtn->move(10, 20);
    m_pUserInfoName->move(15 + m_pHeadPhotoBtn->width() + 5, 20);
    m_pUserInfoSign->move(15 + m_pHeadPhotoBtn->width() + 5, 20 + m_pUserInfoName->height());

    m_pSeekWidget->setGeometry(0, 100, sz.width(), 35);

    m_pMessageListBtn->setGeometry(1, 135, sz.width() / 3, 40);
    m_pContackPersionBtn->setGeometry(m_pMessageListBtn->x() + m_pMessageListBtn->width(), 135, m_pMessageListBtn->width(), 40);
    m_pGroupsBtn->setGeometry(m_pContackPersionBtn->x() + m_pContackPersionBtn->width(), 135, sz.width() - m_pMessageListBtn->width()*2, 40);

    m_pBuddyListWidget->setGeometry(0, 175, sz.width(), sz.height() - ui.statusbar->height() - 175);

}

void CMainWindow::onOperateFriends(const std::string& req)
{
    emit sigOnAddFirendCB(req);
}

void CMainWindow::slotOnAddFirendCB(const std::string& param)
{
    net::COperateFriendResultPtr pAddFriendInfo = boost::make_shared<net::COperateFriendResult>();
    pAddFriendInfo->decodePackage(param);

    //别人加自己
    if (pAddFriendInfo->m_uCmd == protocol::Apply)
    {
        std::wstring titleL = L"加好友请求";
        QString title = QString::fromStdWString(titleL);

        QString msg = QString(" %1 请求加您为好友,  是否同意").arg(pAddFriendInfo->m_szAccountName);

        CConfirmAddFriendDG *pDialog = new CConfirmAddFriendDG(this);
        pDialog->setWindowTitle(title);
        pDialog->setInfoMsg(msg);
        int nRet = pDialog->exec();
        {
            net::COperateFriendRequestPtr pData = boost::make_shared<net::COperateFriendRequest>();
            pData->m_uCmd = (nRet == QDialog::Accepted) ? protocol::Agree : protocol::Refuse;
            pData->m_uAccountID = pAddFriendInfo->m_uAccountID;

            CFlamingoClientCenter::instance()->request_async(pData, std::bind(&CMainWindow::onOperateFriends, this, std::placeholders::_1));
            pDialog->deleteLater();
        }
    }
    else if (pAddFriendInfo->m_uCmd == protocol::Refuse)
    {
        std::wstring titleL = L"拒绝好友请求";
        QString title = QString::fromStdWString(titleL);

        QString msg = QString(" %1 拒绝了加好友请求").arg(pAddFriendInfo->m_szAccountName);
        CConfirmAddFriendDG *pDialog = new CConfirmAddFriendDG(this);
        pDialog->setWindowTitle(title);
        pDialog->setInfoMsg(msg);
        pDialog->exec();
        pDialog->deleteLater();
    }
    else if (pAddFriendInfo->m_uCmd == protocol::Agree)
    {
        std::wstring titleL = L"成功加好友";
        QString title = QString::fromStdWString(titleL);

        QString msg = QString(" 您和 %1 已经是好友啦，开始聊天吧").arg(pAddFriendInfo->m_szAccountName);
        CConfirmAddFriendDG *pDialog = new CConfirmAddFriendDG(this);
        pDialog->setWindowTitle(title);
        pDialog->setInfoMsg(msg);
        pDialog->exec();
        pDialog->deleteLater();

        CUserManager::instance()->queryFirendList();
    }
}

void CMainWindow::slotIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Context:
    {
        //close app 鼠标右键
        break;
    }
    case QSystemTrayIcon::Trigger:
    {
        //鼠标左键

        break;
    }
    default:
        break;
    }
}

void CMainWindow::slotTestMsg(const net::CBuddyMessagePtr&)
{

}
