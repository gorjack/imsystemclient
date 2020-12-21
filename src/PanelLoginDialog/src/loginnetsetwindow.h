#ifndef LOGINNETSETWINDOW_H
#define LOGINNETSETWINDOW_H

#include <QWidget>
#include "ui_loginnetsetwindow.h"
#include "basewindow.h"

class LoginNetSetWindow : public BaseWindow
{
	Q_OBJECT

public:
	LoginNetSetWindow(QWidget *parent = 0);
	~LoginNetSetWindow();

signals:
	void rotateWindow();
	void closeWindow();
	void hideWindow();

protected Q_SLOTS:
    void slotOnOk();
    void on_chatTestBtn_clicked();
    void on_imageTestBtn_clicked();
    void on_fileTestBtn_clicked();
private:
	void initMyTitle();
	void initWindow();
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	

private:
	Ui::LoginNetSetWindow ui;
	bool m_isPressed;
	QPoint m_startMovePos;
};

#endif // LOGINNETSETWINDOW_H
