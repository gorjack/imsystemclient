/**
 *  声音播放器
 *
 */

#ifndef XP_UIRESOURCE_CSOUNDPLAYER_H
#define XP_UIRESOURCE_CSOUNDPLAYER_H

#include <utils/CSingletonT.h>
#include <QObject>
#include <QtMultimedia/QSound>
#include <boost/thread.hpp>

#include <QString>
#include <QMap>
#include <QQueue>
#include <QString>
#include <QMutex>

namespace XP
{
    class DLL_EXPORT_UIRESOURCE CSoundPlayer : public QObject, public utils::CSingletonT<CSoundPlayer>
    {
        Q_OBJECT

    public:
        CSoundPlayer();
        virtual ~CSoundPlayer();
        void play(const QString &key);
        void soundSwitch(bool bRun);
        void setBoolPlay(bool bPlay){m_bPlay = bPlay;}
        bool getBoolPlay(){return m_bPlay;}

    Q_SIGNALS:
        void sigSoundSwitch(bool);

    protected Q_SLOTS:
        void slotSoundSwitch(bool bRun);

    protected:
        void run();

    protected:
        bool m_bPlay;               //是否运行运维警报
        boost::thread * m_pPlayThread;

        QMutex m_soundMutex;
        QSound* m_pSound;

        QMutex m_queueMutex;
        QQueue<QString> m_soundQueue;
    };
}

#endif
