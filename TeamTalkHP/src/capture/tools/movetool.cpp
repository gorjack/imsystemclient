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

#include "movetool.h"
#include <QPainter>

MoveTool::MoveTool(QObject *parent) : CaptureTool(parent) {

}

int MoveTool::id() const {
    return 0;
}

bool MoveTool::isSelectable() const {
    return false;
}

QString MoveTool::iconName() const {
    return ":/TeamTalkHP/Resources/MainWindow/screenImg/cursor-move.png";
}

QString MoveTool::name() const {
    return QStringLiteral("�ƶ���ͼ");
}

QString MoveTool::description() const {
	return QStringLiteral("�ƶ���ͼ");
}

CaptureTool::ToolWorkType MoveTool::toolType() const {
    return TYPE_WORKER;
}

void MoveTool::processImage(
        QPainter &painter,
        const QVector<QPoint> &points,
        const QColor &color,
        const int thickness)
{
    Q_UNUSED(painter);
    Q_UNUSED(points);
    Q_UNUSED(color);
    Q_UNUSED(thickness);
}

void MoveTool::onPressed() {
    Q_EMIT requestAction(REQ_MOVE_MODE);
}
