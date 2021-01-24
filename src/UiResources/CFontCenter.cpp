/**
 *  字体中心
 */

#include <UiResources/CFontCenter.h>
#include <QtXml/QDomDocument>
#include <QFile>

namespace XP
{
    CFontCenter::CFontCenter()
        : m_strSchemeName(""),
        m_nSchemeID(-1),
        m_defaultFont(),
        m_bAutoAdapt(false),
        m_dAdaptFactor(1.0)
    {
        
    }

    CFontCenter::~CFontCenter()
    {
        
    }
    
    void CFontCenter::setAutoAdapt( bool bAutoAdapt, float dFactor )
    {
        m_bAutoAdapt = bAutoAdapt;
        m_dAdaptFactor = dFactor;
    }

/*
    void CFontCenter::init()
    {
        QFont::insertSubstitution("微软雅黑", "黑体");
        parseTheme("default");
    }
*/

    void CFontCenter::parse(QString qsXml)
    {
/*
        QString qsFileName = XP::getResourceDir() + QDir::separator() + "font" + QDir::separator() + qsThemeName + QDir::separator() + "font.xml";
*/
        QDomDocument xmlDomParser;
        QFile qFile(qsXml);

        if (!qFile.open(QIODevice::ReadOnly))
        {
            return;
        }

        if (!xmlDomParser.setContent(&qFile))
        {
            return;
        }

        QDomNode node = xmlDomParser.firstChild();
        if (!node.isNull()) 
        {
            while (node.nodeName() != "fontscheme")
            {
                node = node.nextSibling();
            }

            QDomElement rootElement = node.toElement();
            m_strSchemeName = rootElement.attribute("name");
            m_nSchemeID = rootElement.attribute("id").toInt();

            for (QDomElement element = node.firstChildElement(); element.nodeName() == "font"; element = element.nextSiblingElement())
            {
                QString fontName = element.attributeNode("name").nodeValue();
                QString family = element.attributeNode("family").nodeValue();
                int size = element.attributeNode("size").nodeValue().toInt();
                int weight = element.attributeNode("weight").nodeValue().toInt();
                int italic = element.attributeNode("italic").nodeValue().toInt();
                int underline = element.attributeNode("underline").nodeValue().toInt();

                if (m_bAutoAdapt)
                {
                    size = m_dAdaptFactor * size;
                }

                setFont(fontName, family, size, weight, italic, underline);
            }

            const QFont *pFont = getFont("fnt_default_large");
            if (NULL != pFont)
            {
                m_defaultFont = *pFont;
            }
        }

        qFile.close();
    }

    const QFont * CFontCenter::registerCustomFont( const QFont & fnt )
    {
        QString key = fontKey(fnt);
        m_customedFonts[key] = fnt;
        return &(m_customedFonts[key]);
    }

    QString CFontCenter::registerCustomFontKey( const QFont & fnt )
    {
        QString key = fontKey(fnt);
        m_customedFonts[key] = fnt;
        return key;
    }

    const QFont * CFontCenter::getCustomerFont( QString qsKey ) const
    {
        QMap<QString, QFont>::const_iterator cIter = m_customedFonts.find(qsKey);
        if (cIter != m_customedFonts.end())
        {
            return &(*cIter);
        }
        return NULL;
    }

    const QFont * CFontCenter::getFont( QString qsKey ) const
    {
        QMap<QString, QFont>::const_iterator cIter = m_fontMap.find(qsKey);
        if (cIter != m_fontMap.end())
        {
            return &(*cIter);
        }

        QMap<QString, QFont>::const_iterator cIter1 = m_customedFonts.find(qsKey);
        if (cIter1 != m_customedFonts.end())
        {
            return &(*cIter1);
        }
        return &m_defaultFont;
    }

    QString CFontCenter::getFontSheet( const QFont *pFont ) const
    {
        if (NULL != pFont)
        {
            return QString(pFont->bold() ? "bold " : "") + QString(pFont->italic() ? "italic " : "") + QString::number(pFont->pixelSize()) + "px \"" + pFont->family() + "\"";
        }
        return "";
    }

    void CFontCenter::setFont(
        QString qsKey, QString qsFamily,
        int pixelSize, int weight, bool italic, bool underline
        )
    {
        QFont font(qsFamily, -1, weight, italic);
        font.setUnderline(underline);
        font.setPixelSize(pixelSize);
        m_fontMap[qsKey] = font;
    }

    QString CFontCenter::fontKey( const QFont & fnt ) const
    {
        return fnt.family() + "," + QString::number(fnt.weight())
            + "," + QString::number(fnt.pixelSize())
            + "," + QString::number(fnt.weight())
            + "," + QString::number(fnt.italic() ? 1 : 0)
            + "," + QString::number(fnt.underline() ? 1 : 0);
    }

}

