#include "emotiontable.h"

#include <QPainter>

EmotionTable::EmotionTable(QWidget *parent)
	: QWidget(parent)
	, m_rowHeight(32)
	, m_columnWidth(32)
{

}

EmotionTable::~EmotionTable()
{

}

void EmotionTable::setTableCount(int row, int column)
{
	m_row = row;
	m_column = column;
	update();
}

void EmotionTable::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(palette().brush(QPalette::Base));
	QPen pen = painter.pen();
	pen.setWidthF(1);
	pen.setColor(Qt::red);
	painter.setPen(pen);

	if (m_row > 0)
	{
		for (int i = 0; i <= m_row; ++i) {
			double verticalPos = i * 32;
			painter.drawLine(QPointF(0.0, verticalPos), QPointF(width(), verticalPos));
		}
	}

	if (m_column > 0)
	{
		for (int i = 0; i <= m_column; ++i) {
			double horizontalPos = i * 32;
			painter.drawLine(QPointF(horizontalPos, 0.0), QPointF(horizontalPos, height()));
		}
	}
}
