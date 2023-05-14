#ifndef MSGWEBVIEW_H
#define MSGWEBVIEW_H

#include <QtWebEngineWidgets/QWebEngineView>
#include <QDomNode>

class MsgHtmlObj : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString msgLHtmlTmpl MEMBER m_msgLHtmlTmpl NOTIFY signalMsgHtml)
	Q_PROPERTY(QString msgRHtmlTmpl MEMBER m_msgRHtmlTmpl NOTIFY signalMsgHtml)

public:
	MsgHtmlObj(QObject* parent);

signals:
	void signalMsgHtml(const QString &html);

public slots:
	void console(const QString& content);

private:
	void initHtmlTmpl();
	QString getMsgTmplHtml(const QString& code);

private:
	QString m_msgLHtmlTmpl;
	QString m_msgRHtmlTmpl;
};


class QTimer;
class MsgWebPage : public QWebEnginePage
{
	Q_OBJECT
public:
	explicit MsgWebPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
	bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
};

class QPushButton;
class MsgWebView : public QWebEngineView
{
	Q_OBJECT

public:
	MsgWebView(QWidget* parent);
	~MsgWebView();

public:
	void appendMsg(const QString& html);
	void setShowSkinControl(QWidget* skinWidget);
	QWidget* getTalkWindowSpliterButton() const;

private slots:
	void onUpdateDownArrowtimer();

private:
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);

	QList<QStringList> parseHtml(const QString& html);
	QList<QStringList> parseDocNode(const QDomNode& node);

private slots:
	void onSpliterBtnClicked(bool);

private:
	MsgHtmlObj* m_msgHtmlObj;
	QPushButton* m_spliterBtn;
	QWidget* m_skinWidget;
	QTimer* m_updateDownArrowtimer;
	bool m_bshowbox;
};

#endif // MSGWEBVIEW_H
