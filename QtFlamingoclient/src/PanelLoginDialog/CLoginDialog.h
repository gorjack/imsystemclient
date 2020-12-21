#pragma once

#include <QtWidgets/QDialog>
#include "./GeneratedFiles/ui_CLoginDialog.h"

class CRegistDialog;
class CMainWindow;
class PANELLOGINDIALOG_EXPORT CLoginDialog : public QDialog
{
    Q_OBJECT

public:
    CLoginDialog(QWidget *parent = Q_NULLPTR);

protected Q_SLOTS:
    void slotEmitRegistDialog();
    void slotEmitLoginDialog();


private:
    Ui::CLoginDialogClass ui;
    CRegistDialog         *m_pRegistDialog = NULL;
    CMainWindow           *m_pMainWindow = NULL;
};
