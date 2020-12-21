#include "CChatMainWindowDialog.h"
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QHBoxLayout>
#include "CSplitContainer.h"
#include "CUserDataWidgetItem.h"
#include <QPainter>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>

CChatMainWindowDialog::CChatMainWindowDialog(QWidget *parent /*= nullptr*/)
    : QDialog(parent)
{
    //Qt::WindowFlags windowFlags = Qt::WindowMinimizeButtonHint;
    //windowFlags |= Qt::WindowMaximizeButtonHint;
    //windowFlags |= Qt::WindowCloseButtonHint;

    //setWindowFlags(windowFlags);

    createUi();
    resize(1265, 725);
    connect(m_pUserDataList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotShowCurrentWindow(QListWidgetItem*)));
}

void CChatMainWindowDialog::addBuddyChatWindow(const UC::CUserDataInfo& user)
{
    CChatMessageWindowWidget* pBuddy = new CChatMessageWindowWidget(this);
    pBuddy->setTargetId(user.m_nTargetId);
    int nIndex = m_pStackWidget->addWidget(pBuddy);

    CUserDataWidgetItem* pUser = new CUserDataWidgetItem(this);
    connect(pUser, SIGNAL(sigClose()), this, SLOT(slotClose()));
    pUser->setMessageText(QString::fromStdString(user.m_strName));
    pUser->setHeadIcon(":/QQChatMessage/Resources/right.png");

    QListWidgetItem *pItem = new QListWidgetItem(m_pUserDataList);
    pItem->setSizeHint(QSize(m_pUserDataList->width() - 20, 60));
    m_pUserDataList->setItemWidget(pItem, pUser);

    m_mapIndex2BuddyWindow.insert(pItem, pBuddy);
    m_pUserDataList->setCurrentRow(m_pUserDataList->count() - 1);
}

void CChatMainWindowDialog::slotClose()
{
    QListWidgetItem *pItem = m_pUserDataList->currentItem();
    int nIndex = m_pUserDataList->currentRow();

    CUserDataWidgetItem* pUser = dynamic_cast<CUserDataWidgetItem*>(m_pUserDataList->itemWidget(pItem));
    if (NULL != pUser)
    {
        pUser->deleteLater();
    }

    CChatMessageWindowWidget *pWindow = m_mapIndex2BuddyWindow.value(pItem);
    if (NULL != pWindow)
    {
        m_pStackWidget->removeWidget(pWindow);
        pWindow->deleteLater();
        m_mapIndex2BuddyWindow.remove(pItem);
    }
    m_pUserDataList->takeItem(m_pUserDataList->row(pItem));

    if (m_pUserDataList->count() <= 0)
    {
        close();
    }
}

void CChatMainWindowDialog::slotShowCurrentWindow(QListWidgetItem* nIndex)
{
    CChatMessageWindowWidget* pWindow = m_mapIndex2BuddyWindow.value(nIndex);
    if (pWindow != NULL)
    {
        m_pStackWidget->setCurrentWidget(pWindow);
    }
}

void CChatMainWindowDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    //painter.setBrush(QBrush(QImage(":/QQChatMessage/Resources/talkbg.png")));
    //painter.setBrush(QBrush(QColor(191, 255, 255)));

    painter.drawRect(rect());

    QDialog::paintEvent(event);
}

void CChatMainWindowDialog::createUi()
{
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->setSpacing(0);

    m_pStackWidget = new QStackedWidget(this);

    m_pSplit = new XP::CSplitContainer(Qt::Horizontal, 1, this);
    m_pUserDataList = new QListWidget(this);
    //m_pUserDataList->setStyleSheet("background-color: rgba(255, 255, 255, 40%); border-top-width:1px;border-top-color:rgb(128,128,128);border-right-width:1px;border-right-color:rgb(195,195,195);border-style:outset");
    //background-color: transparent; 
    m_pUserDataList->setStyleSheet("border-top-width:1px;border-top-color:rgb(128,128,128);border-right-width:1px;border-right-color:rgb(195,195,195);border-style:outset");

    m_pSplit->setWidgets(m_pUserDataList, m_pStackWidget, true, 210);
    m_pSplit->setFirstMinLength(210);

    m_pRightWidget = new CShowRightWidget(this);

    pLayout->addWidget(m_pSplit);
    pLayout->addWidget(m_pRightWidget);

    setLayout(pLayout);
}

CShowRightWidget::CShowRightWidget(QWidget*parent /*= NULL*/)
    :QWidget(parent)
{
    createUi();
    setMaximumWidth(280);
}

void CShowRightWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void CShowRightWidget::createUi()
{
    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->setContentsMargins(0, 2, 0, 0);
    pLayout->setSpacing(0);

    m_pTitleWidget = new QLabel(this);
    m_pTitleWidget->setText("消息记录");
    m_pTitleWidget->setStyleSheet("border:1px solid green;");
    m_pTitleWidget->setFixedSize(100, 30);

    m_pContent = new QListView(this);
   // m_pContent->setStyleSheet("background-color: rgba(255, 255, 255, 30%);");

    pLayout->addWidget(m_pTitleWidget);
    pLayout->addWidget(m_pContent);

    setLayout(pLayout);
}
