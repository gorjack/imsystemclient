#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QSize>
#include <QPixmap>
#include <QProxyStyle>

class CustomProxyStyle : public QProxyStyle
{
public:
	CustomProxyStyle(QObject* parent)
	{
		setParent(parent);
	};

	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption * option,
		QPainter * painter, const QWidget * widget = 0) const
	{
		if (PE_FrameFocusRect == element)
		{
			return;
		}
		else
		{
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};

class CommonUtils
{
public:
	CommonUtils();

public:
	static QPixmap getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize = QSize(0, 0));
	static void loadStyleSheet(QWidget* widget, const QString &sheetName);
	static QString CharacterEscaping(QString content);
	static void setDefaultSkinColor(const QColor& color);
	static QColor getDefaultSkinColor();
};

#endif // COMMONUTILS_H
