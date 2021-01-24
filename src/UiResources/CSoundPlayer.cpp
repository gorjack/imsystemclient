#include "UiResources/CSoundPlayer.h"
#include <UiResources/CUiResource.h>
#include <utils/CSingletonT.hpp>
#include <algorithm>
#include <utils/commonFunc.h>

IMPL_SINGLETON_CLASS(XP::CSoundPlayer);

namespace XP
{
    CSoundPlayer::CSoundPlayer()
        : m_queueMutex(QMutex::Recursive)
        , m_soundMutex(QMutex::Recursive)
        , m_pPlayThread(NULL)
        , m_pSound(NULL)
        , m_bPlay(false)
    {
        connect(this, SIGNAL(sigSoundSwitch(bool)), this, SLOT(slotSoundSwitch(bool)));
        if (NULL == m_pPlayThread)
        {
            m_pPlayThread = new boost::thread(boost::bind(&CSoundPlayer::run, this));
        }
    }

    CSoundPlayer::~CSoundPlayer()
    {

    }

    void CSoundPlayer::play(const QString &key)
    {
        QString qsSoundDir = CUiResource::instance()->getSoundPath(key);
        if (!qsSoundDir.isEmpty())
        {
            QMutexLocker locker(&m_queueMutex);
            m_soundQueue.enqueue(key);
        }
    }

    void CSoundPlayer::soundSwitch(bool bRun)
    {
        emit sigSoundSwitch(bRun);
    }

    void CSoundPlayer::run()
    {
        while (true)
        {
            QString qsKey = "";
            QString qsSoundDir = "";
            {
                QMutexLocker locker(&m_queueMutex);
                if (m_soundQueue.empty())
                {
                   // Sleep(100);
                    continue;
                }
                qsKey = m_soundQueue.dequeue();
                qsSoundDir = CUiResource::instance()->getSoundPath(qsKey);
                while(!m_soundQueue.empty() && m_soundQueue.first() == qsKey)
                {
                    m_soundQueue.dequeue();
                }
            }

            int nPlayTime = std::max(utils::getWavFileTimeSpan(qsSoundDir), 0);
            {
                QMutexLocker locker(&m_soundMutex);
                m_pSound = TT_SOUND(qsKey);
            }
            soundSwitch(true);
          //  Sleep(nPlayTime * 1000);
        }
    }

    void CSoundPlayer::slotSoundSwitch(bool bRun)
    {
        QMutexLocker locker(&m_soundMutex);
        if (m_pSound != NULL)
        {
            if (bRun)
            {
                m_pSound->play();
            }
            else
            {
                m_pSound->stop();
                m_pSound = NULL;
            }
        }
    }

}
