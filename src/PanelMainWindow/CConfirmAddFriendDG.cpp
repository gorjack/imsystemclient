#include "CConfirmAddFriendDG.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>

CConfirmAddFriendDG::CConfirmAddFriendDG(QWidget *parent /*= Q_NULLPTR*/)
    : QDialog(parent)
{
   // ui.setupUi(this);
    createUi();
    connect(m_pAgreeBtn, SIGNAL(clicked()), this, SLOT(slotAgree()));
    connect(m_pRejectBtn, SIGNAL(clicked()), this, SLOT(slotReject()));
}

void CConfirmAddFriendDG::setInfoMsg(const QString& msg)
{
    if (NULL != m_pInfoMsg)
    {
        QFontMetrics metric(font());
        int nWidth = metric.width(msg);
        m_pInfoMsg->setText(msg);
        m_pInfoMsg->setFixedWidth(nWidth);
    }
}

void CConfirmAddFriendDG::slotAgree()
{
    accept();
}

void CConfirmAddFriendDG::slotReject()
{
    reject();
}

void CConfirmAddFriendDG::createUi()
{
    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->setMargin(0);
    pVLayout->setSpacing(0);

    {
        QHBoxLayout *pHLayout = new QHBoxLayout;
        pHLayout->setMargin(10);
        pHLayout->setSpacing(10);

        m_pInfoMsg = new QLabel;
        m_pInfoMsg->setFixedHeight(20);
        pHLayout->addWidget(m_pInfoMsg, Qt::AlignCenter);
        pVLayout->addLayout(pHLayout);
    }

    {
        QHBoxLayout *pHLayout = new QHBoxLayout;
        pHLayout->setMargin(10);
        pHLayout->setSpacing(10);

        m_pAgreeBtn = new QPushButton;
        m_pAgreeBtn->setFixedSize(70, 25);
        m_pAgreeBtn->setText(QString::fromLocal8Bit("Í¬Òâ"));
        pHLayout->addStretch(1);
        pHLayout->addWidget(m_pAgreeBtn);

        m_pRejectBtn = new QPushButton;
        m_pRejectBtn->setFixedSize(70, 25);
        m_pRejectBtn->setText(QString::fromLocal8Bit("¾Ü¾ø"));
        pHLayout->addStretch(1);
        pHLayout->addWidget(m_pRejectBtn);
        pVLayout->addLayout(pHLayout);
    }

    setLayout(pVLayout);
}
