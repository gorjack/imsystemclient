#include "buttonhandler.h"
#include "src/capture/widget/qcolorpicker.h"

#include <QPoint>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

// ButtonHandler is a habdler for every active button. It makes easier to
// manipulate the buttons as a unit.

namespace {
    const int SEPARATION = 6;
}

ButtonHandler::ButtonHandler(const QRect &limits, QObject *parent) :
    QObject(parent), m_limits(limits)
{
	
}

void ButtonHandler::hide() {
	m_btnWidget->hide();
	m_colorPicker->hide();
}

void ButtonHandler::show() {
	m_btnWidget->show();
}

bool ButtonHandler::isVisible() const {
	return m_btnWidget->isVisible();
}

size_t ButtonHandler::size() const {
    return m_vectorButtons.size();
}

// UpdatePosition updates the position of the buttons around the
// selection area. Ignores the sides blocked by the end of the screen.
// When the selection is too small it works on a virtual selection with
// the original in the center.
void ButtonHandler::updatePosition(const QRect &selection) {
    const int vecLength = m_vectorButtons.size();
    if (vecLength == 0) {
        return;
    }
    // Copy of the selection area for internal modifications
    m_selection = selection;
	
	QPoint btnWidgetPoint;
	QPoint colorWidgetPoint;
	QRect deskrect = qApp->desktop()->screenGeometry(0);
	if (selection.bottom() + getToolSpacePosition() >= deskrect.bottom() && selection.top() < getToolSpacePosition())
	{
		int btnWidgetPointX = selection.topRight().x() - m_btnWidget->width();
		btnWidgetPointX = btnWidgetPointX < 0 ? 0 : btnWidgetPointX;
		btnWidgetPoint.setX(btnWidgetPointX);
		btnWidgetPoint.setY(0);

		colorWidgetPoint.setX(btnWidgetPointX);
		colorWidgetPoint.setY(btnWidgetPoint.y() + 38);
	}
	else if (selection.bottom() + getToolSpacePosition() >= deskrect.bottom())
	{
		int btnWidgetPointX = selection.topRight().x() - m_btnWidget->width();
		btnWidgetPointX = btnWidgetPointX < 0 ? 0 : btnWidgetPointX;
		btnWidgetPoint.setX(btnWidgetPointX);
		btnWidgetPoint.setY(selection.top() - getToolSpacePosition());

		colorWidgetPoint.setX(btnWidgetPointX);
		colorWidgetPoint.setY(btnWidgetPoint.y() + 38);
	}
	else
	{
		int btnWidgetPointX = selection.bottomRight().x() - m_btnWidget->width();
		btnWidgetPointX = btnWidgetPointX < 0 ? 0 : btnWidgetPointX;
		btnWidgetPoint.setX(btnWidgetPointX);
		btnWidgetPoint.setY(selection.bottom() + 12);

		colorWidgetPoint.setX(btnWidgetPointX);
		colorWidgetPoint.setY(btnWidgetPoint.y() + 38);
	}
	m_btnWidget->move(btnWidgetPoint);
	m_colorPicker->move(colorWidgetPoint);
}

// setButtons redefines the buttons of the button handler
void ButtonHandler::setButtons(QWidget* parent, const QVector<CaptureButton *> v, QColorPicker *colorPicker) {
    if (v.isEmpty())
        return;

    for (CaptureButton *b: m_vectorButtons)
        delete(b);
	m_colorPicker = colorPicker;
	m_btnWidget = parent;
    m_vectorButtons = v;
    m_buttonBaseSize = v[0]->buttonBaseSize();
    m_buttonExtendedSize = m_buttonBaseSize + SEPARATION;
}

QColor ButtonHandler::drawColor()
{
	return m_colorPicker->drawColor();
}

int ButtonHandler::thickNess()
{
	return m_colorPicker->thickNess();
}

void ButtonHandler::onShowColorPicker()
{
	m_colorPicker->show();
	updatePosition(m_selection);
}

void ButtonHandler::onHideColorPicker()
{
	m_colorPicker->hide();
	updatePosition(m_selection);
}

int ButtonHandler::getToolSpacePosition()
{
	if (m_colorPicker->isVisible())
	{
		return 92;
	}
	else
	{
		return 44;
	}
}