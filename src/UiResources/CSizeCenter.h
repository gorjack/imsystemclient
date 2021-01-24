/**
 *  尺寸中心
 */

#ifndef XP_UIRESOURCE_CSIZECENTER_H
#define XP_UIRESOURCE_CSIZECENTER_H

#include <QString>
#include <QMap>
#include <QString>

namespace XP
{
    class DLL_EXPORT_UIRESOURCE CSizeCenter
    {
    public:
        CSizeCenter();
        ~CSizeCenter();

        void parse(QString qsXml);

        int getSize(QString qsKey) const;

    protected:
        void setSize(QString qsKey, int nSize);

        QString                 m_strSchemeName;
        int                     m_nSchemeID;
        QMap<QString, int>      m_sizeMap;
        int                     m_nDefaultSize;
    };
}

#endif
