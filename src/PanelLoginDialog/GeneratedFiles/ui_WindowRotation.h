/********************************************************************************
** Form generated from reading UI file 'WindowRotation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWROTATION_H
#define UI_WINDOWROTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowRotationClass
{
public:

    void setupUi(QWidget *WindowRotationClass)
    {
        if (WindowRotationClass->objectName().isEmpty())
            WindowRotationClass->setObjectName(QString::fromUtf8("WindowRotationClass"));
        WindowRotationClass->resize(600, 400);

        retranslateUi(WindowRotationClass);

        QMetaObject::connectSlotsByName(WindowRotationClass);
    } // setupUi

    void retranslateUi(QWidget *WindowRotationClass)
    {
        WindowRotationClass->setWindowTitle(QCoreApplication::translate("WindowRotationClass", "WindowRotation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowRotationClass: public Ui_WindowRotationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWROTATION_H
