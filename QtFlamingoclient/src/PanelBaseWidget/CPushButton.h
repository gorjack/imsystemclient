/** 
*      圆形的头像按钮
*      @auth gaojie
*      @time 20201118
*        
*/

#pragma once
#include <QtWidgets/QPushButton>
#include <QPixmap>
#include <QMap>

namespace QF
{
    enum ButtonStatus
    {
        TPS_NORMAL = 0,
        TPS_HOVER,
        TPS_DOWN,
    };

    enum EventId
    {
        EVENT_PUSHBUTTON_CLICK,
    };

    class PANELBASEWIDGET_EXPORT EventDeliver
    {
    public:
        EventDeliver(EventDeliver* parent);

    protected:
        void deliverEvent(int nEventId, int nSendId);
        virtual bool handleEvent(int nEventId, int nSendId);

        EventDeliver *m_pParent = NULL;
    };

    PANELBASEWIDGET_EXPORT EventDeliver *castEventDeliverer(QWidget *pWidget);

    class PANELBASEWIDGET_EXPORT CPushButton : public QPushButton, public EventDeliver
    {
        Q_OBJECT
    public:
        CPushButton(QWidget* parent = NULL);
        CPushButton(int nId, QWidget* parent = NULL, QString strImage = "");

        void init(const QStringList& strList);
        void setMessage(const QString& msg);

        void setImageKey(const QString& imageKey);

    Q_SIGNALS:
        void sigClicked(QString);
    protected Q_SLOTS:
        void slotClicked(bool);


    protected:
        void mousePressEvent(QMouseEvent *e);
        void paintEvent(QPaintEvent *e);

        int          m_nId;
        QString      m_strImage;
        QPixmap      m_pixmap;

        //---
        void enterEvent(QEvent *e);
        void leaveEvent(QEvent *e);
        //void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);

        ButtonStatus                m_eTatus = TPS_NORMAL;
        QMap<int, QPixmap>          m_str2Image;
        QString                     m_strMessage;
    };
}