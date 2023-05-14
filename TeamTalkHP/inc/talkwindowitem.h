#ifndef TALKWINDOWITEM_H
#define TALKWINDOWITEM_H

#include <QWidget>
#include "ui_talkwindowitem.h"

class TalkWindowItem : public QWidget
{
	Q_OBJECT

public:
	TalkWindowItem(QWidget *parent = 0);
	~TalkWindowItem();

signals:
	void signalCloseClicked();

public:
	void setHeadPixmap(const QString& headpath);
	void setMsgLabelContent(const QString& msg);

private:
	void initControl();

private:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
	Ui::TalkWindowItem ui;
};

#endif // TALKWINDOWITEM_H
