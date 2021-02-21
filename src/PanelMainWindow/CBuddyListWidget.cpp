#include "CBuddyListWidget.h"
#include "CBuddyItem.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QMouseEvent>
#include <utils/commonFunc.h>
#include <PanelChatWindow/CChatMainWindowDialog.h>
#include <PanelChatWindow/UserDataInfo.h>
#include <ProtocolData/rpc_structs.h>
#include <ProtocolData/rpc_Enum.h>
#include <user/CFlamingoClientCenter.h>
#include <user/CUserManager.h>

CBuddyListWidget::CBuddyListWidget(QWidget *parent /*= 0*/)
    :QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    initMenu();
}

void CBuddyListWidget::initMenu()
{
    m_pBlankMenu = new QMenu(this);
    m_pGroupMenu = new QMenu(this);
    m_pPersonMenu = new QMenu(this);
    m_pGroupNameEdit = new QLineEdit(this);

    QAction *addGroup = new QAction("添加分组", this);
    QAction *refreshList = new QAction("刷新好友列表", this);

    QAction *delGroup = new QAction("删除该组", this);
    QAction *rename = new QAction("重命名", this);
    QAction *delBuddy = new QAction("删除好友", this);

    m_pGroupNameEdit->setParent(this);  
    m_pGroupNameEdit->hide(); 
    m_pGroupNameEdit->setPlaceholderText("未命名");

    m_pBlankMenu->addAction(addGroup);
    m_pBlankMenu->addAction(refreshList);

    m_pGroupMenu->addAction(delGroup);
    m_pGroupMenu->addAction(rename);

    m_pPersonMenu->addAction(delBuddy);
    connect(m_pGroupNameEdit, SIGNAL(editingFinished()), this, SLOT(slotRenameEditFshed()));
    connect(addGroup, SIGNAL(triggered()), this, SLOT(slotAddGroup()));
    connect(delGroup, SIGNAL(triggered()), this, SLOT(slotDelGroup()));
    connect(rename, SIGNAL(triggered()), this, SLOT(slotRename()));
    connect(delBuddy, SIGNAL(triggered()), this, SLOT(slotDelBuddy()));
    connect(refreshList, SIGNAL(triggered()), this, SLOT(slotRefreshBuddyList()));
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotShowTalkWindow(QListWidgetItem*)));
}

void CBuddyListWidget::clearUi()
{
    foreach(QListWidgetItem* item, m_groupMap.keys())
    {
        m_groupMap.remove(item);
        delete item;
        item = NULL;
    }

    m_isHideMap.clear();

    m_pCurrentItem = NULL;
}

void CBuddyListWidget::updateUi(const PC::CBuddyList& pData)
{
    clearUi();
    for (const auto & iter : pData.m_arrBuddyTeamInfo)
    {
        QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/BuddyList/Resources/arrowRight.png"), QString::fromStdString(iter->m_strName));    //创建一个Item  
        newItem->setSizeHint(QSize(this->width(), 25));  
        this->addItem(newItem);         
        m_groupMap.insert(newItem, newItem);
        m_isHideMap.insert(newItem, false);  
        m_pCurrentItem = newItem;     
        for (const auto& subIter : iter->m_arrBuddyInfo)
        {
            CBuddyItem *buddy = new CBuddyItem(this);   
            buddy->m_pHeadPath = ":/BuddyList/Resources/c";                          
            buddy->m_pName->setText(QString::fromStdString(subIter->m_strNickName));                   
            buddy->m_pSign->setText(QString::fromStdString(subIter->m_strSign));
            buddy->m_nId = subIter->m_uUserID;

            QList<QListWidgetItem*> tem = m_groupMap.keys(m_pCurrentItem);  
            QListWidgetItem *newItem = new QListWidgetItem(this); 
            
            this->insertItem(row(m_pCurrentItem) + tem.count(), newItem);  
            this->setItemWidget(newItem, buddy); 

            m_groupMap.insert(newItem, m_pCurrentItem);   
            if (m_isHideMap.value(m_pCurrentItem))         
                newItem->setHidden(true);
            else                                       
                newItem->setHidden(false);
        }
    }
}

void CBuddyListWidget::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event); 
    if (m_pGroupNameEdit->isVisible() && !(m_pGroupNameEdit->rect().contains(event->pos())))
    {
        if (m_pGroupNameEdit->text() != NULL)
            m_pCurrentItem->setText(m_pGroupNameEdit->text());
        m_pGroupNameEdit->hide();
    }
    m_pCurrentItem = this->itemAt(mapFromGlobal(QCursor::pos()));
    m_currentText = m_pCurrentItem != NULL ? m_pCurrentItem->text() : "";
    if (event->button() == Qt::LeftButton && m_pCurrentItem != NULL && m_pCurrentItem == m_groupMap.value(m_pCurrentItem))
    {
        if (m_isHideMap.value(m_pCurrentItem))                                    
        {
            foreach(QListWidgetItem* subItem, m_groupMap.keys(m_pCurrentItem))  
                if (subItem != m_pCurrentItem)                                 
                {
                    subItem->setHidden(false);                            
                }
            m_isHideMap.insert(m_pCurrentItem, false);                            
            m_pCurrentItem->setIcon(QIcon(":/BuddyList/Resources/arrowDown.png"));
        }
        else                                                             
        {
            foreach(QListWidgetItem* subItem, m_groupMap.keys(m_pCurrentItem))
                if (subItem != m_pCurrentItem)                                 
                {
                    subItem->setHidden(true);                           
                }
            m_isHideMap.insert(m_pCurrentItem, true);                          
            m_pCurrentItem->setIcon(QIcon(":/BuddyList/Resources/arrowRight.png"));
        }
    }
}

void CBuddyListWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QListWidget::contextMenuEvent(event);           
    if (m_pCurrentItem == NULL)                           
    {
        m_pBlankMenu->exec(QCursor::pos());
        return;
    }
    if (m_pCurrentItem == m_groupMap.value(m_pCurrentItem))    
        m_pGroupMenu->exec(QCursor::pos());
    else                                           
        m_pPersonMenu->exec(QCursor::pos());
}

void CBuddyListWidget::slotAddGroup()
 {
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/BuddyList/Resources/arrowRight.png"), "未命名哈哈");    
    newItem->setSizeHint(QSize(this->width(), 25));
    this->addItem(newItem);         
    m_groupMap.insert(newItem, newItem);
    m_pGroupNameEdit->raise();
    m_pGroupNameEdit->setText(tr("未命名")); 
    m_pGroupNameEdit->selectAll();        
    m_pGroupNameEdit->setGeometry(this->visualItemRect(newItem).left() + 15, this->visualItemRect(newItem).top() + 1, this->visualItemRect(newItem).width(), this->visualItemRect(newItem).height() - 2);
    m_pGroupNameEdit->show();              
    m_pGroupNameEdit->setFocus();          
    m_pCurrentItem = newItem;    
}

void CBuddyListWidget::slotDelGroup()
{
    net::CUpdateTeamInfoRequestPtr pData = boost::make_shared<net::CUpdateTeamInfoRequest>();
    pData->m_opType = protocol::updateteaminfo_operation_delete;
    pData->m_strOldTeamName = utils::qToStdWString(m_pCurrentItem->text());

    CFlamingoClientCenter::instance()->request_async(pData);
}

void CBuddyListWidget::slotDelBuddy()
{
    m_groupMap.remove(m_pCurrentItem);
    delete m_pCurrentItem;           
}

void CBuddyListWidget::slotRename()
{
    m_pGroupNameEdit->raise();
    m_pGroupNameEdit->setGeometry(this->visualItemRect(m_pCurrentItem).left() + 15, this->visualItemRect(m_pCurrentItem).top() + 1, this->visualItemRect(m_pCurrentItem).width(), this->visualItemRect(m_pCurrentItem).height() - 2);//出现的位置  
    m_pGroupNameEdit->setText(m_pCurrentItem->text());   

    m_pGroupNameEdit->show();                        
    m_pGroupNameEdit->selectAll();                   
    m_pGroupNameEdit->setFocus();    
}

void CBuddyListWidget::slotRenameEditFshed()
{
    net::CUpdateTeamInfoRequestPtr pData = boost::make_shared<net::CUpdateTeamInfoRequest>();
    if (m_isHideMap.find(m_pCurrentItem) != m_isHideMap.end())
    {
        pData->m_opType = protocol::updateteaminfo_operation_modify;
        pData->m_strOldTeamName = utils::qToStdWString(m_currentText);
        pData->m_strNewTeamName = utils::qToStdWString(m_pGroupNameEdit->text());
    }
    else
    {
        pData->m_opType = protocol::updateteaminfo_operation_add;
        pData->m_strNewTeamName = utils::qToStdWString(m_pGroupNameEdit->text());
    }

    CFlamingoClientCenter::instance()->request_async(pData);
}

void CBuddyListWidget::slotRefreshBuddyList()
{
    CUserManager::instance()->queryFirendList();
}

void CBuddyListWidget::slotShowTalkWindow(QListWidgetItem* item)
{
    //if (NULL == m_pChatWindow)
    //{
    //    m_pChatWindow = new CChatMainWindowDialog(this);
    //}

    CBuddyItem *buddy = dynamic_cast<CBuddyItem *>(itemWidget(item));
    if (NULL != buddy)
    {
        UC::CUserDataInfoPtr user(new UC::CUserDataInfo);
        user->m_strName = buddy->m_pName->text().toStdString();
        user->m_strSign = buddy->m_pSign->text().toStdString();
        user->m_nTargetId = buddy->m_nId;

        emit sigAddChatUser(user);
        //if (NULL != buddy)
        //{
        //    m_pChatWindow->addBuddyChatWindow(user);
        //}

        //m_pChatWindow->show();
    }


}
