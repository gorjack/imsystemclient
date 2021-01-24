/**
 *  图片资源中心
 */

#ifndef XP_UIRESOURCE_CIMAGECENTER_H
#define XP_UIRESOURCE_CIMAGECENTER_H
#include <QString>
#include <QMap>
#include <QIcon>
#include <QPixmap>
#include <QImage>

namespace XP
{
    class DLL_EXPORT_UIRESOURCE CImageCenter
    {          
    public:
        CImageCenter();
        virtual ~CImageCenter();

        void parse(QString qsDir);
        void reParseImage(QString qsDir, QString qsKey);
        
        // 获取图片
        // 本函数的实现需保证返回指针不为空，调用者可直接取其地址。
        const QPixmap * getPixmap(QString qsKey) const;
        const QIcon * getIcon(QString qsKey) const;

        QString getStyleSheetUrl(QString qsKey) const;

    protected:
        void setImage(QString qsKey, QString qsImageFile);

        QString                 m_strSchemeName;
        int                     m_nSchemeID;
        mutable QMap<QString, QPixmap>  m_pixmapMap;
        mutable QMap<QString, QIcon>    m_iconMap;
        QMap<QString, QString>  m_keyToImagePath;

        QImage m_defaultImage;
        QPixmap m_defaultPixmap;
        QIcon m_defaultIcon;
    }; 
}

#endif
