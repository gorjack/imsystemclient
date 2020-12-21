/********************************************************************************
** Form generated from reading UI file 'loginnetsetwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINNETSETWINDOW_H
#define UI_LOGINNETSETWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginNetSetWindow
{
public:
    QPushButton *pButtonOk;
    QPushButton *pButtonCancel;
    QLabel *labelNet;
    QPushButton *imageTestBtn;
    QPushButton *chatTestBtn;
    QPushButton *fileTestBtn;
    QSplitter *splitter;
    QLabel *label_2;
    QLineEdit *chatAddr;
    QSplitter *splitter_2;
    QLabel *label_5;
    QLineEdit *imageAddr;
    QSplitter *splitter_3;
    QLabel *label_12;
    QLineEdit *fileAddr;

    void setupUi(QWidget *LoginNetSetWindow)
    {
        if (LoginNetSetWindow->objectName().isEmpty())
            LoginNetSetWindow->setObjectName(QStringLiteral("LoginNetSetWindow"));
        LoginNetSetWindow->resize(428, 334);
        LoginNetSetWindow->setMinimumSize(QSize(428, 334));
        LoginNetSetWindow->setMaximumSize(QSize(428, 334));
        pButtonOk = new QPushButton(LoginNetSetWindow);
        pButtonOk->setObjectName(QStringLiteral("pButtonOk"));
        pButtonOk->setGeometry(QRect(247, 305, 84, 24));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        pButtonOk->setFont(font);
        pButtonOk->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"	padding-left:2px;\n"
"	padding-top:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"\n"
""));
        pButtonCancel = new QPushButton(LoginNetSetWindow);
        pButtonCancel->setObjectName(QStringLiteral("pButtonCancel"));
        pButtonCancel->setGeometry(QRect(335, 305, 84, 24));
        pButtonCancel->setFont(font);
        pButtonCancel->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"	padding-left:2px;\n"
"	padding-top:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"\n"
""));
        labelNet = new QLabel(LoginNetSetWindow);
        labelNet->setObjectName(QStringLiteral("labelNet"));
        labelNet->setGeometry(QRect(0, 0, 430, 41));
        imageTestBtn = new QPushButton(LoginNetSetWindow);
        imageTestBtn->setObjectName(QStringLiteral("imageTestBtn"));
        imageTestBtn->setGeometry(QRect(310, 130, 56, 24));
        imageTestBtn->setMinimumSize(QSize(56, 24));
        imageTestBtn->setMaximumSize(QSize(56, 24));
        imageTestBtn->setFont(font);
        imageTestBtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"	padding-left:2px;\n"
"	padding-top:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"\n"
""));
        chatTestBtn = new QPushButton(LoginNetSetWindow);
        chatTestBtn->setObjectName(QStringLiteral("chatTestBtn"));
        chatTestBtn->setGeometry(QRect(310, 80, 56, 24));
        chatTestBtn->setMinimumSize(QSize(56, 24));
        chatTestBtn->setMaximumSize(QSize(56, 24));
        chatTestBtn->setFont(font);
        chatTestBtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"	padding-left:2px;\n"
"	padding-top:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"\n"
""));
        fileTestBtn = new QPushButton(LoginNetSetWindow);
        fileTestBtn->setObjectName(QStringLiteral("fileTestBtn"));
        fileTestBtn->setGeometry(QRect(310, 180, 56, 24));
        fileTestBtn->setMinimumSize(QSize(56, 24));
        fileTestBtn->setMaximumSize(QSize(56, 24));
        fileTestBtn->setFont(font);
        fileTestBtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    background:rgb(245,249,252);\n"
"    border-radius:2px;\n"
"	padding-left:2px;\n"
"	padding-top:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"\n"
""));
        splitter = new QSplitter(LoginNetSetWindow);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(40, 80, 251, 31));
        splitter->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        splitter->addWidget(label_2);
        chatAddr = new QLineEdit(splitter);
        chatAddr->setObjectName(QStringLiteral("chatAddr"));
        chatAddr->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background:white;\n"
"    padding-left:2px ;\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QLineEdit:hover\n"
"{\n"
"    border: 1px solid rgb(21 , 131 , 221);\n"
"}"));
        splitter->addWidget(chatAddr);
        splitter_2 = new QSplitter(LoginNetSetWindow);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(40, 130, 251, 31));
        splitter_2->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(splitter_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);
        splitter_2->addWidget(label_5);
        imageAddr = new QLineEdit(splitter_2);
        imageAddr->setObjectName(QStringLiteral("imageAddr"));
        imageAddr->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background:white;\n"
"    padding-left:2px ;\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QLineEdit:hover\n"
"{\n"
"    border: 1px solid rgb(21 , 131 , 221);\n"
"}"));
        splitter_2->addWidget(imageAddr);
        splitter_3 = new QSplitter(LoginNetSetWindow);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setGeometry(QRect(40, 180, 251, 31));
        splitter_3->setOrientation(Qt::Horizontal);
        label_12 = new QLabel(splitter_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font);
        splitter_3->addWidget(label_12);
        fileAddr = new QLineEdit(splitter_3);
        fileAddr->setObjectName(QStringLiteral("fileAddr"));
        fileAddr->setStyleSheet(QLatin1String("QLineEdit\n"
"{\n"
"    background:white;\n"
"    padding-left:2px ;\n"
"    border-radius:2px;\n"
"    border: 1px solid rgb(173 , 173 , 173);\n"
"}\n"
"QLineEdit:hover\n"
"{\n"
"    border: 1px solid rgb(21 , 131 , 221);\n"
"}"));
        splitter_3->addWidget(fileAddr);

        retranslateUi(LoginNetSetWindow);

        QMetaObject::connectSlotsByName(LoginNetSetWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginNetSetWindow)
    {
        LoginNetSetWindow->setWindowTitle(QApplication::translate("LoginNetSetWindow", "LoginNetSetWindow", 0));
        pButtonOk->setText(QApplication::translate("LoginNetSetWindow", "\347\241\256\345\256\232", 0));
        pButtonCancel->setText(QApplication::translate("LoginNetSetWindow", "\345\217\226\346\266\210", 0));
        labelNet->setText(QString());
        imageTestBtn->setText(QApplication::translate("LoginNetSetWindow", "\346\265\213\350\257\225", 0));
        chatTestBtn->setText(QApplication::translate("LoginNetSetWindow", "\346\265\213\350\257\225", 0));
        fileTestBtn->setText(QApplication::translate("LoginNetSetWindow", "\346\265\213\350\257\225", 0));
        label_2->setText(QApplication::translate("LoginNetSetWindow", "\350\201\212\345\244\251\346\234\215\345\212\241:", 0));
        label_5->setText(QApplication::translate("LoginNetSetWindow", "\345\233\276\347\211\207\346\234\215\345\212\241:", 0));
        label_12->setText(QApplication::translate("LoginNetSetWindow", "\346\226\207\344\273\266\346\234\215\345\212\241:", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginNetSetWindow: public Ui_LoginNetSetWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINNETSETWINDOW_H
