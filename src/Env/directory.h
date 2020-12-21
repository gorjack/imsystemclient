#pragma once
#include <QString>
#include <QDir>
#include <QtCore/QCoreApplication>

namespace QF
{
    DLL_EXPORT_ENV QString getRootDir();
    DLL_EXPORT_ENV QString getAppBinDir();
    DLL_EXPORT_ENV QString getUserRootDir();
    DLL_EXPORT_ENV QString getConfigDir();
    DLL_EXPORT_ENV QString getUserDir(QString qsUserName);
    DLL_EXPORT_ENV QString getCurrentResourceDir();
    DLL_EXPORT_ENV QString getPluginDir();
    DLL_EXPORT_ENV QString getLogDir();
}
