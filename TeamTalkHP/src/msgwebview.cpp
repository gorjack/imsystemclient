#include "msgwebview.h"
#include "commonutils.h"

#include <QWebChannel>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>
#include <QDesktopServices>
#include <QPushButton>
#include <QJsonDocument>
#include <QEvent>
#include <QTimer>

bool MsgWebPage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType /*type*/, bool /*isMainFrame*/)
{
	// Only allow qrc:/*.html.
	if (url.scheme() == QString("qrc"))
		return true;
	QDesktopServices::openUrl(url);
	return false;
}

MsgHtmlObj::MsgHtmlObj(QObject* parent) : QObject(parent)
{
	qputenv("QTWEBENGINE_REMOTE_DEBUGGING", QString::number(6453).toUtf8());
	initHtmlTmpl();
}

void MsgHtmlObj::console(const QString& content)
{
	qDebug() << content;
}

void MsgHtmlObj::initHtmlTmpl()
{
	m_msgLHtmlTmpl = getMsgTmplHtml("msgleftTmpl");
	m_msgRHtmlTmpl = getMsgTmplHtml("msgrightTmpl");
}

QString MsgHtmlObj::getMsgTmplHtml(const QString& code)
{
	QFile file(":/TeamTalkHP/Resources/MainWindow/MsgHtml/" + code + ".html");
	file.open(QFile::ReadOnly);
	QString data;
	if (file.isOpen())
	{
		data = QLatin1String(file.readAll());
	}
	file.close();
	return data;
}

MsgWebView::MsgWebView(QWidget* parent) :QWebEngineView(parent)
	, m_skinWidget(nullptr)
	, m_bshowbox(false)
{
	MsgWebPage *page = new MsgWebPage(this);
	setPage(page);
	QWebChannel *channel = new QWebChannel(this);
	m_msgHtmlObj = new MsgHtmlObj(this);
	channel->registerObject("external", m_msgHtmlObj);
	this->page()->setWebChannel(channel);
	this->load(QUrl("qrc:/TeamTalkHP/Resources/MainWindow/MsgHtml/msgTmpl.html"));

	m_spliterBtn = new QPushButton(this);
	m_spliterBtn->setObjectName("rightSpliterBtn");
	m_spliterBtn->setVisible(false);
	m_spliterBtn->setFixedSize(13, 90);

	this->installEventFilter(this);
	m_spliterBtn->installEventFilter(this);

	connect(m_spliterBtn, &QPushButton::clicked, this, &MsgWebView::onSpliterBtnClicked);
	m_updateDownArrowtimer = new QTimer(this);
	connect(m_updateDownArrowtimer, SIGNAL(timeout()), this, SLOT(onUpdateDownArrowtimer()));
	m_updateDownArrowtimer->setInterval(500);
}

MsgWebView::~MsgWebView()
{

}

QWidget* MsgWebView::getTalkWindowSpliterButton() const
{
	return m_spliterBtn;
}

void MsgWebView::setShowSkinControl(QWidget* skinWidget)
{
	m_skinWidget = skinWidget;
}

void MsgWebView::onSpliterBtnClicked(bool)
{
	if (m_skinWidget && m_skinWidget->isVisible())
	{
		m_skinWidget->setVisible(false);
		m_spliterBtn->setStyleSheet("QPushButton#rightSpliterBtn{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_left_normal.png);"
			"	border-width:0px;}"
			"	QPushButton#rightSpliterBtn:hover{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_left_hover.png);"
			"	border-width:0px;}"
			"	QPushButton#rightSpliterBtn : pressed{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_left_down.png);"
			"	border-width:0px;}");
	}
	else if (m_skinWidget && !m_skinWidget->isVisible())
	{
		m_skinWidget->setVisible(true);
		m_spliterBtn->setStyleSheet("QPushButton#rightSpliterBtn{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_right_normal.png);"
			"	border-width:0px;}"
			"	QPushButton#rightSpliterBtn:hover{"
			"	border-image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_right_hover.png);"
			"	border - width:0px;}"
			"	QPushButton#rightSpliterBtn : pressed{"
			"	border - image: url(:/TeamTalkHP/Resources/MainWindow/aio_splitbutton_right_down.png);"
			"	border - width:0px;}");
	}
}

