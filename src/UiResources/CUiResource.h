/**
 *  ui资源管理类
 */

#ifndef XP_UIRESOURCE_CUIRESOURCE_H
#define XP_UIRESOURCE_CUIRESOURCE_H

#include <utils/CSingletonT.h>
#include <QString>
#include <QMap>
#include <QList>
#include <QVector>
#include <QtMultimedia/QSound>

#include <QIcon>
#include <QPixmap>
#include <QStaticText>

namespace XP
{
    class CColorCenter;
    class CImageCenter;
    class CFontCenter;
    class CSizeCenter;
    class CSoundCenter;
    class CTextEngine;

    class DLL_EXPORT_UIRESOURCE CUiResource : public utils::CSingletonT<CUiResource>
    {
    public:
        CUiResource();
        virtual ~CUiResource();

        void parseColor(QString qsXml);
        void parseFont(QString qsXml);
        void parseImage(QString qsDir);
        void parseSize(QString qsXml);
        void parseSound(QString qsDir);
        void reParseImage(QString qsDir, QString qsKey);

        void setThemeImageDir(QString qsDir);
        QString getThemeImageDir() const;

        const QColor * registerCustomColor(const QColor & clr);

        const QColor * getColor(QString qsKey) const;
        QString getColorSheet(const QColor *pColor) const;
        QString getColorSheetByKey(QString qsKey) const;

        const QFont * registerCustomFont(const QFont & fnt);
        QString registerCustomFontKey(const QFont & fnt);
        const QFont * getCustomerFont(QString qsKey) const;

        const QFont * getFont(QString qsKey) const;
        QString getFontSheet(const QFont *pFont) const;

        const QPixmap * getPixmap(QString qsKey) const;
        const QIcon * getIcon(QString qsKey) const;

        void initPostfix(const QFont & fnt);
        const QVector<const QStaticText *> & getPostFix() const;
        const QStaticText * getStaticText(const QString & qsText, const QFont & fnt);

        int getSize(QString qsKey) const;

        QString getImageSheet(QString qsKey) const;

        QList<QString> getAllSoundKeys() const;
        QSound * getSound(QString qsKey);
        QString getSoundPath(QString qsKey);

        void setAutoAdapt(bool bAutoAdapt, float dFactor);

    protected:

        CColorCenter * m_pColorCenter;
        CImageCenter * m_pImageCenter;
        CFontCenter * m_pFontCenter;
        CSizeCenter * m_pSizeCenter;
        CSoundCenter * m_pSoundCenter;
        CTextEngine * m_pTextEngine;

        QVector<const QStaticText *> m_fuck;

        QString                 m_qsThemeImageDir;

        QString                 m_qsResourceDir;
    };
}

#define TT_COLOR(arg)   XP::CUiResource::instance()->getColor(arg)
#define TT_FONT(arg)    XP::CUiResource::instance()->getFont(arg)
#define TT_PIXMAP(arg)  XP::CUiResource::instance()->getPixmap(arg)
#define TT_ICON(arg)    XP::CUiResource::instance()->getIcon(arg)
#define TT_SIZE(arg)    XP::CUiResource::instance()->getSize(arg)
#define TT_SOUND(arg)   XP::CUiResource::instance()->getSound(arg)
#define TT_STATICTEXT(arg1, arg2)   XP::CUiResource::instance()->getStaticText(arg1, arg2)
#define TT_IMAGESHEET(arg)          XP::CUiResource::instance()->getImageSheet(arg)
#define TT_COLORSHEET(arg)          XP::CUiResource::instance()->getColorSheetByKey(arg)
#endif
