#pragma once
#include <QtWidgets/QLineEdit>

namespace QF
{
    class CLineEdit : public QLineEdit
    {
        Q_OBJECT
    public:
        CLineEdit(QWidget* parent = NULL)
            : QLineEdit(parent) {}

    signals:
        void sigTextEditFinish();
        void sigFocusIn();
        void sigFocusOut();
    protected:
        void keyPressEvent(QKeyEvent *e);
        void focusInEvent(QFocusEvent *e);
        void focusOutEvent(QFocusEvent *e);
    };
}