void MsgWebView::resizeEvent(QResizeEvent *event)
{
	m_spliterBtn->move(width() - m_spliterBtn->width(), (height() - m_spliterBtn->height()) / 2);
	__super::resizeEvent(event);
}

bool MsgWebView::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == m_spliterBtn)
	{
// 		if (event->type() == QEvent::Enter)
// 		{
// 			this->verticalScrollBar()->setVisible(false);
// 			return true;
// 		}
// 		else if (event->type() == QEvent::Leave)
// 		{
// 			this->verticalScrollBar()->setVisible(true);
// 			return true;
// 		}
	}
	return __super::eventFilter(watched, event);
}

void MsgWebView::runJavaScriptFinished(const QVariant& result)
{
	if (result.type() == QVariant::String) {
		QString output = result.toString();
		qDebug() << output;
	}
}

void MsgWebView::appendMsg(QString userName, const QString& html)
{
	m_updateDownArrowtimer->start();

	QJsonObject msgObj;
	QString qsMsg;
	const QList<QStringList> msgLst = parseHtml(html);
	for (int index = 0; index < msgLst.size(); index++)
	{
		if (msgLst.at(index).at(0) == "img")
		{
			QString imagePath = msgLst.at(index).at(1);
			QPixmap pixmap;
			if (imagePath.left(3) == "qrc")
			{
				pixmap.load(imagePath.mid(3));
			}
			else
			{
				pixmap.load(imagePath);
			}
			int width = this->width() * 0.65;
			if (pixmap.width() > width)
			{
				pixmap =pixmap.scaled(QSize(width, pixmap.height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
			}
			QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>").arg(imagePath).arg(pixmap.width()).arg(pixmap.height());
			qsMsg += imgPath;
		}
		else if (msgLst.at(index).at(0) == "text")
		{
			qsMsg += msgLst.at(index).at(1);
		}
	}

	QString userNamePath = CommonUtils::getUserNamePicPath();
	userNamePath = userNamePath.replace("@@@@@", userName);

	msgObj.insert("HEADIMAGE", userNamePath);
	msgObj.insert("MSG", qsMsg);
	const QString&& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);
	this->page()->runJavaScript(QString("recvHtml(%1)").arg(Msg), 
		[this](const QVariant& result) { runJavaScriptFinished(result); });
}

QList<QStringList> MsgWebView::parseHtml(const QString& html)
{
	QDomDocument doc;
	doc.setContent(html);
	const QDomElement&& root = doc.documentElement();
	const QDomNode&& node = root.firstChildElement("body");
	return parseDocNode(node);
}

QList<QStringList> MsgWebView::parseDocNode(const QDomNode& node)
{
	QList<QStringList> attribute;
	const QDomNodeList&& list = node.childNodes();
	for (int i = 0; i < list.count(); i++)
	{
		const QDomNode&& node = list.at(i);
		if (node.isElement())
		{
			//×ª»»ÎªÔªËØ
			const QDomElement&& element = node.toElement();
			if (element.tagName() == "img")
			{
				QStringList attributeLst;
				attributeLst << "img" << element.attribute("src");
				attribute << attributeLst;
			}
			if (element.tagName() == "span")
			{
				QStringList attributeLst;
				attributeLst << "text" << element.text();
				attribute << attributeLst;
			}
			if (node.hasChildNodes())
			{
				attribute << parseDocNode(node);
			}
		}
	}
	return attribute;
}

void MsgWebView::paintEvent(QPaintEvent *event)
{
	__super::paintEvent(event);
	QPainter painer(this);
	painer.setRenderHint(QPainter::SmoothPixmapTransform, this);
	painer.setPen(Qt::NoPen);

	painer.drawPixmap(width() - 13, height() + 2, QPixmap(":/TeamTalkHP/Resources/MainWindow/scrollbar_top_normal.gft.png"));
	painer.drawPixmap(width() - 13, height() - 14, QPixmap(":/TeamTalkHP/Resources/MainWindow/scrollbar_down_normal.gft.png"));
	if (m_updateDownArrowtimer->isActive())
	{
		if (m_bshowbox)
		{
			painer.setPen(QColor(174, 193, 191));
			painer.drawRect(width() - 13, height() - 14, 11, 11);
		}
	}
}

void MsgWebView::onUpdateDownArrowtimer()
{
	m_bshowbox = !m_bshowbox;
	update();
}