#pragma once
#include <QString>
#include <QDir>
#include <QtCore/QCoreApplication>

namespace PATH
{
    UTILS_EXPORT QString getRootDir();
    UTILS_EXPORT QString getAppBinDir();
    UTILS_EXPORT QString getUserRootDir();
    UTILS_EXPORT QString getConfigDir();
    UTILS_EXPORT QString getUserDir(QString qsUserName);
    UTILS_EXPORT QString getCurrentResourceDir();
    UTILS_EXPORT QString getPluginDir();
    UTILS_EXPORT QString getLogDir();
}
