#ifndef EMOTIONWINDOW_H
#define EMOTIONWINDOW_H

#include <QDialog>
#include "ui_emotionwindow.h"

class EmotionWindow : public QWidget
{
	Q_OBJECT

public:
	EmotionWindow(QWidget *parent = 0);
	~EmotionWindow();

private:
	void initControl();

private slots:
void addEmotion(int emotionNum);

signals:
	void signalEmotionWindowHide();
	void signalEmotionItemClicked(int emotionNum);

private:
	void paintEvent(QPaintEvent *event) override;
	void focusOutEvent(QFocusEvent *event) override;
	void showEvent(QShowEvent *event) override;

private:
	Ui::EmotionWindow ui;
};

#endif // EMOTIONWINDOW_H
