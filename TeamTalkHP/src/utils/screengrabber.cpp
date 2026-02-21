#include "screengrabber.h"
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QtWidgets/QDesktopWidget>

ScreenGrabber::ScreenGrabber(QObject *parent) : QObject(parent) {

}

QPixmap ScreenGrabber::grabEntireDesktop(bool &ok) {
    ok = true;
    QRect geometry;
    for (QScreen *const screen : QGuiApplication::screens()) {
        geometry = geometry.united(screen->geometry());
    }

    QPixmap p(QApplication::primaryScreen()->grabWindow(
                  0,
                  geometry.x(),
                  geometry.y(),
                  geometry.width(),
                  geometry.height())
              );
    return p;
}
