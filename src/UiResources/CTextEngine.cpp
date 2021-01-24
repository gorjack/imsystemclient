/**
 *  文字渲染引擎
 *
 *  @author zhangyi
 *  @since  2013-07-11
 */

#include <UiResources/CTextEngine.h>
#include <utils/commonFunc.h>

namespace XP
{

    CTextEngine::CTextEngine()
    {
        
    }

    CTextEngine::~CTextEngine()
    {
        utils::safeClearContainer(&m_postfix);
    }

    void CTextEngine::initPostfix( const QFont & fnt )
    {
        for (int i = 0; i < 3; ++i)
        {
            QStaticText * pText = new QStaticText();
            initStaticText(*pText, ".", fnt);
            m_postfix.push_back(pText);
        }
    }

    const QVector<const QStaticText *> & CTextEngine::getPostFix() const
    {
        return m_postfix;
    }

    const QStaticText * CTextEngine::getStaticText( const QString & qsText, const QFont & fnt )
    {
        QMap<QString, QMap<QFont, QStaticText> >::iterator iter = m_texts.find(qsText);
        if (m_texts.end() == iter)
        {
            initStaticText(m_texts[qsText][fnt], qsText, fnt);
            return &m_texts[qsText][fnt];
        }
        else
        {
            QMap<QFont, QStaticText>::iterator iIter = iter->find(fnt);
            if (iter->end() == iIter)
            {
                initStaticText((*iter)[fnt], qsText, fnt);
                return &(*iter)[fnt];
            }
            else
            {
                return &(*iIter);
            }
        }
    }

    void CTextEngine::initStaticText( QStaticText & txt, const QString & qsText, const QFont & fnt )
    {
        txt.setText(qsText);
        txt.prepare(QTransform(), fnt);
        txt.setPerformanceHint(QStaticText::AggressiveCaching);
        txt.setTextFormat(Qt::PlainText);
    }

}

