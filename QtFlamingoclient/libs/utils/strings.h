#pragma once
#include <string>
using namespace std;

namespace utils
{
    // 去掉两头的引号
    UTILS_EXPORT std::string trimQuotation(const std::string & strIn);

    /**
    * 从形如192.168.1.1:80这样的字符串中解析ip和port
    */
    UTILS_EXPORT void getIpPort(const string& data, string& ip, unsigned short& port);

    /**
    * 从形如192.168.1.1:80这样的字符串中解析ip和port
    */
    UTILS_EXPORT void getIpPort(const char* data, string& ip, unsigned short& port);

    UTILS_EXPORT void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst);
    UTILS_EXPORT void string_replace(std::string &strBig, char c, const::std::string & strdst);
}
