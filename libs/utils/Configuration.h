#ifndef __UTILS_CONFIGURATION_H__
#define __UTILS_CONFIGURATION_H__

#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <boost/thread.hpp>
#include <string>
#include <boost/utility.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace utils
{
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
        static void readVecConfig(boost::shared_ptr<utils::Configuration> config, std::vector<T>& vec, string section, string propertyStr, string splitStr = ",")
        {
            if (config == NULL)
            {
                return;
            }
            string ps = config->read(section, propertyStr);
            vector<string> tmpTS;
            boost::split(tmpTS, ps, boost::is_any_of(splitStr));
            vec.clear();
            for (size_t i = 0; i < tmpTS.size(); i++)
            {
                if (!tmpTS[i].empty())
                {
                    try
                    {
                        vec.push_back(boost::lexical_cast<T>(tmpTS[i].c_str()));
                    }
                    catch (const boost::bad_lexical_cast& e)
                    {
                        std::cerr << "get bson value error, " << e.what() << std::endl;
                    }
                }
            }
        }

        //读取map类型的配置 例如"1;10012:0",  firstSplitStr含义是;切分平台用，secSplitStr是区分平台和内容 mapDefaultData是搭配的业务通用值，即没被平台特化的值，
        //比如例子的1 defaultData是读取不到配置的时候的缺省值
        template<typename TSec, typename TFir>
        static typename boost::disable_if< boost::is_enum<TSec>, void>::type
            readMapConfig(boost::shared_ptr<utils::Configuration> config, std::map<TFir, TSec>& mapData, TSec& mapDefaultData, string section, string propertyStr, \
            TSec defaultData, string firstSplitStr = ";", string secSplitStr = ":")
        {
            if (config == NULL)
            {
                return;
            }
            string ps = config->read(section, propertyStr);
            vector<string> tmpTS;
            boost::split(tmpTS, ps, boost::is_any_of(firstSplitStr));
            for (vector<string>::iterator it = tmpTS.begin(); it != tmpTS.end(); ++it)
            {
                try
                {
                    size_t pos = it->find(secSplitStr);
                    if (pos == std::string::npos)
                    {
                        if (it->empty())
                        {
                            *it = boost::lexical_cast<string>(defaultData);
                        }
                        mapDefaultData = (boost::lexical_cast<TSec>(it->substr(0, pos)));
                    }
                    else
                    {
                        TFir platform = boost::lexical_cast<TFir>(it->substr(0, pos));
                        mapData[platform] = (boost::lexical_cast<TSec>(it->substr(pos + 1, it->length() - pos - 1)));
                    }
                }
                catch (const boost::bad_lexical_cast& e)
                {
                    std::cerr << "get bson value error, " << e.what() << std::endl;
                }
            }
        }

        template<typename TSec, typename TFir>
        static typename boost::enable_if< boost::is_enum<TSec>, void>::type
            readMapConfig(boost::shared_ptr<utils::Configuration> config, std::map<TFir, TSec>& mapData, TSec& mapDefaultData, string section, string propertyStr, \
            TSec defaultData, string firstSplitStr = ";", string secSplitStr = ":")
        {
            if (config == NULL)
            {
                return;
            }
            string ps = config->read(section, propertyStr);
            vector<string> tmpTS;
            boost::split(tmpTS, ps, boost::is_any_of(firstSplitStr));
            for (vector<string>::iterator it = tmpTS.begin(); it != tmpTS.end(); ++it)
            {
                try
                {
                    size_t pos = it->find(secSplitStr);
                    if (pos == std::string::npos)
                    {
                        if (it->empty())
                        {
                            *it = boost::lexical_cast<string>(defaultData);
                        }
                        mapDefaultData = (TSec)(atoi(it->substr(0, pos).c_str()));
                    }
                    else
                    {
                        TFir platform = boost::lexical_cast<TFir>(it->substr(0, pos));
                        mapData[platform] = (TSec)(atoi(it->substr(pos + 1, it->length() - pos - 1).c_str()));
                    }
                }
                catch (const boost::bad_lexical_cast& e)
                {
                    std::cerr << "get bson value error, " << e.what() << std::endl;
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
        boost::recursive_mutex  m_lock; 
    };

    typedef boost::shared_ptr<Configuration> ConfigurationPtr;
}

#endif

