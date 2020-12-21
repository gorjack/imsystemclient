#pragma once
#include <string>

namespace UC
{
    struct PANELCHATWINDOW_EXPORT UserDataInfo
    {
        std::string        m_strName;
        std::string        m_strSign;
        int                m_nTargetId;
    };

    typedef struct UserDataInfo CUserDataInfo;
}