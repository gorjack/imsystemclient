#include "blurtool.h"
#include <QPainter>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

BlurTool::BlurTool(QObject *parent) : CaptureTool(parent) {

}

int BlurTool::id() const {
    return 0;
}

bool BlurTool::isSelectable() const {
    return true;
}

QString BlurTool::iconName() const {
    return ":/TeamTalkHP/Resources/MainWindow/screenImg/Mosaic.png";
}

QString BlurTool::name() const {
    return QStringLiteral("马赛克工具");
}

QString BlurTool::description() const {
	return QStringLiteral("马赛克工具");
}

CaptureTool::ToolWorkType BlurTool::toolType() const {
    return TYPE_LINE_DRAWER;
}
#include <QApplication>
void BlurTool::processImage(
        QPainter &painter,
        const QVector<QPoint> &points,
        const QColor &color,
        const int thickness)
{
    Q_UNUSED(color);
    Q_UNUSED(thickness);
    QPoint p0 = points[0];
    QPoint p1 = points[1];

    QRect selection = QRect(p0, p1).normalized();
    QPixmap *refPixmap = dynamic_cast<QPixmap*>(painter.device());

    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(10);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem (
                refPixmap->copy(selection));
    item->setGraphicsEffect(blur);

    QGraphicsScene scene;
    scene.addItem(item);

    scene.render(&painter, selection, QRectF());
    blur->setBlurRadius(15);
    scene.render(&painter, selection, QRectF());
}

void BlurTool::onPressed() {
}
