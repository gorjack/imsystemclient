#include <QtWidgets/QApplication>
#include <PanelChatWindow\CChatMainWindowDialog.h>
#include <PanelMainWindow\CMainWindow.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CChatMainWindowDialog *p = new CChatMainWindowDialog(NULL);
    p->setAttribute(Qt::WA_DeleteOnClose, true);
    p->show();

    //CMainWindow w;
    //w.show();



    int nRet = a.exec();


    return nRet;
}