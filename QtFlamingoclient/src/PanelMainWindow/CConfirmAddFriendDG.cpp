#include "CConfirmAddFriendDG.h"


CConfirmAddFriendDG::CConfirmAddFriendDG(QWidget *parent /*= Q_NULLPTR*/)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.m_pAgreeBtn, SIGNAL(clicked()), this, SLOT(slotAgree()));
    connect(ui.m_pRejectBtn, SIGNAL(clicked()), this, SLOT(slotReject()));

}

void CConfirmAddFriendDG::setAddFriendMsg(const QString& msg)
{
    ui.m_pShowAddFriendMsg->setText(msg);
}

void CConfirmAddFriendDG::slotAgree()
{
    accept();

}

void CConfirmAddFriendDG::slotReject()
{
    reject();
}
