#ifndef QCOLORPICKER_H
#define QCOLORPICKER_H

#include <QWidget>
#include "ui_qcolorpicker.h"

class QColorPicker : public QWidget
{
	Q_OBJECT

public:
	QColorPicker(QWidget *parent = 0);
	~QColorPicker();

public:
	QColor drawColor();
	int thickNess();

private:
	void initControl();
	void paintEvent(QPaintEvent *event);

private slots:
	void onColorClicked();
	void onThicknessClicked();

private:
	Ui::QColorPicker ui;
	QString m_curColor;
	int m_thickness = 0;
};

#endif // QCOLORPICKER_H
