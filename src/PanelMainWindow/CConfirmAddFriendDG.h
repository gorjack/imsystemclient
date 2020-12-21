#pragma once

#include <QtWidgets/QDialog>
#include "./GeneratedFiles/ui_ConfirmAddFriendDG.h"

class PANELMAINWINDOW_EXPORT CConfirmAddFriendDG : public QDialog
{
    Q_OBJECT

public:
    CConfirmAddFriendDG(QWidget *parent = Q_NULLPTR);

    void setAddFriendMsg(const QString& msg);
    void setAccountId(unsigned int id) { m_uAccountId = id; }
protected Q_SLOTS:
    void slotAgree();
    void slotReject();

private:
    Ui::ConfirmAddFriendDG   ui;
    unsigned int             m_uAccountId = -1;
};
