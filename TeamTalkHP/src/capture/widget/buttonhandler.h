// Copyright 2017 Alejandro Sirgo Rica
//
// This file is part of Flameshot.
//
//     Flameshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Flameshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Flameshot.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include "capturebutton.h"
#include <QVector>
#include <QObject>

class QColorPicker;
class CaptureButton;
class QRect;
class QPoint;

class ButtonHandler : public QObject {
    Q_OBJECT
public:
    ButtonHandler(const QRect &limits, QObject *parent = nullptr);

    void hideSectionUnderMouse(const QPoint &p);

    bool isVisible() const;
    bool buttonsAreInside() const;
    size_t size() const;

    void updatePosition(const QRect &selection);
	void setButtons(QWidget* parent, const QVector<CaptureButton*>, QColorPicker *colorPicker);

	QColor drawColor();
	int thickNess();

public slots:
    void hide();
    void show();
	void onShowColorPicker();
	void onHideColorPicker();

private:
	int getToolSpacePosition();

private:

	QWidget* m_btnWidget;
	QColorPicker *m_colorPicker;
    QVector<CaptureButton*> m_vectorButtons;

    int m_buttonExtendedSize;
    int m_buttonBaseSize;

    bool m_buttonsAreInside;
    bool m_blockedRight;
    bool m_blockedLeft;
    bool m_blockedBotton;
    bool m_blockedTop;
    bool m_oneHorizontalBlocked;
    bool m_horizontalyBlocked;
    bool m_allSidesBlocked;

    QRect m_limits;
    QRect m_selection;
};

#endif // BUTTONHANDLER_H
