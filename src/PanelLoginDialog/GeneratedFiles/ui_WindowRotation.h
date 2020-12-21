/********************************************************************************
** Form generated from reading UI file 'WindowRotation.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWROTATION_H
#define UI_WINDOWROTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowRotationClass
{
public:

    void setupUi(QWidget *WindowRotationClass)
    {
        if (WindowRotationClass->objectName().isEmpty())
            WindowRotationClass->setObjectName(QStringLiteral("WindowRotationClass"));
        WindowRotationClass->resize(600, 400);

        retranslateUi(WindowRotationClass);

        QMetaObject::connectSlotsByName(WindowRotationClass);
    } // setupUi

    void retranslateUi(QWidget *WindowRotationClass)
    {
        WindowRotationClass->setWindowTitle(QApplication::translate("WindowRotationClass", "WindowRotation", 0));
    } // retranslateUi

};

namespace Ui {
    class WindowRotationClass: public Ui_WindowRotationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWROTATION_H
