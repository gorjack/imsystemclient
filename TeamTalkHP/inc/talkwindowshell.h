#ifndef QQTALKWINDOW_H
#define QQTALKWINDOW_H

#include "BasicWindow.h"
#include "ui_talkwindowshell.h"

class TalkWindow;
class TalkWindowItem;
class EmotionWindow;
class TalkWindowShell : public BasicWindow
{
	Q_OBJECT

public:
	TalkWindowShell(QWidget *parent = 0);
	~TalkWindowShell();

public:
	void addTalkWindow(TalkWindow* talkwindow, TalkWindowItem* talkwindowItem);
	void setCurrentWidget(QWidget* widget);

public slots:
	void onEmotionBtnClicked(bool);

private slots:
	void onTalkWindowItemClicked(QListWidgetItem *item);
	void onEmotionItemClicked(int emotionNum);

private:
	void initControl();

private:

private:
	Ui::TalkWindowClass ui;
	QMap<QListWidgetItem*, QWidget*> m_talkwindowItemMap;
	EmotionWindow* m_emotionWindow;
};

#endif // QQTALKWINDOW_H
