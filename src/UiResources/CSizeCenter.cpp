/**
 *  尺寸中心
 */

#include <UiResources/CSizeCenter.h>
#include <QtXml/QDomDocument>
#include <QFile>

namespace XP
{
    
    CSizeCenter::CSizeCenter()
        : m_strSchemeName(""),
        m_nSchemeID(-1),
        m_nDefaultSize(0)
    {

    }  

    CSizeCenter::~CSizeCenter()
    {

    }

    void CSizeCenter::parse( QString qsXml )
    {
/*
        QString qsFileName = XP::getResourceDir() + QDir::separator() + "font" + QDir::separator() + qsThemeName + QDir::separator() + "size.xml";
*/
        QDomDocument xmlDomParser;
        QFile qFile(qsXml);

        if (!qFile.open(QIODevice::ReadOnly))
        {
            return;
        }

        if (!xmlDomParser.setContent(&qFile))
        {
            qFile.close();
            return;
        }

        QDomNode node = xmlDomParser.firstChild();
        if (!node.isNull()) 
        {
            while (node.nodeName() != "sizescheme")
            {
                node = node.nextSibling();
            }

            QDomElement rootElement = node.toElement();
            m_strSchemeName = rootElement.attribute("name");
            m_nSchemeID = rootElement.attribute("id").toInt();

            for (QDomElement element = node.firstChildElement(); element.nodeName() == "size"; element = element.nextSiblingElement())
            {
                QDomAttr attr = element.attributeNode("name");
                QString qsSizeName = attr.nodeValue();

                int nSize = element.text().toInt();

                setSize(qsSizeName, nSize);
            }
        }

        qFile.close();
    }

/*
    void CSizeCenter::init()
    {
        parseTheme("default");
    }
*/

    int CSizeCenter::getSize( QString qsKey ) const
    {
        QMap<QString, int>::const_iterator cIter = m_sizeMap.find(qsKey);
        if (cIter != m_sizeMap.end())
        {
            return *cIter;
        }
        return m_nDefaultSize;
    }

    void CSizeCenter::setSize( QString qsKey, int nSize )
    {
        m_sizeMap[qsKey] = nSize;
    }
}
