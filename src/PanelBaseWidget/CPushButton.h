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
#include <UiEvent/CEventDeliverer.h>

namespace PC
{
    enum ButtonStatus
    {
        TPS_NORMAL = 0,
        TPS_HOVER,
        TPS_DOWN,
    };

    class PANELBASEWIDGET_EXPORT CPushButton : public QPushButton, public CEventDeliverer
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

        void enterEvent(QEvent *e);
        void leaveEvent(QEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);

        int          m_nId;
        QString      m_strImage;
        QPixmap      m_pixmap;

        ButtonStatus                m_eTatus = TPS_NORMAL;
        QMap<int, QPixmap>          m_str2Image;
        QString                     m_strMessage;
    };
}