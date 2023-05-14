#ifndef QSKINLABEL_H
#define QSKINLABEL_H

#include <QLabel>

class QSkinLabel : public QLabel
{
	Q_OBJECT

public:
	QSkinLabel(QWidget *parent);
	~QSkinLabel();

public:
	void setSpliterButton(QWidget* spliterBtn){ m_spliterBtn = spliterBtn; };

private:
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;

private:
	QWidget* m_spliterBtn;
};

#endif // QSKINLABEL_H
