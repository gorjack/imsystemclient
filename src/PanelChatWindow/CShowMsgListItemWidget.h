#ifndef CSHOWMSGLISTITEMWIDGET_H
#define CSHOWMSGLISTITEMWIDGET_H

#include <QtWidgets/QWidget>
#include <User/userdatas.h>

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;
class QPushButton;

class CShowMsgListItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CShowMsgListItemWidget(QWidget *parent = nullptr);

    enum User_Type {
        User_System,//系统
        User_Me,    //自己
        User_She,   //用户
        User_Time,  //时间
    };
    void setTextSuccess();
    void setText(QString text, QString time, QSize allSize, User_Type userType);

    QSize getRealString(QString src);
    QSize fontRect(QString str);

    inline QString text() { return m_msg; }
    inline QString time() { return m_time; }
    inline User_Type userType() { return m_userType; }
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    QString m_msg;
    QString m_time;
    QString m_curTime;

    QSize m_allSize;
    User_Type m_userType = User_System;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_sanjiaoLeftRect;
    QRect m_sanjiaoRightRect;
    QRect m_kuangLeftRect;
    QRect m_kuangRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;
    QPixmap m_leftPixmap;
    QPixmap m_rightPixmap;
    QLabel* m_loading = Q_NULLPTR;
    QMovie* m_loadingMovie = Q_NULLPTR;
    bool m_isSending = false;
};

struct FileDataItem
{
    QString strfileType;
    QString strFileName;
    QString strFileSize;
    QString strFileInfo;
    QString m_time;
};

class CShowSingleFileItemWidget : public QWidget
{
public:
    explicit CShowSingleFileItemWidget(ChatFileDirection type, QWidget *parent = nullptr);

    void setDataItem(const FileDataItem& data);
    inline QString time() { return m_time; }
protected:
    void createUi(ChatFileDirection type);
    void paintEvent(QPaintEvent *event);
    void loadStyleSheet(const QString &sheetName);

private:
    QPushButton            *m_pOpenBtn = NULL;
    QPushButton            *m_pOpenDirBtn = NULL;
    QPushButton            *m_pRepeatDownBtn = NULL;
    QPushButton            *m_pTransmitBtn = NULL;
    QPushButton            *m_pOtherBtn = NULL;
    QPushButton            *m_pHeaderImgBtn = NULL;

    QPushButton            *m_pFileTypeStateImg = NULL;

    QLabel                 *m_pFileTypeImg = NULL;
    QLabel                 *m_pFileName = NULL;
    QLabel                 *m_pFileSize = NULL;
    QLabel                 *m_pFileInfo = NULL;

    QString                 m_time;
};

class CShowTransferFileItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CShowTransferFileItemWidget(ChatFileDirection type, QWidget *parent = nullptr);

    void setDataItem(const FileDataItem& data) { m_pItemWidget->setDataItem(data); }
    inline QString time() { return m_pItemWidget->time(); }
protected:
    void createUi(ChatFileDirection type);

private:
    CShowSingleFileItemWidget  *m_pItemWidget = NULL;
};

#endif 