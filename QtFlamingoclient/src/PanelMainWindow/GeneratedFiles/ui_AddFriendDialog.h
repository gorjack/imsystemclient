/********************************************************************************
** Form generated from reading UI file 'AddFriendDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIENDDIALOG_H
#define UI_ADDFRIENDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddFriendDialog
{
public:
    QLineEdit *m_pIdLineEdit;
    QLabel *label;
    QPushButton *m_pAddFirendBtn;
    QPushButton *m_pCancelBtn;

    void setupUi(QDialog *AddFriendDialog)
    {
        if (AddFriendDialog->objectName().isEmpty())
            AddFriendDialog->setObjectName(QStringLiteral("AddFriendDialog"));
        AddFriendDialog->resize(400, 300);
        m_pIdLineEdit = new QLineEdit(AddFriendDialog);
        m_pIdLineEdit->setObjectName(QStringLiteral("m_pIdLineEdit"));
        m_pIdLineEdit->setGeometry(QRect(190, 80, 141, 31));
        label = new QLabel(AddFriendDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 80, 131, 41));
        m_pAddFirendBtn = new QPushButton(AddFriendDialog);
        m_pAddFirendBtn->setObjectName(QStringLiteral("m_pAddFirendBtn"));
        m_pAddFirendBtn->setGeometry(QRect(80, 180, 91, 31));
        m_pCancelBtn = new QPushButton(AddFriendDialog);
        m_pCancelBtn->setObjectName(QStringLiteral("m_pCancelBtn"));
        m_pCancelBtn->setGeometry(QRect(220, 180, 91, 31));

        retranslateUi(AddFriendDialog);

        QMetaObject::connectSlotsByName(AddFriendDialog);
    } // setupUi

    void retranslateUi(QDialog *AddFriendDialog)
    {
        AddFriendDialog->setWindowTitle(QApplication::translate("AddFriendDialog", "Dialog", 0));
        label->setText(QApplication::translate("AddFriendDialog", "\346\237\245\346\211\276\350\246\201\346\267\273\345\212\240\347\232\204\345\245\275\345\217\213", 0));
        m_pAddFirendBtn->setText(QApplication::translate("AddFriendDialog", "\346\267\273\345\212\240", 0));
        m_pCancelBtn->setText(QApplication::translate("AddFriendDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class AddFriendDialog: public Ui_AddFriendDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIENDDIALOG_H
