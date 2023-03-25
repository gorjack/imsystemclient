/********************************************************************************
** Form generated from reading UI file 'ConfirmAddFriendDG.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMADDFRIENDDG_H
#define UI_CONFIRMADDFRIENDDG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConfirmAddFriendDG
{
public:
    QLabel *m_pShowAddFriendMsg;
    QPushButton *m_pAgreeBtn;
    QPushButton *m_pRejectBtn;

    void setupUi(QDialog *ConfirmAddFriendDG)
    {
        if (ConfirmAddFriendDG->objectName().isEmpty())
            ConfirmAddFriendDG->setObjectName(QString::fromUtf8("ConfirmAddFriendDG"));
        ConfirmAddFriendDG->resize(549, 546);
        m_pShowAddFriendMsg = new QLabel(ConfirmAddFriendDG);
        m_pShowAddFriendMsg->setObjectName(QString::fromUtf8("m_pShowAddFriendMsg"));
        m_pShowAddFriendMsg->setGeometry(QRect(110, 100, 221, 81));
        m_pAgreeBtn = new QPushButton(ConfirmAddFriendDG);
        m_pAgreeBtn->setObjectName(QString::fromUtf8("m_pAgreeBtn"));
        m_pAgreeBtn->setGeometry(QRect(100, 310, 101, 51));
        m_pRejectBtn = new QPushButton(ConfirmAddFriendDG);
        m_pRejectBtn->setObjectName(QString::fromUtf8("m_pRejectBtn"));
        m_pRejectBtn->setGeometry(QRect(300, 310, 111, 51));

        retranslateUi(ConfirmAddFriendDG);

        QMetaObject::connectSlotsByName(ConfirmAddFriendDG);
    } // setupUi

    void retranslateUi(QDialog *ConfirmAddFriendDG)
    {
        ConfirmAddFriendDG->setWindowTitle(QCoreApplication::translate("ConfirmAddFriendDG", "Dialog", nullptr));
        m_pShowAddFriendMsg->setText(QString());
        m_pAgreeBtn->setText(QCoreApplication::translate("ConfirmAddFriendDG", "\345\220\214\346\204\217", nullptr));
        m_pRejectBtn->setText(QCoreApplication::translate("ConfirmAddFriendDG", "\346\213\222\347\273\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfirmAddFriendDG: public Ui_ConfirmAddFriendDG {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMADDFRIENDDG_H
