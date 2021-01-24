/**
 *  字体中心
 */

#ifndef XP_UIRESOURCE_CFONTCENTER_H
#define XP_UIRESOURCE_CFONTCENTER_H

#include <QString>
#include <QMap>
#include <QFont>

namespace XP
{
    /**
     * 字体管理器
     */
    class DLL_EXPORT_UIRESOURCE CFontCenter
    {
    public:
        CFontCenter();
        ~CFontCenter();

        void setAutoAdapt(bool bAutoAdapt, float dFactor);

        void parse(QString qsXml);

        const QFont * registerCustomFont(const QFont & fnt);
        QString registerCustomFontKey(const QFont & fnt);

        // 获取字体
        // 本函数的实现需保证返回指针不为空，调用者可直接取其地址。
        const QFont * getFont(QString qsKey) const;
        const QFont * getCustomerFont( QString qsKey ) const;
        QString getFontSheet(const QFont *pFont) const;
        
    protected:
        void setFont(
            QString qsKey, QString qsFamily,
            int pixelSize, int weight, bool italic, bool underline
            );
        QString fontKey(const QFont & fnt) const;

        QString                 m_strSchemeName;
        int                     m_nSchemeID;
        QMap<QString, QFont>    m_fontMap;
        QFont                   m_defaultFont;
        QMap<QString, QFont>    m_customedFonts;
        bool                    m_bAutoAdapt;
        float                   m_dAdaptFactor;
    };
}

#endif
