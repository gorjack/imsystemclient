#include "CRegistDialog.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include "utils/commonFunc.h"

CRegistDialog::CRegistDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.okBtn, SIGNAL(clicked()), this, SLOT(slotRegistReq()));
    connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancel()));
}

void CRegistDialog::slotRegistReq()
{
    QString pAccountId = ui.accountId->text();
    QString pNickName = ui.nickName->text();
    QString passWd = ui.passWd->text();
    QString passConfirmWd = ui.confirmPassWd->text();

    if (passWd != passConfirmWd)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("两次输入密码不一致"));
        return;
    }

	net::CRegisterRequest req;
    m_registerData.m_szAccountName = utils::qsToS(pAccountId);
    m_registerData.m_szNickName = utils::qsToS(pNickName);
    m_registerData.m_szPassword = utils::qsToS(passWd);
    done(QDialog::Accepted);
}

void CRegistDialog::slotCancel()
{
    done(QDialog::Rejected);
}
