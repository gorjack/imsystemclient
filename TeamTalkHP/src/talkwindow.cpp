#include "talkwindow.h"
#include "capture/widget/capturewidget.h"
#include "windowmanager.h"

#include <QTextCursor>
#include <QMovie>
#include <QImage>
#include <QScrollBar>
#include <QMenu>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QFontDatabase>
#include <QColorDialog> 
#include <QUuid>
#include <QKeyEvent>
#include <QToolTip>

TalkWindow::TalkWindow(QWidget *parent, const QString& uid)
	: QWidget(parent)
{
	m_talkId = uid;
	WindowManager::getInstance()->addWindowName(m_talkId, this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	initControl();
	initFontWidget();
}

TalkWindow::~TalkWindow()
{
	WindowManager::getInstance()->deleteWindowName(m_talkId);
}

void TalkWindow::initControl()
{
	setSendBtnMenu();
	QList<int> rightWidgetSize;
	rightWidgetSize << 600 << 138;
	ui.bodySpliter->setSizes(rightWidgetSize);

	connect(ui.sysmin, SIGNAL(clicked(bool)), parent(), SLOT(onShowMin(bool)));
	connect(ui.sysclose, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));
	connect(ui.closeBtn, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));

	connect(ui.fontBtn, SIGNAL(clicked(bool)), this, SLOT(onFontBtnClicked(bool)));
	connect(ui.faceBtn, SIGNAL(clicked(bool)), parent(), SLOT(onEmotionBtnClicked(bool)));
	connect(ui.sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendBtnClicked(bool)));

	ui.fontWidget->setVisible(false);
	ui.msgWidget->setShowSkinControl(ui.skinLabel);
	ui.skinLabel->setSpliterButton(ui.msgWidget->getTalkWindowSpliterButton());
}

void TalkWindow::initFontWidget()
{
	QFontDatabase database;
	foreach(const QString &family, database.families())
	{
		ui.fontfamilyCombox->addItem(family);
	}

	for (int fontsize = 9; fontsize < 22; fontsize++)
	{
		ui.fontsizeCombox->addItem(QString::number(fontsize));
	}
	
	onFontSizecurrentIndexChanged("10");

	connect(ui.fontfamilyCombox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onFontFamilycurrentIndexChanged(const QString &)));
	connect(ui.fontsizeCombox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onFontSizecurrentIndexChanged(const QString &)));
	connect(ui.boldBtn, SIGNAL(clicked(bool)), this, SLOT(onBoldBtnCLicked(bool)));
	connect(ui.italBtn, SIGNAL(clicked(bool)), this, SLOT(onItalBtnCLicked(bool)));
	connect(ui.underBtn, SIGNAL(clicked(bool)), this, SLOT(onUnderBtnCLicked(bool)));
	connect(ui.colorBtn, SIGNAL(clicked(bool)), this, SLOT(onColorBtnCLicked(bool)));
	connect(ui.cutBtn, SIGNAL(clicked(bool)), this, SLOT(onCutBtnCLicked(bool)));
	connect(ui.textEdit, &QTextEdit::currentCharFormatChanged, this, &TalkWindow::currentCharFormatChanged);
}

void TalkWindow::onFontFamilycurrentIndexChanged(const QString &family)
{
	m_font.family = family;
	QTextCharFormat fmt;
	fmt.setFontFamily(family);
	mergeFormatOnWordOrSelection(fmt);
	ui.textEdit->setFontFamily(family);
	ui.textEdit->setFocus();
}

void TalkWindow::onFontSizecurrentIndexChanged(const QString &size)
{
	m_font.fontsize = size.toInt();
	QTextCharFormat fmt;
	fmt.setFontPointSize(size.toInt());
	mergeFormatOnWordOrSelection(fmt);
	ui.textEdit->setFontPointSize(size.toInt());
	ui.textEdit->setFocus();
}

void TalkWindow::onBoldBtnCLicked(bool)
{
	QTextCharFormat fmt;
	if (ui.textEdit->fontWeight() == QFont::Bold)
	{
		m_font.bold = QFont::Normal;
		fmt.setFontWeight(QFont::Normal);
		ui.textEdit->setFontWeight(QFont::Normal);
	}
	else
	{
		m_font.bold = QFont::Bold;
		fmt.setFontWeight(QFont::Bold);
		ui.textEdit->setFontWeight(QFont::Bold);
	}
	mergeFormatOnWordOrSelection(fmt);
	ui.textEdit->setFocus();
}

void TalkWindow::onItalBtnCLicked(bool)
{
	bool ital = ui.textEdit->fontItalic();
	m_font.ital = !ital;
	QTextCharFormat fmt;
	fmt.setFontItalic(!ital);
	mergeFormatOnWordOrSelection(fmt);
	ui.textEdit->setFontItalic(!ital);
	ui.textEdit->setFocus();
}

