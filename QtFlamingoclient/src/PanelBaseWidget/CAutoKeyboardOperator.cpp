/**
 *  键盘精灵输入辅助关联工具类    
 *
 *  @author zhangyi
 *  @since  2012-03-29
 *  @modify by huangxu
 *  @since since 2016-03-27
 */

#include "CAutoKeyboardWidget.h"
#include "CAutoKeyboardOperator.h"
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QtWidgets/QDesktopWidget>
#include "CLineEdit.h"

namespace XP
{

    //////////////////////////////////////////////////////////////////////////
    // 尚未处理line edit的move event，后续再添加。
    //////////////////////////////////////////////////////////////////////////

    CAutoKeyboardOperator::CAutoKeyboardOperator( QObject *parent /*= NULL*/ )
        : QObject(parent),
        m_pLineEdit(NULL)
    {

    }

    CAutoKeyboardOperator::~CAutoKeyboardOperator()
    {

    }


    void CAutoKeyboardOperator::setLineEdit(QF::CLineEdit*  pLineEdit)
    {
        m_pLineEdit = pLineEdit;
        if (NULL != m_pLineEdit)
        {
            m_pLineEdit->installEventFilter(this);
        }
    }

    void CAutoKeyboardOperator::addSmartKeyboardWidget( CAutoKeyboardWidget *pSmartKeyboardWidget )
    {
        m_vSmartKeyboardWidgets.push_back(pSmartKeyboardWidget);
        m_vSmartKeyboardShow.push_back(false);
        connect(
            pSmartKeyboardWidget,
            SIGNAL(sigItemDoubleClicked(QString)),
            SLOT(slotItemDoubleClicked(QString))
            );
    }

