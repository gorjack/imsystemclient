#include "commonFunc.h"
namespace utils
{

    std::wstring qToStdWString(const QString& str)
    {
#   ifdef _MSC_VER
        return std::wstring((const wchar_t*)str.utf16());
#   else
        return str.toStdWString();
#endif
    }

    QString stdWToQString(const std::wstring &str)
    {
#    ifdef _MSC_VER
        return QString::fromUtf16((const ushort*)str.c_str());
#    else
        return QString::fromStdWString(str);
#endif
    }

}