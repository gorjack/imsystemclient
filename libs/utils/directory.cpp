/**
 *  程序运行各个路径定义
 *
 *  @author gaojie
 *  @since  2020-11-19
 */

#include "directory.h"


namespace PATH
{
    QString getRootDir()
    {
         QDir dir(getAppBinDir());
         dir.cdUp();
         return QDir::toNativeSeparators(dir.absolutePath());
    }

    QString getAppBinDir()
    {
        return QDir::toNativeSeparators(qApp->applicationDirPath());
    }

    QString getUserRootDir()
    {
        return getRootDir() + QDir::separator() + "userdata" + QDir::separator() + "users";
    }

    QString getLogDir()
    {
        return getRootDir() + QDir::separator() + "userdata" + QDir::separator() + "logs";
    }


    QString getConfigDir()
    {
        return getRootDir() + QDir::separator() + "config";
    }

    QString getUserDir(QString qsUserName)
     {
         return getUserRootDir() + QDir::separator() + qsUserName;
     }

     QString getCurrentResourceDir()
     {
         QDir dir(qApp->applicationDirPath());
         dir.cdUp();
         dir.cd("resource");
         return dir.absolutePath();
     }

     QString getPluginDir()
     {
         return getRootDir() + QDir::separator() + "plugins";
     }

}
