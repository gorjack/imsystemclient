#include "CLoginDialog.h"
#include "CRegistDialog.h"
#include <PanelMainWindow/CMainWindow.h>
#include <User/CFlamingoClientCenter.h>
#include <ProtocolData/rpc_structs.h>
#include <ProtocolData/rpc_proEnum.h>
#include <ProtocolData/rpc_Enum.h>
#include <QtWidgets/QMessageBox>
#include <iostream>

CLoginDialog::CLoginDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.m_pRegistBtn, SIGNAL(clicked()), this, SLOT(slotEmitRegistDialog()));
    connect(ui.m_pLoginBtn, SIGNAL(clicked()), this, SLOT(slotEmitLoginDialog()));

}

void CLoginDialog::slotEmitRegistDialog()
{
    if (NULL == m_pRegistDialog)
    {
        m_pRegistDialog = new CRegistDialog(this);
    }

    m_pRegistDialog->exec();
}

void CLoginDialog::slotEmitLoginDialog()
{
    QString pAccountId = ui.m_userLineE->displayText();
    QString pNickName = ui.m_passWdLineE->displayText();

    net::CLoginRequest req(pAccountId.toLatin1(), pNickName.toLatin1(), 1, protocol::online_type_pc_online);
    net::CLoginResult* pLoginResult = CFlamingoClientCenter::instance()->login_async(req);


    long nLoginResultCode = pLoginResult->m_LoginResultCode;
    UINT uAccountID = pLoginResult->m_uAccountID;


    if (nLoginResultCode != protocol::LOGIN_SUCCESS)
    {
        QMessageBox::information(this, "ÌáÊ¾", "µÇÂ¼Ê§°Ü");
    }
    else
    {
        std::cout << "login success " << std::endl;
        if (NULL == m_pMainWindow)
        {
            m_pMainWindow = new CMainWindow(NULL);
        }

        std::cout << "mainwindow show start " << std::endl;

        m_pMainWindow->show();

        std::cout << "mainwindow show end " << std::endl;

        accept();
    }
}
