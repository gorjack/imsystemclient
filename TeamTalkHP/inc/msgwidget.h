#ifndef MSGWIDGET_H
#define MSGWIDGET_H

#include <QtWebEngineWidgets/qwebengineview.h>

class MsgWidget : public QWebEngineView
{
	Q_OBJECT

public:
	MsgWidget();
	MsgWidget(QWidget *parent);
	~MsgWidget();

private:
	
};

#endif // MSGWIDGET_H
