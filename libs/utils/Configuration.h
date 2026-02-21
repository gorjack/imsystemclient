#ifndef __UTILS_CONFIGURATION_H__
#define __UTILS_CONFIGURATION_H__

#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <mutex>
#include <memory>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>

using namespace std;

namespace utils
{
    // Minimal replacement for boost::lexical_cast used in this header.
    // Supports conversions: From arbitrary type -> To (using ostringstream/isosstream).
    template<typename To, typename From>
    typename std::enable_if<!std::is_same<To, std::string>::value, To>::type
    lexical_cast(const From& src)
    {
        std::ostringstream oss;
        oss << src;
        std::istringstream iss(oss.str());
        To dst;
        if (!(iss >> dst))
        {
            throw std::invalid_argument("bad lexical_cast");
        }
        return dst;
    }

    // Specialization / overload when target is string
    template<typename To = std::string, typename From>
    typename std::enable_if<std::is_same<To, std::string>::value, To>::type
    lexical_cast(const From& src)
    {
        std::ostringstream oss;
        oss << src;
        return oss.str();
    }

    // Overload: convert from string to To
    template<typename To>
    typename std::enable_if<!std::is_same<To, std::string>::value, To>::type
    lexical_cast(const std::string& src)
    {
        std::istringstream iss(src);
        To dst;
        if (!(iss >> dst))
        {
            throw std::invalid_argument("bad lexical_cast");
        }
        return dst;
    }

    // Overload: string -> string (identity)
    inline std::string lexical_cast_string(const std::string& src)
    {
        return src;
    }

    // Replacement for boost::algorithm::split(..., is_any_of(delims))
    inline void splitString(const std::string& input, std::vector<std::string>& output, const std::string& delims)
    {
        output.clear();
        if (input.empty())
        {
            return;
        }
        size_t start = 0;
        while (start <= input.size())
        {
            size_t pos = input.find_first_of(delims, start);
            if (pos == std::string::npos)
            {
                output.push_back(input.substr(start));
                break;
            }
            output.push_back(input.substr(start, pos - start));
            start = pos + 1;
        }
    }

    class UTILS_EXPORT Configuration
    {
    public:
        Configuration(string configFilePath = "", bool needToLower = true);
        virtual ~Configuration();

    public:

        void setConfigFilePath(const std::string& strPath);
        /* 加载配置文件 */
        bool load(string configFilePath = "");

        /* 解析配置 */
        bool parse(string content);

        /* 保存配置到文件 */
        bool save();

        /* 将内容展示成string */
        string dump();

        /* 保存内容 */
        bool save(string content);

        /* 读取某个section的某个属性的字符串值 */
        string read(string section, string property);

        /* 读取某个section的某个属性的整数值 */
        int readInt(string section, string property, int defaultValue);

        /* 读取某个section的某个属性的浮点数值 */
        double readDouble(const string& section, string property, double defaultValue);

        /* 读取某个section的某个属性的字符串列表值 */
        vector<string> readVector(const string& section, string property, string sep);

        /* 写入某个section的某个属性的字符串值 */
        void write(string section, string property, string value);

        /* 写入某个section的某个属性的整数值 */
        void write(string section, string property, int value);

        /* 写入某个section的某个属性的浮点数值 */
        void write(string section, string property, double value);

        /* 写入某个section的某个属性的字符串列表值 */
        void write(string& section, string property, vector<string>& value, string sep);

        /* 读取section列表 */
        vector<string> getSections();

        /* 读取某个section的属性列表 */
        vector<string> getProperties(const string& section);

        /*拿某个section属性map*/
        const map<string, string>& getPropertiesMapRef(const string &section) const;

        //读取vec类型的配置
        template<typename T>
        static void readVecConfig(std::shared_ptr<utils::Configuration> config, std::vector<T>& vec, string section, string propertyStr, string splitStr = ",")
        {
            if (config == NULL)
            {
                return;
            }
            string ps = config->read(section, propertyStr);
            vector<string> tmpTS;
            utils::splitString(ps, tmpTS, splitStr);
            vec.clear();
            for (size_t i = 0; i < tmpTS.size(); i++)
            {
                if (!tmpTS[i].empty())
                {
                    try
                    {
                        vec.push_back(utils::lexical_cast<T>(tmpTS[i]));
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << "get bson value error, " << e.what() << std::endl;
                    }
                }
            }
        }

    public:
        string              argvParm;           //运行参数
        string              m_strServerAdd;      //ip地址 运行状态拓扑图的需要
        string              m_strclientAdd;      //ip地址 运行状态拓扑图的需要

    private:
        string              m_configFilePath;   // 配置文件路径
        bool                     m_needToLower;        // 是否需要强制小写
        map<string, map<string,string> > m_properties; // 属性表
        std::recursive_mutex  m_lock; 
    };

    typedef std::shared_ptr<Configuration> ConfigurationPtr;
}

#endif

