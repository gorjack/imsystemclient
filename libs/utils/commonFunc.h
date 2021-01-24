#pragma once
#include <string>
#include <QString>
#include <QTextCodec>


namespace utils
{
    UTILS_EXPORT std::wstring qToStdWString(const QString& str);
    UTILS_EXPORT QString stdWToQString(const std::wstring &str);
    UTILS_EXPORT int getWavFileTimeSpan(QString qsWavFilePath);

    inline std::string qsToS(const QString& qs)
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        return qs.toUtf8().constData();
#else
        return qs.toLocal8Bit().constData();
#endif
    }

    template <typename T>
    inline void safeDeletePtr(T *&p)
    {
        if (NULL != p)
        {
            delete p;
            p = NULL;
        }
    }

    template <typename TContainer>
    inline void safeClearContainer(TContainer *pContainer)
    {
        typedef typename TContainer::iterator TContainerItr;
        if (NULL != pContainer)
        {
            for (TContainerItr it = pContainer->begin();
                it != pContainer->end(); it++)
            {
                delete (*it);
            }
            pContainer->clear();
        }
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