#include "CAutoKeyboardLineEdit.h"
#include <QtWidgets/QToolTip>
#include "CAutoKeyboardOperator.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include "CLineEdit.h"
#include "CPushButton.h"

namespace XP
{

    CAutoKeyboardLineEdit::CAutoKeyboardLineEdit(ISearchDataModel *pData, int nID,QWidget *parent /* = NULL */, bool bNeedCustom/* = false*/)
        : QWidget(parent)
        , m_nID(nID)
        , m_pLineEdit(NULL)
        , m_pPullBtn(NULL)
        , m_pOperator(NULL)
        , m_pWidget(NULL)
        , m_qsRealCode("")
        , m_nIndex(0)
        , m_bNeedCustom(bNeedCustom)
        , m_bFilterSpecialChar(true)
    {
        m_pLineEdit = new QF::CLineEdit(this);
        m_pLineEdit->installEventFilter(this);
        m_pLineEdit->setFocusPolicy(Qt::StrongFocus);
        connect(m_pLineEdit, SIGNAL(sigFocusIn()), this, SLOT(slotFocusIn()));
        connect(m_pLineEdit, SIGNAL(sigFocusOut()), this, SLOT(slotFocusOut()));
        
        m_pOperator = new CAutoKeyboardOperator(this);
        m_pWidget = new CAutoKeyboardWidget(this);
        if (NULL == pData)
        {
            pData = new CDefaultDataModel();
        }

        m_pWidget->setDataModel(pData);

        if (NULL != m_pOperator)
        {
            m_pOperator->setLineEdit(m_pLineEdit);
            m_pOperator->addSmartKeyboardWidget(m_pWidget);
            connect(m_pOperator, SIGNAL(sigChangeText(int, const QString&, const QString&)), SLOT(slotChangeText(int, const QString&, const QString&)));
        }

        connect(m_pLineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(slotTextEdited(const QString &)));

    }

    CAutoKeyboardLineEdit::~CAutoKeyboardLineEdit()
    {
    }

    QString CAutoKeyboardLineEdit::toString()
    {
        return m_pLineEdit->text();
    }
    
    void CAutoKeyboardLineEdit::clear()
    {
        m_pLineEdit->clear();
        m_pWidget->clearCache();
        m_pWidget->getDataModel()->clearModelData();
    }

    void CAutoKeyboardLineEdit::focusInEvent(QFocusEvent *e)
    {
        QWidget::focusInEvent(e);
        if (NULL != m_pLineEdit)
        {
            m_pLineEdit->setFocus();
        }
    }

    void CAutoKeyboardLineEdit::focusOutEvent(QFocusEvent *e)
    {
        QWidget::focusOutEvent(e);
    }

    void CAutoKeyboardLineEdit::setText(const QString& strId, const QString& qsText, bool bTestString/* = true*/)
    {
        if (NULL != m_pLineEdit && NULL != m_pWidget && (-1 != m_pWidget->testString(strId) || qsText.isEmpty() || !bTestString))
        {
            m_pLineEdit->setText(qsText);
            m_qsRealCode = strId;
        }
    }

    void CAutoKeyboardLineEdit::setTextFontKey( QString qsTextFontKey )
    {
        if (NULL != m_pLineEdit)
        {
           // m_pLineEdit->setFont(*TT_FONT(qsTextFontKey));
        }
    }

    void CAutoKeyboardLineEdit::setShowName(bool bShowName)
    {
        if (NULL != m_pLineEdit)
        {
          //  m_pLineEdit->setShowLabel(bShowName);
        }
    }

    QString CAutoKeyboardLineEdit::getText() const
    {
        return m_qsRealCode;
    }

    void CAutoKeyboardLineEdit::setFrame(bool bShowFrame)
    {
        if (NULL != m_pLineEdit)
        {
            m_pLineEdit->setFrame(bShowFrame);
        }
    }

    void CAutoKeyboardLineEdit::clearCache()
    {
        if (NULL != m_pWidget)
        {
            m_pWidget->clearCache();
        }
    }

    void CAutoKeyboardLineEdit::setIndexAndText( int nIndex, QString qsText )
    {
        m_qsRealCode = qsText;
        m_pLineEdit->setText(qsText);
        m_nIndex = nIndex;
    }

    int CAutoKeyboardLineEdit::getIndex() const
    {
        return m_nIndex;
    }
    void CAutoKeyboardLineEdit::clearIndex()
    {
        m_nIndex = 0;
    }

    void CAutoKeyboardLineEdit::slotChangeText(int nIndex, const QString& qsText, const QString& qsParam)
    {
        //if (nIndex == -1)
        //{
        //    m_pLineEdit->clear();
        //    QToolTip::showText(QCursor::pos(), "未找到适配项", m_pLineEdit, m_pLineEdit->rect(), 3);
        //    return;
        //}

        m_qsRealCode = qsParam.isEmpty() ? qsText : qsParam;
        m_pLineEdit->setText(qsText);
        m_pLineEdit->clearFocus();
        m_nIndex = nIndex;
    }

    void CAutoKeyboardLineEdit::slotTextEdited(const QString &)
    {
        if (NULL != m_pOperator)
        {
            m_pOperator->testSmartKeyboardWidgets();
        }
    }

    void CAutoKeyboardLineEdit::slotFocusIn()
    {
        if (!m_pWidget->isListDataEmpty())
        {
            m_pOperator->testSmartKeyboardWidgets();
        }
    }

