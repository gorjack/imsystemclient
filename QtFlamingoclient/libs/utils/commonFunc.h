#pragma once
#include <string>
#include <QString>
#include <QTextCodec>

namespace utils
{
    UTILS_EXPORT std::wstring qToStdWString(const QString& str);
    UTILS_EXPORT QString stdWToQString(const std::wstring &str);

    inline std::string qsToS(const QString& qs)
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        return qs.toUtf8().constData();
#else
        return qs.toLocal8Bit().constData();
#endif
    }

    inline QString sToQs(const std::string& s)
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        static QTextCodec * pCodec = QTextCodec::codecForName("UTF-8");
        return (NULL != pCodec) ? pCodec->toUnicode(s.c_str(), s.size()) : QString::fromStdString(s);
#else
        static QTextCodec * pCodec = QTextCodec::codecForName("System");
        return (NULL != pCodec) ? pCodec->toUnicode(s.c_str(), s.size()) : QString::fromStdString(s);
#endif
    }
}