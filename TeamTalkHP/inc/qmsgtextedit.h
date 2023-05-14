#ifndef QMSGTEXTEDIT_H
#define QMSGTEXTEDIT_H

#include <QTextEdit>

class QMsgTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	QMsgTextEdit(QWidget *parent);
	~QMsgTextEdit();

private:
	void insertFromMimeData(const QMimeData *source) override;

private slots:
	void onEmotionImageFrameChange(int frame);

public:
	void addEmotionUrl(int emotionNum);
	void delteAllEmotionImage();

private:
	QList<QString> m_listEmotionUrl;
	QMap<QMovie*, QString> m_emotionMap;
};

#endif // QMSGTEXTEDIT_H