    void CAutoKeyboardOperator::testSmartKeyboardWidgets()
    {
        for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); i++)
        {
            testSmartKeyboardWidget(i);
        }
    }

    void CAutoKeyboardOperator::hideSmartKeyboardWidgets()
    {
        for (int i = 0; i < m_vSmartKeyboardWidgets.size(); i++)
        {
            if (m_vSmartKeyboardWidgets[i]->isActiveWindow())
                return;
        }

        for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); i++)
        {
            hideSmartKeyboardWidget(i);
        }
    }

    bool CAutoKeyboardOperator::anySmartKeyboardShow() const
    {
        for (QVector<bool>::const_iterator cIt = m_vSmartKeyboardShow.begin(); cIt != m_vSmartKeyboardShow.end(); cIt++)
        {
            if (*cIt)
            {
                return true;
            }
        }
        return false;
    }

    void CAutoKeyboardOperator::slotItemDoubleClicked(QString qsText )
    {
        for (int i = 0; i < m_vSmartKeyboardWidgets.size(); i++)
        {
            if (NULL != m_vSmartKeyboardWidgets[i])
            {
                pushSelectionOnTextEdit(i);
                break;
            }
        }
    }

    bool CAutoKeyboardOperator::eventFilter( QObject *pObj, QEvent *pEvent )
    {
        if (pObj == m_pLineEdit)
        {
            if (pEvent->type() == QEvent::KeyPress && anySmartKeyboardShow())
            {
                QKeyEvent *pKeyEvent = dynamic_cast<QKeyEvent *>(pEvent);
                if (NULL != pKeyEvent)
                {
                    int nKey = pKeyEvent->key();
                    int nMod = pKeyEvent->modifiers();

                    if (pKeyEvent->key() == Qt::Key_Up)
                    {
                        if (hasVisibleSmartKeyboardWidgets())
                        {
                            // 按“上”，往上移动当前选项
                            for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); i++)
                            {
                                CAutoKeyboardWidget *pWidget = m_vSmartKeyboardWidgets[i];
                                bool bShow = m_vSmartKeyboardShow[i];
                                if (NULL != pWidget && bShow)
                                {
                                    pWidget->setCurrentRow(pWidget->currentRow() - 1);
                                }
                            }
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else if (pKeyEvent->key() == Qt::Key_Down)
                    {
                        if (hasVisibleSmartKeyboardWidgets())
                        {
                            // 按“下”，往上移动当前选项
                            for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); i++)
                            {
                                CAutoKeyboardWidget *pWidget = m_vSmartKeyboardWidgets[i];
                                bool bShow = m_vSmartKeyboardShow[i];
                                if (NULL != pWidget && bShow)
                                {
                                    pWidget->setCurrentRow(pWidget->currentRow() + 1);
                                }
                            }
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else if (
                        (Qt::Key_Return == nKey && 0 == nMod)
                        || (Qt::Key_Enter == nKey && Qt::KeypadModifier == nMod)
                        )
                    {
                        if (hasVisibleSmartKeyboardWidgets())
                        {
                            // 按回车，将当前选项上屏
                            for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); i++)
                            {
                                pushSelectionOnTextEdit(i);
                                hideSmartKeyboardWidget(i);
                            }
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else if (Qt::Key_Escape == nKey)
                    {
                        // 按esc，隐藏输入辅助窗口
                        for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); i++)
                        {
                            hideSmartKeyboardWidget(i);
                        }
                        return true;
                    }
                    else if (Qt::Key_Tab == nKey)
                    {
                        // 按tab，隐藏输入辅助窗口
                        for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); i++)
                        {
                            hideSmartKeyboardWidget(i);
                        }
                        return false;
                    }
                }
            }
        }
        
        if (pEvent->type() == QEvent::Move)
        {
            QMoveEvent * pMoveEvent = dynamic_cast<QMoveEvent *>(pEvent);
            if (NULL != pMoveEvent)
            {
                QPoint ptShift(pMoveEvent->pos() - pMoveEvent->oldPos());
                for (int i = 0; i < m_vSmartKeyboardShow.size() && i < m_vSmartKeyboardWidgets.size(); ++i)
                {
                    if (m_vSmartKeyboardShow[i] && NULL != m_vSmartKeyboardWidgets[i])
                    {
                        m_vSmartKeyboardWidgets[i]->shift(ptShift);
                    }
                }
            }
        }


        return false;
    }

    void CAutoKeyboardOperator::testSmartKeyboardWidget(int i)
    {
        if (i < 0 || i >= m_vSmartKeyboardShow.size() || i >= m_vSmartKeyboardWidgets.size())
        {
            return;
        }

        CAutoKeyboardWidget *pWidget = m_vSmartKeyboardWidgets[i];
        if (NULL != m_pLineEdit && NULL != pWidget)
        {
            ////没有可选项时 不弹出下拉框
            //if (pWidget->isListDataEmpty())
            //{
            //    m_pLineEdit->clearFocus();
            //    return;
            //}
            QString qsSelection = m_pLineEdit->selectedText();
            if (!qsSelection.isEmpty())
            {
                // 选中文本不为空。
                hideSmartKeyboardWidget(i);
            }
            else
            {
                // 选中文本为空。
                showSmartKeyboardWidget(0, m_pLineEdit->height() + 2, m_pLineEdit->width(), m_pLineEdit->height(), m_pLineEdit->text(), i);
            }
        }
    }

    void CAutoKeyboardOperator::showSmartKeyboardWidget( int x, int y, int w, int h, QString qsKey, int i )
    {
        if (i < 0 || i >= m_vSmartKeyboardShow.size() || i >= m_vSmartKeyboardWidgets.size())
        {
            return;
        }

        CAutoKeyboardWidget *pWidget = m_vSmartKeyboardWidgets[i];
        if (NULL != pWidget)
        {
            // zhangyi : 2013-05-28
            // 这个地方需要特殊说明：
            // 
            // 需求：
            // 1. 文本框有焦点，弹出的输入提示框无焦点。
            // 2. 文本框移动（在屏幕内的位置移动），输入框要跟随移动。
            //
            // 如果输入提示框ISmartKeyboardWidget的属性是Popup
            // 则qt会在其show的时候调用openPopup，会强制发一个focusout到文本框中
            // 进而引发一系列连锁循环反应以致stack overflow，并且也不符合需求1。
            //
            // 因此，为保证输入框能弹出来，又不在任务栏显示，只能是Tool属性。
            // 而Tool属性本身确实无法保证主窗体移动的时候输入框会跟着移动。
            //
            // 而且，在主窗体移动时，文本框是没有moveevent的，因为文本框相对于其parent的位置是没变的。
            // 还要考虑到文本框的某个parent的parent的parent……（但不是主窗体）移动时的情形。
            //
            // 因此，最终的做法是：
            // 1. 将从文本框一直上溯到主窗体的所有qwidget都设event filter，捕捉其所有move event并处理。
            // 2. 因为dock系统的存在，文本框属于哪个主窗体是可变的，因此在每次show出来的时候重新install event filter，在隐藏时清空。
            reinstallEvtFilter();

            m_vSmartKeyboardShow[i] = true;

            QPoint pt(x, y);
            QPoint ptLeLeftBottom(x, y);
            QPoint ptLeLeftTop(x, y);
            if (NULL != m_pLineEdit)
            {
                ptLeLeftBottom = m_pLineEdit->mapToGlobal(pt);
                pt = ptLeLeftBottom;
                ptLeLeftTop.setY(pt.y() - m_pLineEdit->height());
            }

            QDesktopWidget * desktopWidget = qApp->desktop();
            QRect clientRect = desktopWidget->availableGeometry(desktopWidget->screenNumber(pt));

            if (pt.x() + pWidget->width() > clientRect.right())
            {
                pt.setX(clientRect.right() - pWidget->width());
            }
            if (pt.x() < clientRect.left())
            {
                pt.setX(clientRect.left());
            }
 
            if (pt.y() + pWidget->height() > clientRect.bottom())
            {
                pt.setY(clientRect.bottom() - pWidget->height());

                //上移有可能遮住lineedit
                if (pt.y() < ptLeLeftBottom.y())
                {
                    pt.setY(ptLeLeftTop.y() - pWidget->height() - 5);
                }
            }
            if (pt.y() < clientRect.top())
            {
                pt.setY(clientRect.top());
            }

            pWidget->display(pt, qsKey);
        }
    }

    void CAutoKeyboardOperator::hideSmartKeyboardWidget( int i )
    {
        if (i < 0 || i >= m_vSmartKeyboardShow.size() || i >= m_vSmartKeyboardWidgets.size())
        {
            return;
        }

        CAutoKeyboardWidget *pWidget = m_vSmartKeyboardWidgets[i];

        if (NULL != pWidget)
        {
            clearEvtFilter();
            m_vSmartKeyboardShow[i] = false;
            pWidget->hide();
        }
    }

    void CAutoKeyboardOperator::pushSelectionOnTextEdit( int i )
    {
        if (i < 0 || i >= m_vSmartKeyboardShow.size() || i >= m_vSmartKeyboardWidgets.size())
        {
            return;
        }
        if (!m_vSmartKeyboardShow[i])
        {
            return;
        }

        CAutoKeyboardWidget *pWidget = m_vSmartKeyboardWidgets[i];

        if (NULL != m_pLineEdit && NULL != pWidget)
        {
            QString qsFinalText = pWidget->getSelection();
            QString qsId = pWidget->getParam();
            int nOriginalIndex = pWidget->testString(qsId);
            emit sigChangeText(nOriginalIndex, pWidget->getSelection(), pWidget->getParam());
        }
    }

    bool CAutoKeyboardOperator::hasVisibleSmartKeyboardWidgets()
    {
        for (int i = 0; i < m_vSmartKeyboardShow.size(); i++)
        {
            if (m_vSmartKeyboardShow[i])
            {
                return true;
            }
        }

        return false;
    }

    void CAutoKeyboardOperator::reinstallEvtFilter()
    {
        if (NULL != m_pLineEdit)
        {
            QWidget * pw = m_pLineEdit->parentWidget();
            while (pw != NULL)
            {
                m_evtFiltered.insert(pw);
                pw->installEventFilter(this);
                pw = pw->parentWidget();
            }
        }
    }

    void CAutoKeyboardOperator::clearEvtFilter()
    {
        for (QSet<QObject *>::const_iterator oIter = m_evtFiltered.begin(); oIter != m_evtFiltered.end(); ++oIter)
        {
            QObject * pObj = *oIter;
            if (NULL != pObj)
            {
                pObj->removeEventFilter(this);
            }
        }
        m_evtFiltered.clear();
    }
}
