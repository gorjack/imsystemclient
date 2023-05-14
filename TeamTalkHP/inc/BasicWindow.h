#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QDialog>
#include <QIcon>
#include "titlebar.h"
#define BACK_SHADOW_WIDTH 8

class BasicWindow : public QDialog
{
	Q_OBJECT

public:
    BasicWindow(QWidget *parent = nullptr);
	virtual ~BasicWindow();

public:
	// 加载qss
	void loadStyleSheet(const QString &sheetName);
	QPixmap getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize = QSize(0, 0));

private:
	void initBackGroundColor();//初始化背景
	void moveDirection();
	void sizeDirection();

protected:
	void paintEvent(QPaintEvent*);// 绘制事件
	void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

protected:
	void initTitleBar(ButtonType buttontype = MIN_BUTTON);
	void setTitleBarTitle(const QString& title, const QString& icon = "");

public slots:
	void onShowClose(bool);
	void onShowMin(bool);
	void onShowHide(bool);
	void onShowNormal(bool);
	void onShowQuit(bool);
	void onSignalSkinChanged(const QColor& color);

    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

protected:
    QPoint mousePoint;
    bool m_mousePressed;
	QColor m_colorBackGround;
	QString m_styleName;
    TitleBar* _titleBar;
};

#endif // TMQWIDGET_H
