/**
 *  文字渲染引擎
 */

#ifndef XP_UIRESOURCE_CTEXTENGINE_H
#define XP_UIRESOURCE_CTEXTENGINE_H
#include <QMap>
#include <QStaticText>
#include <QFont>
#include <QString>
#include <QColor>
#include <QPixmap>

namespace XP
{
    class DLL_EXPORT_UIRESOURCE CTextEngine
    {
    public:
        CTextEngine();
        virtual ~CTextEngine();

        void initPostfix(const QFont & fnt);
        const QVector<const QStaticText *> & getPostFix() const;
        const QStaticText * getStaticText(const QString & qsText, const QFont & fnt);

    protected:

        QMap<QString, QMap<QFont, QStaticText> > m_texts;
        QMap<QString, QMap<QFont, QMap<QColor, QPixmap> > > m_pixmaps;
        QVector<const QStaticText *> m_postfix;

        void initStaticText(QStaticText & txt, const QString & qsText, const QFont & fnt);
    };
}

#endif
