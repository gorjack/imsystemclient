#include "strings.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <sstream>

namespace utils
{
    UTILS_EXPORT std::string trimQuotation(const std::string & strIn)
    {
        std::string strOut = strIn;
        if (!strOut.empty())
        {
            if (strOut[0] == '\"')
            {
                strOut = strOut.substr(1, strOut.size() - 1);
            }
            if (strOut[strOut.size() - 1] == '\"')
            {
                strOut = strOut.substr(0, strOut.size() - 1);
            }
        }
        return strOut;
    }

    UTILS_EXPORT void getIpPort(const string& data, string& ip, unsigned short& port)
    {
        vector<string> items;
        boost::split(items, data, boost::is_any_of(":"));
        if (items.size() == 2)
        {
            ip = items[0];
            port = atoi(items[1].c_str());

        }
        else
        {
            ip = "0.0.0.0";
            port = 0;
        }
    }

    UTILS_EXPORT void getIpPort(const char* data, string& ip, unsigned short& port)
    {
        return getIpPort(string(data), ip, port);
    }

    UTILS_EXPORT void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
    {
        std::string::size_type last_pos = 0;
        std::string::size_type pos = 0;
        std::string::size_type srclen = strsrc.size();
        std::stringstream ss;

        while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
        {
            ss << strBig.substr(last_pos, pos - last_pos) << strdst;
            pos += srclen;
            last_pos = pos;
        }
        ss << strBig.substr(last_pos, strBig.size() - last_pos);
        strBig = ss.str();
    }

    UTILS_EXPORT void string_replace(std::string &strBig, char c, const::std::string & strdst)
    {
        std::string::size_type last_pos = 0;
        std::string::size_type pos = 0;
        std::stringstream ss;

        while ((pos = strBig.find(c, pos)) != std::string::npos)
        {
            ss << strBig.substr(last_pos, pos - last_pos) << strdst;
            pos += 1;
            last_pos = pos;
        }
        ss << strBig.substr(last_pos, strBig.size() - last_pos);
        strBig = ss.str();
    }

    UTILS_EXPORT int string_matches(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        int nT = vscanf(format, args);
        va_end(args);

        return nT;
    }

}