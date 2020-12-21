#pragma once
#include <QtWidgets/QMainWindow>
#include "./GeneratedFiles/ui_MainWindow.h"


class CQueryForAddDialog;
class CBuddyListWidget;
class QLabel;
namespace QF
{
    class CPushButton;
}

class PANELMAINWINDOW_EXPORT CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    CMainWindow(QWidget *parent = Q_NULLPTR);
    void createUi();
protected Q_SLOTS:
    void slotEmitAddFirend();
    void slotRefreshFriendList();
    void slotDoRefreshFriendList();

protected:
    void resizeEvent(QResizeEvent *e);
private:
    Ui::MainWindow ui;

    QLabel                       *m_pTopDisPlayWidget;
    QF::CPushButton                  *m_pHeadPhotoBtn;
    QLabel                       *m_pUserInfoName;
    QLabel                       *m_pUserInfoSign;
    QLineEdit                    *m_pSeekWidget;


    QF::CPushButton                  *m_pMessageListBtn;
    QF::CPushButton                  *m_pContackPersionBtn;
    QF::CPushButton                  *m_pGroupsBtn;

    CQueryForAddDialog           *m_pAddFriendDialog = NULL;
    CBuddyListWidget             *m_pBuddyListWidget = NULL;
};
