/**
 *  管理所有颜色
 */

#ifndef XP_UIRESOURCE_CCOLORCENTER_H
#define XP_UIRESOURCE_CCOLORCENTER_H

#include <QString>
#include <QColor>
#include <QMap>

namespace XP
{
    class DLL_EXPORT_UIRESOURCE CColorCenter
    {
    public:
        CColorCenter();
        ~CColorCenter();

        void parse(QString qsXml);

        const QColor * registerCustomColor(const QColor & clr);

        // 获取颜色
        // 本函数的实现需保证返回指针不为空，调用者可直接取其地址。
        const QColor * getColor(QString qsKey) const;
        QString getColorSheet(const QColor *pColor) const;

    protected:
        void setColor(QString qsKey, int r, int g, int b, int a);

        QString colorKey(const QColor & clr) const;

        QString                 m_strSchemeName;
        int                     m_nSchemeID;
        QMap<QString, QColor>   m_colorMap;
        QColor                  m_defaultColor;

        QMap<QString, QColor>   m_customedColors;
    };
}

#endif
