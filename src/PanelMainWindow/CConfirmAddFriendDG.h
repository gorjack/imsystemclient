#pragma once

#include <QtWidgets/QDialog>
#include "./GeneratedFiles/ui_ConfirmAddFriendDG.h"

class QPushButton;
class QLabel;
class PANELMAINWINDOW_EXPORT CConfirmAddFriendDG : public QDialog
{
    Q_OBJECT

public:
    CConfirmAddFriendDG(QWidget *parent = Q_NULLPTR);

    void setInfoMsg(const QString& msg);
    void setAccountId(unsigned int id) { m_uAccountId = id; }

protected Q_SLOTS:
    void slotAgree();
    void slotReject();

private:
    void createUi();

private:
    //Ui::ConfirmAddFriendDG   ui;
    QLabel                  *m_pInfoMsg = NULL;
    QPushButton             *m_pAgreeBtn = NULL;
    QPushButton             *m_pRejectBtn = NULL ;
    unsigned int             m_uAccountId = -1;
};