void TalkWindow::onUnderBtnCLicked(bool)
{
	bool underline = ui.textEdit->fontUnderline();
	m_font.underline = !underline;
	QTextCharFormat fmt;
	fmt.setFontUnderline(!underline);
	mergeFormatOnWordOrSelection(fmt);
	ui.textEdit->setFontUnderline(!underline);
	ui.textEdit->setFocus();
}

void TalkWindow::onColorBtnCLicked(bool)
{
	QColorDialog colorDialog;
	QColor color = colorDialog.getColor(ui.textEdit->textColor(), this, QStringLiteral("选择字体颜色"));
	m_font.color = color;
	QTextCharFormat fmt;
	fmt.setForeground(color);
	mergeFormatOnWordOrSelection(fmt);
	ui.textEdit->setTextColor(color);
	ui.textEdit->setFocus();
}

void TalkWindow::onCutBtnCLicked(bool)
{
	CaptureWidget* captureWidget = new CaptureWidget(this);
	connect(captureWidget, SIGNAL(capturePixmap(const QPixmap&)), this, SLOT(onCapturePixmap(const QPixmap&)));
	captureWidget->show();
}

void TalkWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = ui.textEdit->textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::Document);
	cursor.mergeCharFormat(format);
	ui.textEdit->mergeCurrentCharFormat(format);
}

void TalkWindow::onCapturePixmap(const QPixmap& pixmap)
{
	QTextImageFormat imageFormat;
	QString path = qApp->applicationDirPath() + "/" + QUuid::createUuid().toString() + ".png";
	pixmap.save(path);
	imageFormat.setName(path);
	ui.textEdit->textCursor().insertImage(imageFormat);
}

void TalkWindow::currentCharFormatChanged(const QTextCharFormat &format)
{
	ui.textEdit->setFontFamily(m_font.family);
	ui.textEdit->setFontPointSize(m_font.fontsize);
	ui.textEdit->setFontWeight(m_font.bold);
	ui.textEdit->setFontItalic(m_font.ital);
	ui.textEdit->setFontUnderline(m_font.underline);
	ui.textEdit->setTextColor(m_font.color);
	QTextCharFormat fmt;
	fmt.setBackground(Qt::transparent);
	mergeFormatOnWordOrSelection(fmt);
}

void TalkWindow::onFontBtnClicked(bool)
{
	if (ui.fontWidget->isVisible())
	{
		ui.fontWidget->setVisible(false);
		ui.fontBtn->setChecked(false);
	}
	else
	{
		ui.fontWidget->setVisible(true);
		ui.fontBtn->setChecked(true);
	}
	update();
}

void TalkWindow::onSetEmotionBtnStatus()
{
	ui.faceBtn->setChecked(false);
}

void TalkWindow::setWindowName(const QString& name)
{
	ui.nameLabel->setText(name);
}

void TalkWindow::setWindowSignName(const QString& name)
{
	ui.signLabel->setText(name);
}

void TalkWindow::onSignalWindowclosed()
{
	close();
}

void TalkWindow::onSendBtnClicked(bool)
{
	if (ui.textEdit->toPlainText().isEmpty())
	{
		QToolTip::showText(this->mapToGlobal(QPoint(630, 660)), QStringLiteral("发送消息不能为空"), this, QRect(0, 0, 120, 100), 2000);
		return;
	}

	const QString&& html = ui.textEdit->document()->toHtml();
	ui.textEdit->clear();
	ui.textEdit->delteAllEmotionImage();

	ui.msgWidget->appendMsg(html);
}

void TalkWindow::addEmotionImage(int emotionNum)
{
	ui.textEdit->setFocus();
	ui.textEdit->addEmotionUrl(emotionNum);
}

void TalkWindow::setSendBtnMenu()
{
	QMenu* menu = new QMenu(this);
	menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint);
	menu->setAttribute(Qt::WA_TranslucentBackground);
	menu->setObjectName("senMenu");
	m_sendAction = menu->addAction(QStringLiteral("按Enter键，发送消息"), this, SLOT(onEnterAction()));
	m_ctrlSendAction = menu->addAction(QStringLiteral("按Enter+Ctrl键，发送消息"), this, SLOT(onEnterCtrlAction()));
	
	QActionGroup* actiongroup = new QActionGroup(this);
	m_sendAction->setCheckable(true);
	m_ctrlSendAction->setCheckable(true);
	m_sendAction->setChecked(true);
	actiongroup->addAction(m_sendAction);
	actiongroup->addAction(m_ctrlSendAction);
	ui.sendBtn->setMenu(menu);
}

void TalkWindow::onEnterAction()
{
	m_sendAction->setChecked(true);
}

void TalkWindow::onEnterCtrlAction()
{
	m_ctrlSendAction->setChecked(true);
}

void TalkWindow::keyPressEvent(QKeyEvent *event)
{
	__super::keyPressEvent(event);
}