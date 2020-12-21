#pragma once

#ifndef BUILD_STATIC
# if defined(PANELLOGINDIALOG_LIB)
#  define PANELLOGINDIALOG_EXPORT __declspec(dllexport)
# else
#  define PANELLOGINDIALOG_EXPORT __declspec(dllimport)
# endif

# if defined(EVENTLOOP_LIB)
#  define EVENTLOOP_EXPORT __declspec(dllexport)
# else
#  define EVENTLOOP_EXPORT __declspec(dllimport)
# endif

# if defined(USER_LIB)
#  define USER_EXPORT __declspec(dllexport)
# else
#  define USER_EXPORT __declspec(dllimport)
# endif

# if defined(WINLOG_LIB)
#  define WINLOG_EXPORT __declspec(dllexport)
# else
#  define WINLOG_EXPORT __declspec(dllimport)
# endif

# if defined(PROTOCOLDATA_LIB)
#  define PROTOCOLDATA_EXPORT __declspec(dllexport)
# else
#  define PROTOCOLDATA_EXPORT __declspec(dllimport)
# endif

# if defined(UTILS_LIB)
#  define UTILS_EXPORT __declspec(dllexport)
# else
#  define UTILS_EXPORT __declspec(dllimport)
# endif

# if defined(PANELMAINWINDOW_LIB)
#  define PANELMAINWINDOW_EXPORT __declspec(dllexport)
# else
#  define PANELMAINWINDOW_EXPORT __declspec(dllimport)
# endif

# if defined(PANELCHATWINDOW_LIB)
#  define PANELCHATWINDOW_EXPORT __declspec(dllexport)
# else
#  define PANELCHATWINDOW_EXPORT __declspec(dllimport)
# endif

# if defined(PANELBASEWIDGET_LIB)
#  define PANELBASEWIDGET_EXPORT __declspec(dllexport)
# else
#  define PANELBASEWIDGET_EXPORT __declspec(dllimport)
# endif

# if defined(ENV_LIB)
#  define DLL_EXPORT_ENV __declspec(dllexport)
# else
#  define DLL_EXPORT_ENV __declspec(dllimport)
# endif

#else
# define PANELLOGINDIALOG_EXPORT
#endif