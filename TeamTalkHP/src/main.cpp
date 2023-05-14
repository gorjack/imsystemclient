#include "UserLogin.h"
#include "ccmainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);
    UserLogin* w = new UserLogin;
	w->show();
	return a.exec();
}
