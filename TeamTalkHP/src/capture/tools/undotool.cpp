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

#include "undotool.h"
#include <QPainter>

UndoTool::UndoTool(QObject *parent) : CaptureTool(parent) {

}

int UndoTool::id() const {
    return 0;
}

bool UndoTool::isSelectable() const {
    return false;
}

QString UndoTool::iconName() const {
    return ":/TeamTalkHP/Resources/MainWindow/screenImg/Undo.png";
}

QString UndoTool::name() const {
    return QStringLiteral("�����༭");
}

QString UndoTool::description() const {
	return QStringLiteral("�����༭");
}

CaptureTool::ToolWorkType UndoTool::toolType() const {
    return TYPE_WORKER;
}

void UndoTool::processImage(
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

void UndoTool::onPressed() {
    Q_EMIT requestAction(REQ_UNDO_MODIFICATION);
}
