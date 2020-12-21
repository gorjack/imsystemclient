#include "CRegistDialog.h"
#include <User/CFlamingoClientCenter.h>
#include <ProtocolData/rpc_structs.h>
#include <ProtocolData/rpc_proEnum.h>
#include <QtWidgets/QMessageBox>

CRegistDialog::CRegistDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.m_pRegistBtn, SIGNAL(clicked()), this, SLOT(slotRegistReq()));
    connect(CFlamingoClientCenter::instance(), SIGNAL(sigStatus(int, QString)), this, SLOT(slotStatus(int, QString)));

}

void CRegistDialog::slotRegistReq()
{
    QString pAccountId = ui.m_pAccountId->displayText();
    QString pNickName = ui.m_pNickName->displayText();
    QString passWd = ui.m_pPassWd->displayText();

    net::CRegisterRequest req(pAccountId.toLatin1(), pNickName.toLatin1(), passWd.toLatin1());
    CFlamingoClientCenter::instance()->regist_async(req);
    //net::CRegisterResult* pRegisterResult = const_cast<net::CRegisterResult*>(CFlamingoClientCenter::instance()->regist_async(req));


    //using namespace protocol;
    //long nRegisterResult = pRegisterResult->m_nResultCode;
    //if (nRegisterResult == REGISTER_EXIST)
    //{
    //    QMessageBox::information(this, "提示", "您注册的手机号已经被注册, 建议更换号码");
    //}
    //else if (nRegisterResult == REGISTER_SUCCESS)
    //{
    //    QMessageBox::information(this, "提示", "恭喜您，注册成功");
    //}
    //else
    //    QMessageBox::information(this, "提示", "网络故障，注册失败，请稍后重试！");

}

void CRegistDialog::slotStatus(int status, QString msg)
{
    if (status == protocol::REGISTER_EXIST)
    {
        QMessageBox::information(this, "提示", "您注册的手机号已经被注册, 建议更换号码");
    }
    else if (status == protocol::REGISTER_SUCCESS)
    {
        QMessageBox::information(this, "提示", "恭喜您，注册成功");
    }
    else
        QMessageBox::information(this, "提示", "网络故障，注册失败，请稍后重试！");
}
