#ifndef TALKWINDOW_H
#define TALKWINDOW_H

#include <QWidget>
#include "ui_talkwindow.h"

class QTimer;
class TalkWindow : public QWidget
{
	Q_OBJECT

	struct TexteditFont_t{
		QString family;
		int fontsize;
		int bold;
		bool ital;
		bool underline;
		QColor color;

		TexteditFont_t()
		{
			family = QStringLiteral("微软雅黑");
			fontsize = 9;
			bold = QFont::Normal;
			ital = false;
			underline = false;
			color = Qt::black;
		}
	};

public:
	TalkWindow(QWidget *parent, const QString& uid);
	~TalkWindow();

public:
	void addEmotionImage(int emotionNum);
	void setTalkId(const QString& id){ m_talkId = id; };
	QString getTalkId(){ return m_talkId; };

private slots:
	void currentCharFormatChanged(const QTextCharFormat &format);

public slots:
	void onSignalWindowclosed();
	void onSetEmotionBtnStatus();
	void onSendBtnClicked(bool);

private slots:
	void onEnterAction();
	void onEnterCtrlAction();
	void onFontBtnClicked(bool);
	void onBoldBtnCLicked(bool);
	void onItalBtnCLicked(bool);
	void onUnderBtnCLicked(bool);
	void onColorBtnCLicked(bool);
	void onCutBtnCLicked(bool);
	void onFontFamilycurrentIndexChanged(const QString &family);
	void onFontSizecurrentIndexChanged(const QString &size);
	void onCapturePixmap(const QPixmap&);

private:
	Ui::TalkWindow ui;
	QAction* m_sendAction;
	QAction* m_ctrlSendAction;
	TexteditFont_t m_font;
	QString m_talkId;

public:
	void setWindowName(const QString& name);
	void setWindowSignName(const QString& name);
	void handleChatMsg(const std::string& strMsg);

private:
	void initControl();
	void initFontWidget();
	void setSendBtnMenu();
	void keyPressEvent(QKeyEvent *event);
	void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif // TALKWINDOW_H
