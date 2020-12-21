#ifndef CUSERDATAWIDGETITEM_H
#define CUSERDATAWIDGETITEM_H

#include <QtWidgets/QWidget>
#include <QPixmap>

class CUserDataWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit CUserDataWidgetItem(QWidget *parent = nullptr);

    void setMessageText(const QString& msg);
    void setHeadIcon(const QString& strHead);
    void setDelIcon(const QString& strDel);
Q_SIGNALS:
    void sigClose();

protected Q_SLOTS:

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    QString                 m_strText;
    QRect                   m_textRect;

    QRect                   m_headIcon;
    QPixmap                 m_headPng;

    QRect                   m_delIcon;
    QPixmap                 m_delPng;

    bool                    m_bShowDel = false;

};

#endif 