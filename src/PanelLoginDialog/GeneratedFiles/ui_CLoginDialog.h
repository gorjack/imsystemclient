/********************************************************************************
** Form generated from reading UI file 'CLoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOGINDIALOG_H
#define UI_CLOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CLoginDialogClass
{
public:
    QFrame *formFrame;
    QGridLayout *gridLayout;
    QLabel *m_userLabel;
    QLabel *m_passWdLabel;
    QLineEdit *m_passWdLineE;
    QLineEdit *m_userLineE;
    QPushButton *m_pLoginBtn;
    QPushButton *m_pRegistBtn;

    void setupUi(QDialog *CLoginDialogClass)
    {
        if (CLoginDialogClass->objectName().isEmpty())
            CLoginDialogClass->setObjectName(QString::fromUtf8("CLoginDialogClass"));
        CLoginDialogClass->resize(635, 377);
        formFrame = new QFrame(CLoginDialogClass);
        formFrame->setObjectName(QString::fromUtf8("formFrame"));
        formFrame->setGeometry(QRect(140, 60, 341, 181));
        gridLayout = new QGridLayout(formFrame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_userLabel = new QLabel(formFrame);
        m_userLabel->setObjectName(QString::fromUtf8("m_userLabel"));

        gridLayout->addWidget(m_userLabel, 0, 0, 1, 1);

        m_passWdLabel = new QLabel(formFrame);
        m_passWdLabel->setObjectName(QString::fromUtf8("m_passWdLabel"));

        gridLayout->addWidget(m_passWdLabel, 1, 0, 1, 1);

        m_passWdLineE = new QLineEdit(formFrame);
        m_passWdLineE->setObjectName(QString::fromUtf8("m_passWdLineE"));

        gridLayout->addWidget(m_passWdLineE, 1, 1, 1, 1);

        m_userLineE = new QLineEdit(formFrame);
        m_userLineE->setObjectName(QString::fromUtf8("m_userLineE"));

        gridLayout->addWidget(m_userLineE, 0, 1, 1, 1);

        m_pLoginBtn = new QPushButton(CLoginDialogClass);
        m_pLoginBtn->setObjectName(QString::fromUtf8("m_pLoginBtn"));
        m_pLoginBtn->setGeometry(QRect(180, 290, 231, 41));
        m_pRegistBtn = new QPushButton(CLoginDialogClass);
        m_pRegistBtn->setObjectName(QString::fromUtf8("m_pRegistBtn"));
        m_pRegistBtn->setGeometry(QRect(510, 110, 75, 23));
        m_pRegistBtn->setFlat(true);

        retranslateUi(CLoginDialogClass);

        QMetaObject::connectSlotsByName(CLoginDialogClass);
    } // setupUi

    void retranslateUi(QDialog *CLoginDialogClass)
    {
        CLoginDialogClass->setWindowTitle(QCoreApplication::translate("CLoginDialogClass", "CLoginDialog", nullptr));
#if QT_CONFIG(tooltip)
        formFrame->setToolTip(QCoreApplication::translate("CLoginDialogClass", "<html><head/><body><p><span style=\" font-weight:600;\">\347\203\247\350\261\206\350\205\220</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        m_userLabel->setText(QCoreApplication::translate("CLoginDialogClass", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        m_passWdLabel->setText(QCoreApplication::translate("CLoginDialogClass", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201\357\274\232", nullptr));
        m_pLoginBtn->setText(QCoreApplication::translate("CLoginDialogClass", "\347\231\273              \345\275\225", nullptr));
        m_pRegistBtn->setText(QCoreApplication::translate("CLoginDialogClass", "\346\263\250   \345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CLoginDialogClass: public Ui_CLoginDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOGINDIALOG_H
