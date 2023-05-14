#ifndef EMOTIONLABELITEM_H
#define EMOTIONLABELITEM_H

#include "qclicklabel.h"

class QMovie;
class EmotionLabelItem : public QClickLabel
{
	Q_OBJECT

public:
	EmotionLabelItem(QWidget *parent);
	~EmotionLabelItem();

signals:
	void emotionClicked(int emotionNum);

private:
	void initControl();

private:
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;

public:
	void setEmotionName(int emotionName);

private:
	int m_emotionName;
	QMovie* m_apngMovie;
};

#endif // EMOTIONLABELITEM_H
