#pragma once
#include <string>
using namespace std;

namespace utils
{
    // ȥ����ͷ������
    UTILS_EXPORT std::string trimQuotation(const std::string & strIn);

    /**
    * ������192.168.1.1:80�������ַ����н���ip��port
    */
    UTILS_EXPORT void getIpPort(const string& data, string& ip, unsigned short& port);

    /**
    * ������192.168.1.1:80�������ַ����н���ip��port
    */
    UTILS_EXPORT void getIpPort(const char* data, string& ip, unsigned short& port);

    UTILS_EXPORT void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst);
    UTILS_EXPORT void string_replace(std::string &strBig, char c, const::std::string & strdst);
}
