#pragma once

#include <QtWidgets/QDialog>
#include "ui_CRegistDialog.h"

class QLineEdit;
class CRegistDialog : public QDialog
{
    Q_OBJECT

public:
    CRegistDialog(QWidget *parent = Q_NULLPTR);
    void createUi();

protected Q_SLOTS:
    void slotRegistReq();
    void slotStatus(int, QString);

private:

    //Ui::CRegistDialog ui;
    QLineEdit            *m_pAccountId = NULL;
    QLineEdit            *m_pNickName = NULL;
    QLineEdit            *m_pPasswd = NULL;
    QLineEdit            *m_pConfirmPasswd = NULL;
    QPushButton          *m_pRegistBtn = NULL;
};
