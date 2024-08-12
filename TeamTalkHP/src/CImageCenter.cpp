/**
 *  图片资源中心
 *
 */

#include "CImageCenter.h"
#include <QtXml/QDomDocument>
#include <QFile>
#include <QFileInfoList>
#include <QDir>
#include <iostream>
#include "utils/IULog.h"

CImageCenter::CImageCenter()
    : m_defaultPixmap(0, 0)
{
    m_defaultImage.fill(0);
    m_defaultPixmap.fill(QColor(0, 0, 0));
    m_defaultIcon.addPixmap(m_defaultPixmap);
}

CImageCenter::~CImageCenter()
{

}

/*
    void CImageCenter::init()
    {
        parseTheme("default");
    }

    void CImageCenter::parseTheme( QString qsThemeName )
    {
        m_strSchemeName = qsThemeName;
        QString qsDirName = XP::getResourceDir() + QDir::separator() + "theme" + QDir::separator() + qsThemeName;
        parseDir(qsDirName);

        // 一些和界面主题无关的图标资源
        qsDirName = XP::getResourceDir() + QDir::separator() + "global";
        parseDir(qsDirName);
    }
*/

void CImageCenter::parse(QString qsDir)
{
	static QString strDir;

	if (strDir != qsDir)
	{
		strDir = qsDir;
	}
	else
	{
		m_pixmapMap.clear();
		m_iconMap.clear();
	}

    QDir qDir(strDir);
    QFileInfoList fileInfoList = qDir.entryInfoList();
    for (int i = 0; i < fileInfoList.size(); i++)
    {
        QFileInfo& fileInfo = fileInfoList[i];
        if (fileInfo.isFile())
        {
            if (fileInfo.suffix().toLower() == "png")
            {
                setImage(fileInfo.baseName(), fileInfo.absoluteFilePath());
            }
        }
    }
}

QPixmap* CImageCenter::getPixmap(QString qsKey)
{
	QMap<QString, QPixmap>::iterator cIter = m_pixmapMap.find(qsKey);
	if (m_pixmapMap.end() != cIter)
	{
		return &(*cIter);
	}
	QMap<QString, QString>::iterator sIter = m_keyToImagePath.find(qsKey);
    if (m_keyToImagePath.end() != sIter)
    {
        QPixmap pImage;
        QFile file(*sIter);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();

            if (!pImage.loadFromData(data))
            {
                bool temp1 = pImage.load(*sIter);
                std::string temp = (*sIter).toStdString();
                std::cout << "file read error" << (*sIter).toStdString();
            }
        }
        file.close();

        m_pixmapMap[qsKey] = pImage;
        return &m_pixmapMap[qsKey];
    }
    return NULL;
}

const QIcon* CImageCenter::getIcon(QString qsKey) const
{
    QMap<QString, QIcon>::const_iterator cIter = m_iconMap.find(qsKey);
    if (m_iconMap.end() != cIter)
    {
        return &(*cIter);
    }
    QMap<QString, QString>::const_iterator sIter = m_keyToImagePath.find(qsKey);
    if (m_keyToImagePath.end() != sIter)
    {
        QIcon p(*sIter);
        m_iconMap[qsKey] = p;
        return &m_iconMap[qsKey];
    }
    return &m_defaultIcon;
}

void CImageCenter::setImage(QString qsKey, QString qsImageFile)
{
    LOG_INFO("qsImageFile :%s", qsImageFile.toStdString().c_str());
    m_keyToImagePath[qsKey] = qsImageFile;
}

QString CImageCenter::getStyleSheetUrl(QString qsKey) const
{
    QString qsRelativePath = "";
    if (m_keyToImagePath.contains(qsKey))
    {
        qsRelativePath = QDir::current().relativeFilePath(m_keyToImagePath[qsKey]);
    }

    return QString("image: url(%1)").arg(qsRelativePath);
}

void CImageCenter::reParseImage(QString qsDir, QString qsKey)
{
    if (m_pixmapMap.end() != m_pixmapMap.find(qsKey))
    {
        m_pixmapMap.remove(qsKey);
    }
    if (m_iconMap.end() != m_iconMap.find(qsKey))
    {
        m_iconMap.remove(qsKey);
    }
    QDir qDir(qsDir);
    QFileInfoList fileInfoList = qDir.entryInfoList();
    for (int i = 0; i < fileInfoList.size(); i++)
    {
        QFileInfo& fileInfo = fileInfoList[i];
        if (fileInfo.isFile())
        {
            if (fileInfo.baseName() == qsKey)
            {
                if (fileInfo.suffix().toLower() == "png")
                {
                    setImage(fileInfo.baseName(), fileInfo.absoluteFilePath());
                }
            }
        }
    }
}