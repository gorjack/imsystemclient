#pragma once
#include <QtWidgets/QListWidget>
#include <User/CUserBusinessCenter.h>
#include <QtWidgets/QLineEdit>

class CChatMainWindowDialog;
class CBuddyListWidget : public QListWidget 
{
    Q_OBJECT
public:
    explicit CBuddyListWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent*);
    void initMenu(); 

    void updateUi(const PC::CBuddyList& pData);
public slots:
    void slotAddGroup();  
    void slotDelGroup();  
    void slotDelBuddy();  
    void slotRename();    
    void slotRenameEditFshed();
    void slotRefreshBuddyList();

    void slotShowTalkWindow(QListWidgetItem* item);

protected:
    void clearUi();

private:
    QMap<QListWidgetItem*, QListWidgetItem*>         m_groupMap;   
    QMap<QListWidgetItem*, bool>                     m_isHideMap;
    QLineEdit                                       *m_pGroupNameEdit = NULL;
    QListWidgetItem                                 *m_pCurrentItem = NULL;
    CChatMainWindowDialog                           *m_pChatWindow = NULL;
    QMenu                                           *m_pBlankMenu = NULL;
    QMenu                                           *m_pGroupMenu = NULL;
    QMenu                                           *m_pPersonMenu;

    QString                                          m_currentText;
};