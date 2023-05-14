#ifndef EMOTIONTABLE_H
#define EMOTIONTABLE_H

#include <QWidget>

class EmotionTable : public QWidget
{
	Q_OBJECT

public:
	EmotionTable(){};
	EmotionTable(QWidget *parent);
	~EmotionTable();

public:
	void setTableCount(int row, int column);

private:
	void paintEvent(QPaintEvent *event);

private:
	int m_rowHeight;
	int m_columnWidth;

	int m_row;
	int m_column;
};

#endif // EMOTIONTABLE_H
