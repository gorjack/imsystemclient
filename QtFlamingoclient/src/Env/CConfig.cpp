#include "CConfig.h"
#include <utils/CSingletonT.hpp>
#include <utils/strings.h>
#include "directory.h"
#include <utils/FileHelper.h>
#include <utils/commonFunc.h>
#include <winlog/IULog.h>
#include <jsoncpp/reader.h>


IMPL_SINGLETON_CLASS(CConfig);
const char* const g_cAddrName = "addressconf.json";

CConfig::CConfig()
{

}

CConfig::~CConfig()
{

}

const QString& CConfig::userName()
{
    return m_strUserName;
}

void CConfig::setUserName(const QString &strName)
{
    m_strUserName = strName;

    QString strPath = QF::getUserRootDir();
    QDir d(strPath);
    if (!d.exists())
    {
        d.mkpath(".");
    }

    if (!d.exists(m_strUserName))
    {
        d.mkpath(m_strUserName);
    }
}

void CConfig::setPassWd(const QString& strPssWD)
{
    m_strPassWd = strPssWD;
}

void CConfig::loadData()
{
    QString strConfigPath = QF::getUserRootDir() + QDir::separator() + g_cAddrName;
    if (!loadFromFile(strConfigPath))
    {
        strConfigPath = QF::getConfigDir() + QDir::separator() + g_cAddrName;
        loadFromFile(strConfigPath);
    }
}

bool CConfig::loadFromFile(QString strFileName)
{
    m_servers.clear();
    std::string content;
    std::string strPath = utils::qsToS(strFileName);
    if (!utils::FileHelper::open(strPath, content))
    {
        LOG_INFO("file %s open error", content);
        return false;
    }

    utils::string_replace(content, '\r', "");
    utils::string_replace(content, '\n', "");

    Json::Reader JsonReader;
    Json::Value JsonValue;
    if (JsonReader.parse(content, JsonValue))
    {
        if (!JsonValue["m_services"].isNull() && JsonValue["m_services"].isArray())
        {
            for (int i = 0; i < JsonValue["m_services"].size(); ++i)
            {
                int type = JsonValue["m_services"][i]["m_type"].asInt();
                std::string address = JsonValue["m_services"][i]["m_addr"].asCString();
                m_servers[(SERVERTYPE)type] = utils::sToQs(address);
            }
            return true;
        }
    }

    return false;
}

bool CConfig::save()
{
    QString strConfigPath = QF::getUserRootDir() + QDir::separator() + g_cAddrName;
    std::string content;

    content = R"({ \n \t"m_services": [ )";
    for (const auto& iter : m_servers)
    {
        ostringstream str;
        str << "\n\t\t{ \n \t\t\t \"m_type\" " << ":" << to_string(iter.first)
            << ",\n\t\t\t" << "m_addr" << ":" << utils::qsToS(iter.second) << ",\n\t\t },";
        content += str.str();
    }

    if (!utils::FileHelper::open(utils::qsToS(strConfigPath), content))
    {
        LOG_INFO("save file %s is error", utils::qsToS(strConfigPath));
        return false;
    }
    return true;
}

std::map<SERVERTYPE, QString>& CConfig::getServers()
{
    return m_servers;
}

