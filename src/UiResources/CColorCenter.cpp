/**
 *  管理所有颜色
 */

#include <UiResources/CColorCenter.h>
#include <QtXml/QDomDocument>
#include <QFile>

namespace XP
{
    CColorCenter::CColorCenter()
        : m_strSchemeName(""),
        m_nSchemeID(-1),
        m_defaultColor()
    {

    }

    CColorCenter::~CColorCenter()
    {
        m_colorMap.clear();
    }

    void CColorCenter::parse(QString qsXml)
    {
        //QString qsFileName = XP::getResourceDir() + QDir::separator() + "theme" + QDir::separator() + qsThemeName + QDir::separator() + "color.xml";
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
            while (node.nodeName() != "colorscheme")
            {
                node = node.nextSibling();
            }

            QDomElement rootElement = node.toElement();
            m_strSchemeName = rootElement.attribute("name");
            m_nSchemeID = rootElement.attribute("id").toInt();

            for (QDomElement element = node.firstChildElement(); element.nodeName() == "color"; element = element.nextSiblingElement())
            {
                QDomAttr attr = element.attributeNode("name");
                QString qsColorName = attr.nodeValue();
                QString qsColorValue = element.text();
                QStringList colorItemList = qsColorValue.split(",");

                if (
                    colorItemList.size() != 4
                    && colorItemList.size() != 3
                    )
                {
                    continue;
                }

                int r = colorItemList[0].toInt();
                int g = colorItemList[1].toInt();
                int b = colorItemList[2].toInt();
                if (colorItemList.size() == 4)
                {
                    int a = colorItemList[3].toInt();
                    setColor(qsColorName, r, g, b, a);
                }
                else
                {
                    setColor(qsColorName, r, g, b, 0xff);
                }
            }
        }

        qFile.close();
    }

    const QColor * CColorCenter::registerCustomColor(const QColor & clr)
    {
        QString key = colorKey(clr);
        m_customedColors[key] = clr;
        return &(m_customedColors[key]);
    }

    const QColor * CColorCenter::getColor(QString qsKey) const
    {
        QMap<QString, QColor>::const_iterator cIter = m_colorMap.find(qsKey);
        if (cIter != m_colorMap.end())
        {
            return &(*cIter);
        }
        return &m_defaultColor;
    }

    void CColorCenter::setColor(QString qsKey, int r, int g, int b, int a)
    {
        m_colorMap[qsKey] = QColor(r, g, b, a);
    }

    QString CColorCenter::colorKey(const QColor & clr) const
    {
        return QString::number(clr.red()) + "," + QString::number(clr.green())
            + "," + QString::number(clr.blue()) + "," + QString::number(clr.alpha());
    }

    QString CColorCenter::getColorSheet(const QColor *pColor) const
    {
        if (NULL != pColor)
        {
            return "rgba(" + QString::number(pColor->red()) + ", " + QString::number(pColor->green()) + ", " + QString::number(pColor->blue()) + ", " + QString::number(pColor->alpha()) + ")";
        }
        return "";
    }

}