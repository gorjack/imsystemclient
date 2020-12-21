#include "appUtil.h"
#include "directory.h"
#include <QLibrary>
#include <QtPlugin>

void loadQtImagePlugins()
{
    const char* pImgName[] = { "gif", "ico", "jepg", "mng", "svg", "tiff", NULL };
    for (int i = 0; i < 7 && pImgName[i] != NULL; i++)
    {
        QString filename = QString("%1\\imageformats\\q%2%3").arg(QF::getPluginDir()).arg(pImgName[i]).arg(".dll");
        QLibrary* pLib = new QLibrary(filename);
        if (pLib != NULL)
        {
            void* pFN = pLib->resolve("qt_plugin_instance");

            if (pFN != NULL)
            {
                qRegisterStaticPluginFunction(*((QStaticPlugin*)pFN));
            }
            else
            {
                delete pLib;
            }
        }
    }
}

