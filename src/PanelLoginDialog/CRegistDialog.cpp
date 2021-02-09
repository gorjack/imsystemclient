#include "CRegistDialog.h"
#include <User/CFlamingoClientCenter.h>
#include <ProtocolData/rpc_structs.h>
#include <ProtocolData/rpc_proEnum.h>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <utils/commonFunc.h>

CRegistDialog::CRegistDialog(QWidget *parent)
    : QDialog(parent)
{
    //ui.setupUi(this);
    createUi();
    connect(m_pRegistBtn, SIGNAL(clicked()), this, SLOT(slotRegistReq()));
    connect(CFlamingoClientCenter::instance(), SIGNAL(sigStatus(int, QString)), this, SLOT(slotStatus(int, QString)));
}

void CRegistDialog::createUi()
{
    setFixedSize(450, 320);

    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    pVLayout->setMargin(0);
    pVLayout->setSpacing(0);

    auto createSingleUi = [&](const QString& label, QLineEdit *& pLineEdit)
    {
        QHBoxLayout *pHLayout = new QHBoxLayout;
        pHLayout->setMargin(10);
        pHLayout->setSpacing(10);
        pHLayout->addStretch(1);

        QLabel *pLabel = new QLabel(label);
        pLabel->setFixedSize(70, 30);
        pHLayout->addWidget(pLabel);

        pLineEdit = new QLineEdit;
        pLineEdit->setFixedSize(210, 30);
        pHLayout->addWidget(pLineEdit);
        pHLayout->addStretch(1);

        pVLayout->addLayout(pHLayout);
    };

    createSingleUi(QString::fromLocal8Bit("账号ID:"), m_pAccountId);
    createSingleUi(QString::fromLocal8Bit("账号昵称:"), m_pNickName);
    createSingleUi(QString::fromLocal8Bit("账号密码:"), m_pPasswd);
    createSingleUi(QString::fromLocal8Bit("确认密码:"), m_pConfirmPasswd);

    {
        QHBoxLayout *pHLayout = new QHBoxLayout;
        pHLayout->setMargin(10);
        pHLayout->setSpacing(10);

        m_pRegistBtn = new QPushButton;
        m_pRegistBtn->setText(QString::fromLocal8Bit("注       册"));
        m_pRegistBtn->setFixedSize(150, 36);
        //pHLayout->addStretch(1);

        pHLayout->addWidget(m_pRegistBtn, Qt::AlignHCenter);
        //pHLayout->addStretch(1);

        pVLayout->addLayout(pHLayout);
    }

    setLayout(pVLayout);
}

void CRegistDialog::slotRegistReq()
{
    QString pAccountId = m_pAccountId->text();
    QString pNickName = m_pNickName->text();
    QString passWd = m_pPasswd->text();
    QString passConfirmWd = m_pConfirmPasswd->text();

    if (passWd != passConfirmWd)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("两次输入密码不一致"));
        return;
    }

    net::CRegisterRequest req;
    req.m_szAccountName = utils::qsToS(pAccountId);
    req.m_szNickName = utils::qsToS(pNickName);
    req.m_szPassword = utils::qsToS(passWd);
    CFlamingoClientCenter::instance()->regist_async(req);
}

void CRegistDialog::slotStatus(int status, QString msg)
{
    if (status == protocol::REGISTER_EXIST)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("您注册的手机号已经被注册, 建议更换号码"));
    }
    else if (status == protocol::REGISTER_SUCCESS)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("恭喜您，注册成功"));
        close();
    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网络故障，注册失败，请稍后重试！"));
        close();
    }
}
