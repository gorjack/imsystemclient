#pragma once

#include <QtWidgets/QDialog>
#include "ui_CRegistDialog.h"

class CRegistDialog : public QDialog
{
    Q_OBJECT

public:
    CRegistDialog(QWidget *parent = Q_NULLPTR);

protected Q_SLOTS:
    void slotRegistReq();
    void slotStatus(int, QString);

private:

    Ui::CRegistDialog ui;
};
