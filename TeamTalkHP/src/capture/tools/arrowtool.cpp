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

#include "arrowtool.h"
#include <QPainter>
#include <QPainterPath>

namespace {

const int ArrowWidth = 10;
const int ArrowHeight = 18;

QPainterPath getArrowHead(QPoint p1, QPoint p2, const int thickness) {
    QLineF body(p1, p2);
    int originalLength = body.length();
    body.setLength(ArrowWidth + thickness*2);
    // move across the line up to the head
    QLineF temp(QPoint(0,0), p2-p1);
    temp.setLength(originalLength - ArrowHeight - thickness*2);
    QPointF bottonTranslation(temp.p2());

    // generates the transformation to center of the arrowhead
    body.setAngle(body.angle()+90);
    QPointF temp2 = p1-body.p2();
    QPointF centerTranslation((temp2.x()/2), (temp2.y()/2));

    body.translate(bottonTranslation);
    body.translate(centerTranslation);

    QPainterPath path;
    path.moveTo(p2);
    path.lineTo(body.p1());
    path.lineTo(body.p2());
    path.lineTo(p2);
    return path;
}

// gets a shorter line to prevent overlap in the point of the arrow
QLine getShorterLine(QPoint p1, QPoint p2, const int thickness) {
    QLineF l(p1, p2);
    l.setLength(l.length() - ArrowHeight - thickness*2);
    return l.toLine();
}

} // unnamed namespace

ArrowTool::ArrowTool(QObject *parent) : CaptureTool(parent) {

}

int ArrowTool::id() const {
    return 0;
}

bool ArrowTool::isSelectable() const {
    return true;
}

QString ArrowTool::iconName() const {
    return ":/TeamTalkHP/Resources/MainWindow/screenImg/Arrow.png";
}

QString ArrowTool::name() const {
    return QStringLiteral("箭头工具");
}

QString ArrowTool::description() const {
	return QStringLiteral("箭头工具");
}

CaptureTool::ToolWorkType ArrowTool::toolType() const {
    return TYPE_LINE_DRAWER;
}

void ArrowTool::processImage(
        QPainter &painter,
        const QVector<QPoint> &points,
        const QColor &color,
        const int thickness)
{
    painter.setPen(QPen(color, 2 + thickness));
    painter.drawLine(getShorterLine(points[0], points[1], thickness));
    painter.fillPath(getArrowHead(points[0], points[1], thickness), QBrush(color));
}

void ArrowTool::onPressed() {
}
