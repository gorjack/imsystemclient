#ifndef CSENDMSGTEXTEDIT_H
#define CSENDMSGTEXTEDIT_H

#include <QtWidgets/QWidget>
#include <User/userdatas.h>

class QTextEdit;
class QPushButton;
class QToolBar;
class QHBoxLayout;
class CSendMsgTextEdit : public QWidget
{
    Q_OBJECT
public:
    explicit CSendMsgTextEdit(QWidget *parent = nullptr);

    void setText(const QString& msg);
Q_SIGNALS:
    void sigSendMsg(QString);
    void sigShowRightWidget();
    void sigSendFile(const FileTransferStatus&, const QString&);

protected Q_SLOTS:
    void slotSendMessage();
    void slotOnHandleSendFile();
    void onHandleErrorStatus(int, QString);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

    void onHandleSendFile(const FileTransferStatus& status,  const QString& msgInfo);

private:
    void createUi();

    QTextEdit           *m_pMainMsgEdit = NULL;
    QPushButton         *m_pSendMsgBtn = NULL;
    QToolBar            *m_pShowToolBtns = NULL;
    QToolBar            *m_pShowTool2Btns = NULL;
    QHBoxLayout         *m_pHLayout = NULL;
};

#endif 