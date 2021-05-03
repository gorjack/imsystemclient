#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>
#include "./GeneratedFiles/ui_MainWindow.h"
#include <ProtocolData/rpc_structs.h>
#include <PanelChatWindow/UserDataInfo.h>

using namespace net;


class CQueryForAddDialog;
class CBuddyListWidget;
class QLabel;
class QCustomFloatWidget;
class CChatMainWindowDialog;

namespace PC
{
    class CPushButton;
    class PANELMAINWINDOW_EXPORT CMainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        CMainWindow(QWidget *parent = Q_NULLPTR);
        void createUi();
        void onOperateFriends(const std::string& req);            //处理好友请求(加 删 请求添加等)


    protected Q_SLOTS:
        void slotEmitAddFirend();
        void slotRefreshFriendList();
        void slotDoRefreshFriendList();
        void slotHandleCacheChatMsg(net::CBuddyMessagePtr);

    protected:
        void resizeEvent(QResizeEvent *e);
        bool eventFilter(QObject *obj, QEvent *event);

    Q_SIGNALS:
        void sigOnAddFirendCB(const std::string&);

    protected Q_SLOTS:
        void slotOnAddFirendCB(const std::string&);
        void slotIconActivated(QSystemTrayIcon::ActivationReason reason);
        void slotAddChatUser(const UC::CUserDataInfoPtr&);

    private:
        Ui::MainWindow ui;

        QLabel                       *m_pTopDisPlayWidget;
        CPushButton              *m_pHeadPhotoBtn;
        QLabel                       *m_pUserInfoName;
        QLabel                       *m_pUserInfoSign;
        QLineEdit                    *m_pSeekWidget;


        CPushButton               *m_pMessageListBtn;
        CPushButton               *m_pContackPersionBtn;
        CPushButton               *m_pGroupsBtn;

        CQueryForAddDialog            *m_pAddFriendDialog = NULL;
        CBuddyListWidget              *m_pBuddyListWidget = NULL;
        QSystemTrayIcon               *m_pSystemIcon = NULL;
        QCustomFloatWidget            *m_pFloatMsgWidget = NULL;
        QString                        m_strCurrentSystemIcon = NULL;
        std::list<std::string>         m_strCacheMsg;

        CChatMainWindowDialog          *m_pChatWindow = NULL;
        net::CBuddyMessagePtr           m_pUserMessageData;
    };

}