    void CAutoKeyboardLineEdit::slotFocusOut()
    {
        if (NULL != m_pOperator)
        {
            m_pOperator->hideSmartKeyboardWidgets();
        }
    }

    void CAutoKeyboardLineEdit::slotHandleClicked()
    {
        if (NULL != m_pLineEdit)
        {
            m_pLineEdit->clear();
            m_pLineEdit->setFocus();
        }
    }

    void CAutoKeyboardLineEdit::resizeEvent(QResizeEvent *e)
    {
        QWidget::resizeEvent(e);

        if (NULL != m_pLineEdit)
        {
            m_pLineEdit->setGeometry(0, 0, width(), height());
        }

        if (NULL != m_pWidget)
        {
            m_pWidget->resize(width(), m_pWidget->height());
        }

        if (NULL != m_pPullBtn)
        {
            m_pPullBtn->resize(height() - 2, height() - 2);
            m_pPullBtn->move(width() - height() + 1, 1);
        }
    }

    bool CAutoKeyboardLineEdit::eventFilter(QObject *pObj, QEvent *pEvent)
    {
        if (pEvent->type() == QEvent::FocusIn && !m_bNeedCustom)
        {
            QFocusEvent *pFocusEvent = dynamic_cast<QFocusEvent *>(pEvent);
            if (NULL != pFocusEvent && NULL != m_pWidget && m_pWidget->isListDataEmpty()
                && (pFocusEvent->reason() == Qt::MouseFocusReason || pFocusEvent->reason() == Qt::TabFocusReason))
            {
                QToolTip::showText(QCursor::pos(), "当前无可选项！");
            }
        }
        if (pEvent->type() == QEvent::KeyPress)
        {
            QKeyEvent *pKeyEvent = dynamic_cast<QKeyEvent *>(pEvent);
            if (NULL != pKeyEvent)
            {
                int nKey = pKeyEvent->key();
                qDebug() << nKey << "\n";
                if (nKey == Qt::Key_Up || nKey == Qt::Key_Down || nKey == Qt::Key_Left || nKey == Qt::Key_Right 
                    || nKey == Qt::Key_Enter || nKey == Qt::Key_Return || nKey == Qt::Key_Escape 
                    || nKey == Qt::Key_Backspace || nKey == Qt::Key_Delete || nKey == Qt::Key_Tab
                    || nKey == Qt::Key_Shift || nKey == Qt::Key_Control || nKey == Qt::Key_Alt
                    || nKey == Qt::Key_Space || nKey == Qt::Key_Ampersand   // '&'
                    || QChar(nKey).isLetterOrNumber())
                {
                    return false;
                }

                if (m_listFilterChar.contains(nKey))
                {
                    return true;
                }

                if (!m_bFilterSpecialChar)  // && nKey != Key_Apostrophe/*'*/ && nKey != Key_QuoteDbl/*"*/ && nKey != Key_Backslash/*\*/)
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    QString CAutoKeyboardLineEdit::getInput() const
    {
        return m_pLineEdit->text();
    }

    void CAutoKeyboardLineEdit::setcurrentId(int id)
    {   
        this->m_nID = id;
    }

    void CAutoKeyboardLineEdit::setNeedCustom(bool bNeedCustom)
    {
        m_bNeedCustom = bNeedCustom;
    }

    void CAutoKeyboardLineEdit::setValidator(QValidator* pValidator)
    {
        m_pLineEdit->setValidator(pValidator);
    }

    void CAutoKeyboardLineEdit::setAutoToUpper(bool autoToUpper)
    {
        if (NULL != m_pWidget)
        {
            m_pWidget->setAutoToUpper(autoToUpper);
        }
    }

    void CAutoKeyboardLineEdit::setFilterSpecialChar(bool bFilterSpecialChar)
    {
        m_bFilterSpecialChar = bFilterSpecialChar;
    }

    void CAutoKeyboardLineEdit::setFilterChar(QList<int> filterCharList)
    {
        m_listFilterChar = filterCharList;
    }

    void CAutoKeyboardLineEdit::setDataModel( ISearchDataModel *pDataModel )
    {
        m_pWidget->setDataModel(pDataModel);
    }

    void CAutoKeyboardLineEdit::setWidgetWidth(int iWidth)
    {
        if (NULL != m_pWidget)
        {
            m_pWidget->setFixedWidth(iWidth);
        }
    }

    QLineEdit * CAutoKeyboardLineEdit::getLineEdit() const
    {
        return m_pLineEdit;
    }

    void CAutoKeyboardLineEdit::setPinYinAdapter( bool bAdapter )
    {
        if (NULL != m_pWidget)
        {
            m_pWidget->setPinYinAdapter(bAdapter);
        }
    }

    void CAutoKeyboardLineEdit::setPullBtnShow( bool bTrue )
    {
        if (bTrue)
        {
            if (NULL == m_pPullBtn)
            {
                m_pPullBtn = new QF::CPushButton(this);
                m_pPullBtn->init(QStringList{ "normal_down.png", "hover_down.png", "down_down_up.png" });
                connect(m_pPullBtn, SIGNAL(clicked()), this, SLOT(slotHandleClicked()));
                m_pPullBtn->setFlat(true);
                m_pPullBtn->installEventFilter(this);
            }
            resize(width(),height());
        }
        else
        {
            delete(m_pPullBtn);
            m_pPullBtn = NULL;
        }
    }
}