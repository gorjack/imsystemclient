#pragma once

#include <QtWidgets/QDialog>
#include "ProtocolData/rpc_structs.h"
#include "ui_CRegistDialog.h"

using namespace net;

class QLineEdit;
class CRegisterReques;
class CRegistDialog : public QDialog
{
    Q_OBJECT

public:
    CRegistDialog(QWidget *parent = Q_NULLPTR);

    const CRegisterRequest& getRegistData() { return m_registerData; }

protected Q_SLOTS:
    void slotRegistReq();
    void slotCancel();

private:

    Ui::CRegistDialog ui;

    CRegisterRequest m_registerData;
};
