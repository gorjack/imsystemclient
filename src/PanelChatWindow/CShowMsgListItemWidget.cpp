#include "CShowMsgListItemWidget.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QtWidgets/QLabel>
#include <QDebug>
#include <Env/directory.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

CShowMsgListItemWidget::CShowMsgListItemWidget(QWidget *parent) : QWidget(parent)
{
    QFont te_font = this->font();
    te_font.setFamily("MicrosoftYaHei");
    te_font.setPointSize(12);
    //    te_font.setWordSpacing(0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing,0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing, 100);          //300%,100为默认  //设置字间距%
    //    te_font.setLetterSpacing(QFont::AbsoluteSpacing, 0);             //设置字间距为3像素 //设置字间距像素值
    this->setFont(te_font);
    m_leftPixmap = QPixmap(":/QQChatMessage/Resources/left.png");
    m_rightPixmap = QPixmap(":/QQChatMessage/Resources/right.png");

    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(QString("%1/loadinfo.gif").arg(QF::getCurrentResourceDir()));
    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16, 16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground, true);
    m_loading->setAutoFillBackground(false);
}

void CShowMsgListItemWidget::setTextSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void CShowMsgListItemWidget::setText(QString text, QString time, QSize allSize, CShowMsgListItemWidget::User_Type userType)
{
    m_msg = text;
    m_userType = userType;
    m_time = time;
    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("hh:mm");
    m_allSize = allSize;
    if (userType == User_Me) {
        if (!m_isSending) {
            m_loading->move(m_kuangRightRect.x() - m_loading->width() - 10, m_kuangRightRect.y() + m_kuangRightRect.height() / 2 - m_loading->height() / 2);
            m_loading->show();
            m_loadingMovie->start();
        }
    }
    else {
        m_loading->hide();
    }

    this->update();
}

QSize CShowMsgListItemWidget::fontRect(QString str)
{
    m_msg = str;
    int minHei = 30;
    int iconWH = 40;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 10;
    int sanJiaoW = 6;
    int kuangTMP = 20;
    int textSpaceRect = 12;

    m_kuangWidth = this->width() - kuangTMP - 2 * (iconWH + iconSpaceW + iconRectW);
    m_textWidth = m_kuangWidth - 2 * textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(m_msg); // 整个的size

    qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH + iconSpaceW + iconRectW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);

    if (size.width() < (m_textWidth + m_spaceWid)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2 * textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
            m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
    }
    else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x() + textSpaceRect, m_kuangLeftRect.y() + iconTMPH,
        m_kuangLeftRect.width() - 2 * textSpaceRect, m_kuangLeftRect.height() - 2 * iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x() + textSpaceRect, m_kuangRightRect.y() + iconTMPH,
        m_kuangRightRect.width() - 2 * textSpaceRect, m_kuangRightRect.height() - 2 * iconTMPH);

    return QSize(size.width(), hei);
}

QSize CShowMsgListItemWidget::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    int nCount = src.count("\n");
    int nMaxWidth = 0;
    if (nCount == 0) {
        nMaxWidth = fm.width(src);
        QString value = src;
        if (nMaxWidth > m_textWidth) {
            nMaxWidth = m_textWidth;
            int size = m_textWidth / fm.width(" ");
            int num = fm.width(value) / m_textWidth;
            int ttmp = num * fm.width(" ");
            num = (fm.width(value)) / m_textWidth;
            nCount += num;
            QString temp = "";
            for (int i = 0; i < num; i++) {
                temp += value.mid(i*size, (i + 1)*size) + "\n";
            }
            src.replace(value, temp);
        }
    }
    else {
        for (int i = 0; i < (nCount + 1); i++) {
            QString value = src.split("\n").at(i);
            nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
            if (fm.width(value) > m_textWidth) {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                num = ((i + num)*fm.width(" ") + fm.width(value)) / m_textWidth;
                nCount += num;
                QString temp = "";
                for (int i = 0; i < num; i++) {
                    temp += value.mid(i*size, (i + 1)*size) + "\n";
                }
                src.replace(value, temp);
            }
        }
    }
    return QSize(nMaxWidth + m_spaceWid, (nCount + 1) * m_lineHeight + 2 * m_lineHeight);
}

