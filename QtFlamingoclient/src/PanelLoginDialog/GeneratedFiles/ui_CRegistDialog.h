/********************************************************************************
** Form generated from reading UI file 'CRegistDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREGISTDIALOG_H
#define UI_CREGISTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_CRegistDialog
{
public:
    QPushButton *m_pRegistBtn;
    QSplitter *splitter;
    QLabel *label;
    QLineEdit *m_pAccountId;
    QSplitter *splitter_2;
    QLabel *label_2;
    QLineEdit *m_pNickName;
    QSplitter *splitter_3;
    QLabel *label_3;
    QLineEdit *m_pPassWd;
    QSplitter *splitter_4;
    QLabel *label_4;
    QLineEdit *m_pConfirmPassWd;

    void setupUi(QDialog *CRegistDialog)
    {
        if (CRegistDialog->objectName().isEmpty())
            CRegistDialog->setObjectName(QStringLiteral("CRegistDialog"));
        CRegistDialog->resize(428, 341);
        m_pRegistBtn = new QPushButton(CRegistDialog);
        m_pRegistBtn->setObjectName(QStringLiteral("m_pRegistBtn"));
        m_pRegistBtn->setGeometry(QRect(120, 280, 211, 41));
        m_pRegistBtn->setStyleSheet(QLatin1String("    color:white;\n"
"    background-color:rgb(14 , 150 , 254);\n"
"    border-radius:5px;"));
        splitter = new QSplitter(CRegistDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(50, 50, 331, 31));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QStringLiteral("label"));
        splitter->addWidget(label);
        m_pAccountId = new QLineEdit(splitter);
        m_pAccountId->setObjectName(QStringLiteral("m_pAccountId"));
        splitter->addWidget(m_pAccountId);
        splitter_2 = new QSplitter(CRegistDialog);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(50, 100, 331, 31));
        splitter_2->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        splitter_2->addWidget(label_2);
        m_pNickName = new QLineEdit(splitter_2);
        m_pNickName->setObjectName(QStringLiteral("m_pNickName"));
        splitter_2->addWidget(m_pNickName);
        splitter_3 = new QSplitter(CRegistDialog);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setGeometry(QRect(50, 150, 331, 31));
        splitter_3->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        splitter_3->addWidget(label_3);
        m_pPassWd = new QLineEdit(splitter_3);
        m_pPassWd->setObjectName(QStringLiteral("m_pPassWd"));
        splitter_3->addWidget(m_pPassWd);
        splitter_4 = new QSplitter(CRegistDialog);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setGeometry(QRect(50, 200, 331, 31));
        splitter_4->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(splitter_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(76, 31));
        splitter_4->addWidget(label_4);
        m_pConfirmPassWd = new QLineEdit(splitter_4);
        m_pConfirmPassWd->setObjectName(QStringLiteral("m_pConfirmPassWd"));
        splitter_4->addWidget(m_pConfirmPassWd);

        retranslateUi(CRegistDialog);

        QMetaObject::connectSlotsByName(CRegistDialog);
    } // setupUi

    void retranslateUi(QDialog *CRegistDialog)
    {
        CRegistDialog->setWindowTitle(QApplication::translate("CRegistDialog", "Dialog", 0));
        m_pRegistBtn->setText(QApplication::translate("CRegistDialog", "\346\263\250    \345\206\214", 0));
        label->setText(QApplication::translate("CRegistDialog", "\347\224\250   \346\210\267ID\357\274\232", 0));
        label_2->setText(QApplication::translate("CRegistDialog", "\346\230\265      \347\247\260\357\274\232", 0));
        label_3->setText(QApplication::translate("CRegistDialog", "\345\257\206      \347\240\201\357\274\232", 0));
        label_4->setText(QApplication::translate("CRegistDialog", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class CRegistDialog: public Ui_CRegistDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREGISTDIALOG_H
