#pragma once

#include <QtWidgets/QDialog>
#include "./GeneratedFiles/ui_AddFriendDialog.h"

class CConfirmAddFriendDG;
class PANELMAINWINDOW_EXPORT CQueryForAddDialog : public QDialog
{
    Q_OBJECT

public:
    CQueryForAddDialog(QWidget *parent = Q_NULLPTR);

    void addFirend(unsigned int uAccountToAdd);
    void onAddFirend(const std::string& req);

Q_SIGNALS:
    void sigOnFindFirendCallBack();
    void sigOnAddFirendCB();

protected Q_SLOTS:
    void slotFindFriend();
    void slotOnFindFirendCallBack();
    void slotOnAddFirendCB();


private:
    void onHandleFindFirend(const std::string& req);

private:
    Ui::AddFriendDialog ui;
    std::string            m_strBuffer;
    CConfirmAddFriendDG    *m_pConfirmAddFriendDG;
};
