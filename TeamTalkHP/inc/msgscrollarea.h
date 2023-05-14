#ifndef MSGSCROLLAREA_H
#define MSGSCROLLAREA_H

#include <QScrollArea>

class QPushButton;
class MsgScrollArea : public QScrollArea
{
	Q_OBJECT

public:
	MsgScrollArea(QWidget *parent);
	~MsgScrollArea();

private slots:
	void onSpliterBtnClicked(bool);

public:
	void setShowSkinControl(QWidget* skinWidget);
	QWidget* getTalkWindowSpliterButton() const;
	void scrollToBottom(QWidget* widget);

private:
	void resizeEvent(QResizeEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);

private:
	QPushButton* m_spliterBtn;
	QWidget* m_skinWidget;
	
};

#endif // MSGSCROLLAREA_H