void CShowMsgListItemWidget::paintEvent(QPaintEvent *event)
{
#if 1
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if (m_userType == User_Type::User_She) { // 用户
        //头像
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x() - 1, m_kuangLeftRect.y() - 1, m_kuangLeftRect.width() + 2, m_kuangLeftRect.height() + 2, 4, 4);
        //框
        QColor col_Kuang(255, 255, 255);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect, 4, 4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoLeftRect.x(), 30),
            QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 25),
            QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //三角加边
        QPen penSanJiaoBian;
        penSanJiaoBian.setColor(col_KuangB);
        painter.setPen(penSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 36));

        //内容
        QPen penText;
        penText.setColor(QColor(51, 51, 51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textLeftRect, m_msg, option);
    }
    else if (m_userType == User_Type::User_Me) { // 自己
   //头像
//        painter.drawRoundedRect(m_iconRightRect,m_iconRightRect.width(),m_iconRightRect.height());
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //框
        QColor col_Kuang(75, 164, 242);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangRightRect, 4, 4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoRightRect.x() + m_sanjiaoRightRect.width(), 30),
            QPointF(m_sanjiaoRightRect.x(), 25),
            QPointF(m_sanjiaoRightRect.x(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //内容
        QPen penText;
        penText.setColor(Qt::white);
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRightRect, m_msg, option);
    }
    else if (m_userType == User_Type::User_Time) { // 时间
        QPen penText;
        penText.setColor(QColor(153, 153, 153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont te_font = this->font();
        te_font.setFamily("MicrosoftYaHei");
        te_font.setPointSize(10);
        painter.setFont(te_font);
        painter.drawText(this->rect(), m_curTime, option);
    }
#endif
}

void CShowMsgListItemWidget::resizeEvent(QResizeEvent *event)
{
    //这里为啥进不去
    QWidget::resizeEvent(event);
    if (m_msg.isEmpty())
    {
        return;
    }
    int minHei = 30;
    int iconWH = 40;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 10;
    int sanJiaoW = 6;
    int kuangTMP = 20;
    int textSpaceRect = 12;

    m_kuangWidth = this->width() - kuangTMP - 2 * (iconWH + iconSpaceW + iconRectW);
    m_textWidth = m_kuangWidth - 2 * textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(m_msg); // 整个的size

    qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH + iconSpaceW + iconRectW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);

    if (size.width() < (m_textWidth + m_spaceWid)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2 * textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
            m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
    }
    else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x() + textSpaceRect, m_kuangLeftRect.y() + iconTMPH,
        m_kuangLeftRect.width() - 2 * textSpaceRect, m_kuangLeftRect.height() - 2 * iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x() + textSpaceRect, m_kuangRightRect.y() + iconTMPH,
        m_kuangRightRect.width() - 2 * textSpaceRect, m_kuangRightRect.height() - 2 * iconTMPH);
}

CShowTransferFileItemWidget::CShowTransferFileItemWidget(ChatFileDirection type, QWidget *parent /*= nullptr*/)
    :QWidget(parent)
{
    createUi(type);
}

void CShowTransferFileItemWidget::createUi(ChatFileDirection type)
{
    setFixedHeight(130);
    QHBoxLayout *pMainLayout = new QHBoxLayout(this);
    pMainLayout->setMargin(0);
    pMainLayout->setSpacing(0);

    m_pItemWidget = new CShowSingleFileItemWidget(type, this);

    if (type == RIGHT_FILE_DIRECTION)
    {
        pMainLayout->addStretch(1);
    }
    pMainLayout->addWidget(m_pItemWidget);


    setLayout(pMainLayout);
}

CShowSingleFileItemWidget::CShowSingleFileItemWidget(ChatFileDirection type, QWidget *parent /*= nullptr*/)
    :QWidget(parent)
{
    createUi(type);
     //这里的子控件样式为啥不行
    //this->loadStyleSheet(QString(":/QQChatMessage/Resources/chat.css"));
    //setStyleSheet(QString("QPushButton#m_pOpenBtn{color:rgb(38 , 133 , 227);background-color:transparent;}"));
}

void CShowSingleFileItemWidget::setDataItem(const FileDataItem& data)
{
   // m_pFileTypeImg->setText(data.strfileType);
    m_pFileName->setText(data.strFileName);
    m_pFileSize->setText(data.strFileSize);
    m_pFileInfo->setText(data.strFileInfo);
    m_time = data.m_time;
}

