/**
 *  播放声音
 */

#ifndef XP_UIRESOURCE_CSOUNDCENTER_H
#define XP_UIRESOURCE_CSOUNDCENTER_H

#include <QString>
#include <QMap>
#include <QString>
#include <QtMultimedia/QSound>

namespace XP
{
    class DLL_EXPORT_UIRESOURCE CSoundCenter
    {
    public:
        CSoundCenter();
        virtual ~CSoundCenter();

        void parse(QString qsDir);

        QList<QString> getAllSoundKeys() const;

        QSound * getSound(QString qsKey);
        QString getSoundPath(QString qsKey);

    protected:
        void setSound(QString qsKey, QString qsSoundFile);

        QString                 m_strSchemeName;
        int                     m_nSchemeID;
        mutable QMap<QString, QSound *> m_soundMap;
        QMap<QString, QString>  m_keyToSoundPath;

        QSound m_defaultSound;
    };
}

#endif
