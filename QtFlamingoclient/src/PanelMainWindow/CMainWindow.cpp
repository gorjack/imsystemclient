#include "CMainWindow.h"
#include <User/CFlamingoClientCenter.h>
#include <User/CUserManager.h>
#include <CQueryForAddDialog.h>
#include "CBuddyListWidget.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtGui/QtEvents>
#include <PanelBaseWidget/CPushButton.h>

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
    resize(430, 835);
    ui.statusbar->addPermanentWidget(ui.m_pAddFriend);
    connect(ui.m_pAddFriend, SIGNAL(clicked()), this, SLOT(slotEmitAddFirend()));
    connect(CUserManager::instance(), SIGNAL(sigFinishGetFriendListReq()), this, SLOT(slotRefreshFriendList()));

    m_pAddFriendDialog = new CQueryForAddDialog(this);

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
        m_pHeadPhotoBtn->setText("123333");
        m_pUserInfoName->setText("jeckma");
        m_pUserInfoSign->setText("alibaba");
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