void CShowSingleFileItemWidget::createUi(ChatFileDirection type)
{
    setFixedSize(430, 130);
    QHBoxLayout *pHMainLayout = new QHBoxLayout(this);
    pHMainLayout->setContentsMargins(15, 15, 60, 15);
    pHMainLayout->setSpacing(5);
    {
        QVBoxLayout  *pVBoxLayout = new QVBoxLayout(this);
        pVBoxLayout->setMargin(0);
        pVBoxLayout->setSpacing(0);
        {
            QHBoxLayout *pHBoxLayout = new QHBoxLayout(this);
            pHBoxLayout->setMargin(0);
            pHBoxLayout->setSpacing(0);
            {
                m_pFileTypeImg = new QLabel(this);
                m_pFileTypeImg->setFixedSize(40, 40);
                m_pFileTypeImg->setPixmap(QPixmap(":/QQChatMessage/Resources/filetype/default.png"));

                m_pFileTypeStateImg = new QPushButton(this);
                m_pFileTypeStateImg->setFixedSize(15, 15);
                m_pFileTypeStateImg->setIcon(QIcon(":/QQChatMessage/Resources/send_success.png"));
                m_pFileTypeStateImg->move(45, 60);

                pHBoxLayout->addWidget(m_pFileTypeImg);
                {
                    QVBoxLayout *pV = new QVBoxLayout(this);
                    pV->setMargin(0);
                    pV->setSpacing(5);
                    QHBoxLayout *pH = new QHBoxLayout(this);
                    pH->setMargin(0);
                    pH->setSpacing(5);
                    m_pFileName = new QLabel;
                    m_pFileSize = new QLabel;
                    pH->addWidget(m_pFileName);
                    pH->addWidget(m_pFileSize);
                    pH->addStretch(1);
                    pV->addLayout(pH);

                    m_pFileInfo = new QLabel;
                    pV->addWidget(m_pFileInfo);
                    pHBoxLayout->addSpacing(10);
                    pHBoxLayout->addLayout(pV);
                }
            }
            pVBoxLayout->addLayout(pHBoxLayout);
        }

        {
            QHBoxLayout *pHBoxLayout = new QHBoxLayout(this);
            pHBoxLayout->setMargin(0);
            pHBoxLayout->setSpacing(5);

            QFontMetrics fontM(font());

            int nAdjust = 5;
            m_pOpenBtn = new QPushButton(this);
            m_pOpenBtn->setText("打开");
            m_pOpenBtn->setFixedWidth(fontM.width(QString("打开")) + nAdjust);
            m_pOpenDirBtn = new QPushButton(this);
            m_pOpenDirBtn->setText("打开文件夹");
            m_pOpenDirBtn->setFixedWidth(fontM.width(QString("打开文件夹")) + nAdjust);
            m_pRepeatDownBtn = new QPushButton(this);
            m_pRepeatDownBtn->setText("重新下载");
            m_pRepeatDownBtn->setFixedWidth(fontM.width(QString("重新下载")) + nAdjust);
            m_pTransmitBtn = new QPushButton(this);
            m_pTransmitBtn->setText("转发");
            m_pTransmitBtn->setFixedWidth(fontM.width(QString("转发")) + nAdjust);
            m_pOtherBtn = new QPushButton(this);
            m_pOtherBtn->setFixedSize(22, m_pTransmitBtn->height());


            pHBoxLayout->addWidget(m_pOpenBtn);
            pHBoxLayout->addWidget(m_pOpenDirBtn);
            pHBoxLayout->addWidget(m_pRepeatDownBtn);
            pHBoxLayout->addWidget(m_pTransmitBtn);
            pHBoxLayout->addWidget(m_pOtherBtn);

            pVBoxLayout->addLayout(pHBoxLayout);
        }

        m_pHeaderImgBtn = new QPushButton;
        m_pHeaderImgBtn->setFixedSize(40, 40);

        if (type == RIGHT_FILE_DIRECTION)
        {
            pHMainLayout->addLayout(pVBoxLayout);
            pHMainLayout->addWidget(m_pHeaderImgBtn, 0, Qt::AlignTop);
        }
        else
        {
            pHMainLayout->addWidget(m_pHeaderImgBtn, 0, Qt::AlignTop);
            pHMainLayout->addLayout(pVBoxLayout);
        }
    }

    setLayout(pHMainLayout);
}

void CShowSingleFileItemWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QRect rect(0, 15, width() - 116, height() - 17);     //减是对齐头像

    painter.setBrush(QBrush(QColor(176, 255, 255)));
    painter.drawRect(rect);
}

void CShowSingleFileItemWidget::loadStyleSheet(const QString &sheetName)
{
    QFile file(sheetName);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}
