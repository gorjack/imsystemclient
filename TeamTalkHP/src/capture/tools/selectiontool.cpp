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

#include "selectiontool.h"
#include <QPainter>

SelectionTool::SelectionTool(QObject *parent) : CaptureTool(parent) {

}

int SelectionTool::id() const {
    return 0;
}

bool SelectionTool::isSelectable() const {
    return true;
}

QString SelectionTool::iconName() const {
	return ":/TeamTalkHP/Resources/MainWindow/screenImg/Rectangle.png";
}

QString SelectionTool::name() const {
    return QStringLiteral("矩形工具");
}

QString SelectionTool::description() const {
	return QStringLiteral("矩形工具");
}

CaptureTool::ToolWorkType SelectionTool::toolType() const {
    return TYPE_LINE_DRAWER;
}

void SelectionTool::processImage(
        QPainter &painter,
        const QVector<QPoint> &points,
        const QColor &color,
        const int thickness)
{
    painter.setPen(QPen(color, 2 + thickness));
    painter.drawRect(QRect(points[0], points[1]));
}

void SelectionTool::onPressed() {
}
