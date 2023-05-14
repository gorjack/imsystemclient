#include "TeamTalkHP.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TeamTalkHP w;
    w.show();
    return a.exec();
}
