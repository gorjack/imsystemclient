/**
 *  播放声音
 */

#include <UiResources/CSoundCenter.h>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QFileInfoList>
#include <QDir>

namespace XP
{

    CSoundCenter::CSoundCenter()
        : m_defaultSound("")
    {

    }

    CSoundCenter::~CSoundCenter()
    {

    }

    void CSoundCenter::parse( QString qsDir )
    {
        m_soundMap.clear();

        QDir qDir(qsDir);
        QFileInfoList fileInfoList = qDir.entryInfoList();
        for (int i = 0; i < fileInfoList.size(); i++)
        {
            QFileInfo& fileInfo = fileInfoList[i];
            if (fileInfo.isFile())
            {
                if (fileInfo.suffix().toLower() == "wav")
                {
                    setSound(fileInfo.baseName(), fileInfo.absoluteFilePath());
                }
            }
        }
    }

    QList<QString> CSoundCenter::getAllSoundKeys() const
    {
        return m_keyToSoundPath.keys();
    }

    QSound * CSoundCenter::getSound( QString qsKey )
    {
        QMap<QString, QSound *>::iterator iter = m_soundMap.find(qsKey);
        if (m_soundMap.end() != iter)
        {
            return *iter;
        }
        QMap<QString, QString>::const_iterator sIter = m_keyToSoundPath.find(qsKey);
        if (m_keyToSoundPath.end() != sIter)
        {
            m_soundMap[qsKey] = new QSound(*sIter);
            return m_soundMap[qsKey];
        }
        return &m_defaultSound;
    }

    void CSoundCenter::setSound( QString qsKey, QString qsSoundFile )
    {
        m_keyToSoundPath[qsKey] = qsSoundFile;
    }
    
    QString CSoundCenter::getSoundPath(QString qsKey)
    {
        if (m_keyToSoundPath.contains(qsKey))
        {
            return m_keyToSoundPath[qsKey];
        }
        return "";
    }
}
