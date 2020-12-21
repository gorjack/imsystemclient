#include "CLineEdit.h"
#include <QKeyEvent>

namespace  QF
{
    void CLineEdit::keyPressEvent(QKeyEvent *e)
    {
        if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
        {
            emit sigTextEditFinish();
        }
        QLineEdit::keyPressEvent(e);
    }

    void CLineEdit::focusInEvent(QFocusEvent *e)
    {
        QLineEdit::focusInEvent(e);
        emit sigFocusIn();
    }

    void CLineEdit::focusOutEvent(QFocusEvent *e)
    {
        QLineEdit::focusOutEvent(e);
        emit sigFocusOut();
    }
}