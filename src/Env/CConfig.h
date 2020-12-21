#pragma once
#include <utils/CSingletonT.h>
#include <QString>
#include <map>

enum SERVERTYPE
{
    CHAT_SERVER,
    FILE_SERVER,
    IMAGE_SERVER,
};
class DLL_EXPORT_ENV CConfig : public utils::CSingletonT<CConfig>
{
public:
    CConfig();
    ~CConfig();

    const QString& userName();
    void setUserName(const QString &strName);
    void setPassWd(const QString& strPssWD);
    void loadData();
    bool loadFromFile(QString strFileName);
    bool save();

    std::map<SERVERTYPE, QString>&    getServers();
protected:
    QString                            m_strUserName;
    QString                            m_strPassWd;
    std::map<SERVERTYPE, QString>      m_servers;
};