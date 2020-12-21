#include "CPushButton.h"
#include <QtGui/QBitmap>
#include <QFile>
#include <QByteArray>
#include <Env/directory.h>
#include <QPainter>
#include <string>

namespace QF
{
    EventDeliver::EventDeliver(EventDeliver* parent)
        : m_pParent(parent)
    {

    }

    void EventDeliver::deliverEvent(int nEventId, int nSendId)
    {
        if (NULL != m_pParent)
        {
            if (!m_pParent->handleEvent(nEventId, nSendId))
            {
                m_pParent->deliverEvent(nEventId, nSendId);
            }
        }
    }

    bool EventDeliver::handleEvent(int nEventId, int nSendId)
    {
        return false;
    }

    EventDeliver * castEventDeliverer(QWidget *pWidget)
    {
        return dynamic_cast<EventDeliver *>(pWidget);
    }

    CPushButton::CPushButton(int nId, QWidget* parent, QString strImage)
        : QPushButton(parent)
        , EventDeliver(castEventDeliverer(parent))
        , m_nId(nId)
        , m_strImage(strImage)
    {
    }

    CPushButton::CPushButton(QWidget* parent /*= NULL*/)
        : QPushButton(parent)
        , EventDeliver(castEventDeliverer(parent))
    {
        connect(this, SIGNAL(clicked(bool)), SLOT(slotClicked(bool)));
    }

    void CPushButton::setImageKey(const QString& imageKey)
    {
        QString fileName = QF::getRootDir() + QDir::separator() + "resource" + QDir::separator() + imageKey;
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();

            if (m_pixmap.loadFromData(data))
            {
                m_str2Image.insert(m_eTatus, m_pixmap);
            }
            else
            {
                //error do something to handle the error
            }

            file.close();
            return;
        }
    }

    void CPushButton::init(const QStringList& strList)
    {
        std::string& strPath = QF::getRootDir().toStdString();
        std::string strFileName;

        for (int i = 0; i < strList.size(); ++i)
        {
            strFileName = strPath.substr(0, strPath.find_last_of("\\")) + "\\" + "resources" + "\\" + strList.at(i).toStdString();
            QFile file(QString::fromLocal8Bit(strFileName.c_str()));
            if (file.open(QIODevice::ReadOnly))
            {
                QByteArray ret = file.readAll();
                file.close();

                QPixmap pixTemp;
                pixTemp.loadFromData(ret);
                m_str2Image.insert(i, pixTemp);
            }
        }
    }

    void CPushButton::setMessage(const QString& msg)
    {
        m_strMessage = msg;
    }

    void CPushButton::slotClicked(bool)
    {
        emit sigClicked(m_strMessage);
    }

    void CPushButton::paintEvent(QPaintEvent *ev)
    {
        //QPushButton::paintEvent(e);
        //QPainter painter(this);
        //if (!m_pixmap.isNull())
        //{
        //    painter.drawPixmap(0, 0, m_pixmap);
        //}
        QPushButton::paintEvent(ev);

        QPainter painter(this);
        QMap<int, QPixmap>::iterator iter = m_str2Image.find(m_eTatus);
        if (iter != m_str2Image.end())
        {
            painter.drawPixmap(0, 0, iter.value());
        }
    }

    void CPushButton::enterEvent(QEvent *e)
    {
        m_eTatus = TPS_HOVER;

        QPushButton::enterEvent(e);
    }

    void CPushButton::leaveEvent(QEvent *e)
    {
        if (m_eTatus != TPS_NORMAL)
        {
            m_eTatus = TPS_NORMAL;
        }
        QPushButton::leaveEvent(e);

    }

    void CPushButton::mousePressEvent(QMouseEvent *e)
    {
        if (m_eTatus != TPS_DOWN)
        {
            m_eTatus = TPS_DOWN;
        }
        QPushButton::mousePressEvent(e);
        deliverEvent(EVENT_PUSHBUTTON_CLICK, m_nId);
    }

    void CPushButton::mouseReleaseEvent(QMouseEvent *e)
    {
        if (m_eTatus != TPS_HOVER)
        {
            m_eTatus = TPS_HOVER;
        }

        QPushButton::mouseReleaseEvent(e);

    }
}