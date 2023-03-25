#include "loginnetsetwindow.h"
#include <QPainter>
#include <QMovie>
#include <QMouseEvent>
#include <Env/CConfig.h>
#include <User/CFlamingoClientCenter.h>
#include <QPainterPath>

namespace PC
{

    LoginNetSetWindow::LoginNetSetWindow(QWidget *parent)
        : BaseWindow(parent)
    {
        ui.setupUi(this);
        initWindow();
        initMyTitle();
        connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SIGNAL(hideWindow()));
    }

    LoginNetSetWindow::~LoginNetSetWindow()
    {

    }

    void LoginNetSetWindow::slotOnOk()
    {
        QString chatServer = ui.chatAddr->text();
        QString imageServer = ui.imageAddr->text();
        QString fileServer = ui.fileAddr->text();

        std::map<SERVERTYPE, QString>& servers = CConfig::instance()->getServers();
        servers[CHAT_SERVER] = chatServer;
        servers[IMAGE_SERVER] = imageServer;
        servers[FILE_SERVER] = fileServer;
        CFlamingoClientCenter::instance()->resetAddress();
    }

    void LoginNetSetWindow::on_chatTestBtn_clicked()
    {

    }

    void LoginNetSetWindow::on_imageTestBtn_clicked()
    {

    }

    void LoginNetSetWindow::on_fileTestBtn_clicked()
    {

    }

    void LoginNetSetWindow::initMyTitle()
    {
        m_titleBar->move(0, 0);
        m_titleBar->raise();
        m_titleBar->setBackgroundColor(0, 0, 0, true);
        m_titleBar->setButtonType(MIN_BUTTON);
        m_titleBar->setTitleWidth(this->width());
        // 这里需要设置成false，不允许通过标题栏拖动来移动窗口位置,否则会造成窗口位置错误;
        m_titleBar->setMoveParentWindowFlag(false);
    }

    void LoginNetSetWindow::initWindow()
    {
        QLabel* pBack = new QLabel(this);
        QMovie *movie = new QMovie();
        movie->setFileName(":/Resources/NetSetWindow/headBack.gif");
        pBack->setMovie(movie);
        movie->start();
        pBack->move(0, 0);

        ui.chatAddr->setInputMask("000.000.000.000:00000");
        ui.imageAddr->setInputMask("000.000.000.000:00000");
        ui.fileAddr->setInputMask("000.000.000.000:00000");

        const auto& servers = CConfig::instance()->getServers();
        for (auto& iter : servers)
        {
            if (iter.first == CHAT_SERVER)
            {
                ui.chatAddr->setText(iter.second);
            }
            else if (iter.first == FILE_SERVER)
            {
                ui.fileAddr->setText(iter.second);
            }
            else if (iter.first == IMAGE_SERVER)
            {
                ui.imageAddr->setText(iter.second);
            }
        }

        connect(ui.pButtonOk, SIGNAL(clicked()), this, SIGNAL(rotateWindow()));
        connect(ui.pButtonOk, SIGNAL(clicked()), this, SLOT(slotOnOk()));
        connect(ui.pButtonCancel, SIGNAL(clicked()), this, SIGNAL(rotateWindow()));
    }

    void LoginNetSetWindow::paintEvent(QPaintEvent *event)
    {
        // 绘制背景图;
        QPainter painter(this);
        QPainterPath pathBack;
        pathBack.setFillRule(Qt::WindingFill);
        pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(pathBack, QBrush(QColor(235, 242, 249)));

        QPainterPath pathBottom;
        pathBottom.setFillRule(Qt::WindingFill);
        pathBottom.addRoundedRect(QRect(0, 300, this->width(), this->height() - 300), 3, 3);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(pathBottom, QBrush(QColor(205, 226, 242)));

        painter.setPen(QPen(QColor(160, 175, 189)));
        painter.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
    }

    // 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果;
    void LoginNetSetWindow::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton)
        {
            m_isPressed = true;
            m_startMovePos = event->globalPos();
        }

        return QWidget::mousePressEvent(event);
    }

    void LoginNetSetWindow::mouseMoveEvent(QMouseEvent *event)
    {
        if (m_isPressed)
        {
            QPoint movePoint = event->globalPos() - m_startMovePos;
            QPoint widgetPos = this->parentWidget()->pos() + movePoint;
            m_startMovePos = event->globalPos();
            this->parentWidget()->move(widgetPos.x(), widgetPos.y());
        }
        return QWidget::mouseMoveEvent(event);
    }

    void LoginNetSetWindow::mouseReleaseEvent(QMouseEvent *event)
    {
        m_isPressed = false;
        return QWidget::mouseReleaseEvent(event);
    }

    void LoginNetSetWindow::closeEvent(QCloseEvent *event)
    {
        emit closeWindow();
        return __super::closeEvent(event);
    }

}