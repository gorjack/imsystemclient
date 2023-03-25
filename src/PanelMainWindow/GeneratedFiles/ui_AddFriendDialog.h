/********************************************************************************
** Form generated from reading UI file 'AddFriendDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIENDDIALOG_H
#define UI_ADDFRIENDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriendDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *m_pIdLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pAddFirendBtn;
    QPushButton *m_pCancelBtn;

    void setupUi(QDialog *AddFriendDialog)
    {
        if (AddFriendDialog->objectName().isEmpty())
            AddFriendDialog->setObjectName(QString::fromUtf8("AddFriendDialog"));
        AddFriendDialog->resize(400, 300);
        widget = new QWidget(AddFriendDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 40, 311, 221));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_pIdLineEdit = new QLineEdit(widget);
        m_pIdLineEdit->setObjectName(QString::fromUtf8("m_pIdLineEdit"));

        horizontalLayout->addWidget(m_pIdLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_pAddFirendBtn = new QPushButton(widget);
        m_pAddFirendBtn->setObjectName(QString::fromUtf8("m_pAddFirendBtn"));

        horizontalLayout_2->addWidget(m_pAddFirendBtn);

        m_pCancelBtn = new QPushButton(widget);
        m_pCancelBtn->setObjectName(QString::fromUtf8("m_pCancelBtn"));

        horizontalLayout_2->addWidget(m_pCancelBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(AddFriendDialog);

        QMetaObject::connectSlotsByName(AddFriendDialog);
    } // setupUi

    void retranslateUi(QDialog *AddFriendDialog)
    {
        AddFriendDialog->setWindowTitle(QCoreApplication::translate("AddFriendDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddFriendDialog", "\346\237\245\346\211\276\350\246\201\346\267\273\345\212\240\347\232\204\345\245\275\345\217\213:", nullptr));
        m_pAddFirendBtn->setText(QCoreApplication::translate("AddFriendDialog", "\346\267\273\345\212\240", nullptr));
        m_pCancelBtn->setText(QCoreApplication::translate("AddFriendDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriendDialog: public Ui_AddFriendDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIENDDIALOG_H
