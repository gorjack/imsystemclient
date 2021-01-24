/**
 *  ui资源管理类
 *
 */

#include <UiResources/CUiResource.h>
#include <UiResources/CColorCenter.h>
#include <UiResources/CFontCenter.h>
#include <UiResources/CImageCenter.h>
#include <UiResources/CSizeCenter.h>
#include <UiResources/CSoundCenter.h>
#include <UiResources/CTextEngine.h>
#include <utils/CSingletonT.hpp>
#include <utils/commonFunc.h>


IMPL_SINGLETON_CLASS(XP::CUiResource);

namespace XP
{

    CUiResource::CUiResource()
        : m_pColorCenter(NULL)
        , m_pImageCenter(NULL)
        , m_pFontCenter(NULL)
        , m_pSizeCenter(NULL)
        , m_pTextEngine(NULL)
        , m_pSoundCenter(NULL)
    {
        m_pColorCenter = new CColorCenter();
        m_pImageCenter = new CImageCenter();
        m_pFontCenter = new CFontCenter();
        m_pSizeCenter = new CSizeCenter();
        m_pSoundCenter = new CSoundCenter();
        m_pTextEngine = new CTextEngine();
    }

    CUiResource::~CUiResource()
    {
        utils::safeDeletePtr(m_pColorCenter);
        utils::safeDeletePtr(m_pImageCenter);
        utils::safeDeletePtr(m_pFontCenter);
        utils::safeDeletePtr(m_pSizeCenter);
        utils::safeDeletePtr(m_pSoundCenter);
        utils::safeDeletePtr(m_pTextEngine);
    }

    void CUiResource::parseColor( QString qsXml )
    {
        if (NULL != m_pColorCenter)
        {
            m_pColorCenter->parse(qsXml);
        }
    }

    void CUiResource::parseFont( QString qsXml )
    {
        if (NULL != m_pFontCenter)
        {
            m_pFontCenter->parse(qsXml);
        }
    }

    void CUiResource::parseImage( QString qsDir )
    {
        if (NULL != m_pImageCenter)
        {
            m_pImageCenter->parse(qsDir);
        }
    }

    void CUiResource::reParseImage(QString qsDir, QString qsKey)
    {
        if (NULL != m_pImageCenter)
        {
            m_pImageCenter->reParseImage(qsDir, qsKey);
        }
    }

    void CUiResource::parseSize( QString qsXml )
    {
        if (NULL != m_pSizeCenter)
        {
            m_pSizeCenter->parse(qsXml);
        }
    }

    void CUiResource::parseSound( QString qsDir )
    {
        if (NULL != m_pSoundCenter)
        {
            m_pSoundCenter->parse(qsDir);
        }
    }

    void CUiResource::setThemeImageDir( QString qsDir )
    {
        m_qsThemeImageDir = qsDir;
    }

    QString CUiResource::getThemeImageDir() const
    {
        return m_qsThemeImageDir;
    }

    const QColor * CUiResource::registerCustomColor( const QColor & clr )
    {
        return (NULL != m_pColorCenter) ? m_pColorCenter->registerCustomColor(clr) : NULL;
    }

    const QColor * CUiResource::getColor( QString qsKey ) const
    {
        return (NULL != m_pColorCenter) ? m_pColorCenter->getColor(qsKey) : NULL;
    }

    QString CUiResource::getColorSheet( const QColor *pColor ) const
    {
        return (NULL != m_pColorCenter) ? m_pColorCenter->getColorSheet(pColor) : "";
    }

    QString CUiResource::getColorSheetByKey( QString qsKey ) const
    {
        return (NULL != m_pColorCenter) ? m_pColorCenter->getColorSheet(getColor(qsKey)) : "";
    }

    const QFont * CUiResource::registerCustomFont( const QFont & fnt )
    {
        return (NULL != m_pFontCenter) ? m_pFontCenter->registerCustomFont(fnt) : NULL;
    }

    QString CUiResource::registerCustomFontKey( const QFont & fnt )
    {
        return (NULL != m_pFontCenter) ? m_pFontCenter->registerCustomFontKey(fnt) : NULL;
    }
    
    const QFont * CUiResource::getCustomerFont( QString qsKey ) const
    {
        return (NULL != m_pFontCenter) ? m_pFontCenter->getCustomerFont(qsKey) : NULL;
    }

    const QFont * CUiResource::getFont( QString qsKey ) const
    {
        return (NULL != m_pFontCenter) ? m_pFontCenter->getFont(qsKey) : NULL;
    }

    QString CUiResource::getFontSheet( const QFont *pFont ) const
    {
        return (NULL != m_pFontCenter) ? m_pFontCenter->getFontSheet(pFont) : "";
    }

    const QPixmap * CUiResource::getPixmap( QString qsKey ) const
    {
        return (NULL != m_pImageCenter) ? m_pImageCenter->getPixmap(qsKey) : NULL;
    }

    const QIcon * CUiResource::getIcon( QString qsKey ) const
    {
        return (NULL != m_pImageCenter) ? m_pImageCenter->getIcon(qsKey) : NULL;
    }

    void CUiResource::initPostfix( const QFont & fnt )
    {
        if (NULL != m_pTextEngine)
        {
            m_pTextEngine->initPostfix(fnt);
        }
    }

    const QVector<const QStaticText *> & CUiResource::getPostFix() const
    {
        return (NULL != m_pTextEngine) ? m_pTextEngine->getPostFix() : m_fuck;
    }

    const QStaticText * CUiResource::getStaticText( const QString & qsText, const QFont & fnt )
    {
        return (NULL != m_pTextEngine) ? m_pTextEngine->getStaticText(qsText, fnt) : NULL;
    }

    int CUiResource::getSize( QString qsKey ) const
    {
        return (NULL != m_pSizeCenter) ? m_pSizeCenter->getSize(qsKey) : NULL;
    }

    QString CUiResource::getImageSheet(QString qsKey) const
    {
        return (NULL != m_pImageCenter) ? m_pImageCenter->getStyleSheetUrl(qsKey) : "";
    }

    QList<QString> CUiResource::getAllSoundKeys() const
    {
        return (NULL != m_pSoundCenter) ? m_pSoundCenter->getAllSoundKeys() : QList<QString>();
    }

    QSound * CUiResource::getSound( QString qsKey )
    {
        return (NULL != m_pSoundCenter) ? m_pSoundCenter->getSound(qsKey) : NULL;
    }

    QString CUiResource::getSoundPath(QString qsKey)
    {
        return (NULL != m_pSoundCenter) ? m_pSoundCenter->getSoundPath(qsKey) : "";
    }

    void CUiResource::setAutoAdapt( bool bAutoAdapt, float dFactor)
    {
        if (NULL != m_pFontCenter)
        {
            m_pFontCenter->setAutoAdapt(bAutoAdapt, dFactor);
        }
    }
}
