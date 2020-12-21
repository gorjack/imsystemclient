#include "CSendMsgTextEdit.h"
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <Env/directory.h>
#include <QPainter>
#include <QtWidgets/QFileDialog>
#include <ProtocolData/rpc_proEnum.h>
#include <winlog/IULog.h>
#include <utils/commonFunc.h>
#include <Env/CConfig.h>
#include <User/CFlamingoClientCenter.h>
#include <QtWidgets/QMessageBox>

CSendMsgTextEdit::CSendMsgTextEdit(QWidget *parent /*= nullptr*/)
    :QWidget(parent)
{
    createUi();
    setStyleSheet(":/QQChatMessage/Resources/sendedit.css");
    //setStyleSheet("background-color: rgb(255, 255, 255)");
    //setStyleSheet("background-color: rgba(255, 255, 255, 30%); border-top-width:1px;border-top-color:rgb(128,128,128);border-style:outset");
    //setStyleSheet("border-top-width:1px;border-top-color:rgb(128,128,128);border-style:outset");

    connect(m_pSendMsgBtn, SIGNAL(clicked()), this, SLOT(slotSendMessage()));
    connect(CFlamingoClientCenter::instance(), SIGNAL(sigLogindStatus(UserLoginStatus, QString)),
        this, SLOT(onHandleErrorStatus(UserLoginStatus, QString)));
}

void CSendMsgTextEdit::setText(const QString& msg)
{
    m_pMainMsgEdit->setText(msg);
}

void CSendMsgTextEdit::slotSendMessage()
{
    emit sigSendMsg(m_pMainMsgEdit->toPlainText());
}

void CSendMsgTextEdit::slotOnHandleSendFile()
{
    CFlamingoClientCenter::instance()->connect_async(FILE_SERVER);

    using namespace protocol;
    QString fileName = QFileDialog::getOpenFileName(this, "file", ".", "files (*.*)");
    if (fileName.isEmpty())
    {
        return;
    }

    upLoadFile(fileName);
}

void CSendMsgTextEdit::onHandleErrorStatus(UserLoginStatus status, QString msg)
{
    switch (status)
    {
    case FILE_STATUS_CONNECTING:
        break;
    case FILE_STATUS_CONNECTED:
        break;
    case FILE_STATUS_ERROR:
        QMessageBox::information(this, "info", msg);
        break;
    case FILE_STATUS_SUCCESS:
        QMessageBox::information(this, "info", "上传文件成功");
        break;
    default:
        break;
    }
}

void CSendMsgTextEdit::resizeEvent(QResizeEvent *event)
{
    m_pSendMsgBtn->setGeometry(width() - 100, height() - 50, 85, 35);

    m_pShowToolBtns->setGeometry(5, 0, 300, 30);
    m_pShowTool2Btns->setGeometry(width() - 37, 0, 30, 30);

    m_pMainMsgEdit->setGeometry(0, 35, width(), height());

}

void CSendMsgTextEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    QWidget::paintEvent(event);
}

void CSendMsgTextEdit::upLoadFile(const QString& fileName)
{
    const QString error = CFlamingoClientCenter::instance()->sendFileToServer(fileName);
    if (!error.isEmpty())
    {
        QMessageBox::information(this, "info", error);
    }
}

void CSendMsgTextEdit::createUi()
{
    m_pMainMsgEdit = new QTextEdit(this);
    m_pMainMsgEdit->setFrameShape(QFrame::NoFrame);
    //QTextCursor tmpCursor = m_pMainMsgEdit->textCursor();
    //tmpCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 4);
    //m_pMainMsgEdit->setTextCursor(tmpCursor);

    m_pSendMsgBtn = new QPushButton(this);
    m_pSendMsgBtn->setFixedSize(85, 35);
    m_pSendMsgBtn->setText("Send");

    m_pShowToolBtns = new QToolBar(this);
    m_pShowToolBtns->setMovable(false);
    QToolButton* pFaceBtn = new QToolButton(this);
    QToolButton* pGifBtn = new QToolButton(this);
    QToolButton* pCaptureBtn = new QToolButton(this);
    QToolButton* pSendfilebtn = new QToolButton(this);
    QToolButton* pSendimagebtn = new QToolButton(this);
    QToolButton* pPermissionBtn = new QToolButton(this);
    QToolButton* pFontBtn = new QToolButton(this);
    QToolButton* pMobileBtn = new QToolButton(this);
    QToolButton* pOtherBtn = new QToolButton(this);
    {
        connect(pSendfilebtn, SIGNAL(clicked()), this, SLOT(slotOnHandleSendFile()));
    }

    m_pShowTool2Btns = new QToolBar(this);
    m_pShowTool2Btns->setMovable(false);
    QToolButton* pMessagesBtn = new QToolButton(this);
    pMessagesBtn->setIcon(QIcon(QString("%1/messages_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pMessagesBtn->setFixedSize(30, 30);
    m_pShowTool2Btns->addWidget(pMessagesBtn);

    m_pShowToolBtns->addWidget(pFaceBtn);
    m_pShowToolBtns->addWidget(pGifBtn);
    m_pShowToolBtns->addWidget(pCaptureBtn);
    m_pShowToolBtns->addWidget(pSendfilebtn);
    m_pShowToolBtns->addWidget(pSendimagebtn);
    m_pShowToolBtns->addWidget(pPermissionBtn);
    m_pShowToolBtns->addWidget(pFontBtn);
    m_pShowToolBtns->addWidget(pMobileBtn);
    m_pShowToolBtns->addWidget(pOtherBtn);


    pFaceBtn->setIcon(QIcon(QString("%1/face_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pFaceBtn->setFixedSize(30, 30);
    pGifBtn->setIcon(QIcon(QString("%1/gif_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pGifBtn->setFixedSize(30, 30);
    pCaptureBtn->setIcon(QIcon(QString("%1/capture_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pCaptureBtn->setFixedSize(30, 30);
    pSendfilebtn->setIcon(QIcon(QString("%1/file_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pSendfilebtn->setFixedSize(30, 30);
    pSendimagebtn->setIcon(QIcon(QString("%1/picture_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pSendimagebtn->setFixedSize(30, 30);
    pPermissionBtn->setIcon(QIcon(QString("%1/info.png").arg(QF::getCurrentResourceDir())));
    pPermissionBtn->setFixedSize(30, 30);
    pFontBtn->setIcon(QIcon(QString("%1/font_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pFontBtn->setFixedSize(30, 30);
    pMobileBtn->setIcon(QIcon(QString("%1/mobile_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pMobileBtn->setFixedSize(30, 30);
    pOtherBtn->setIcon(QIcon(QString("%1/other_toolbtn.png").arg(QF::getCurrentResourceDir())));
    pOtherBtn->setFixedSize(30, 30);
}