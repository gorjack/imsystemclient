#pragma once
#include <string>
#include <ProtocolData/rpc_structs.h>
#include <memory>
#include <vector>
/*
    todo: 多个消息会重叠
*/

namespace UC
{
    class PANELCHATWINDOW_EXPORT CUserDataInfo
    {
    public:
        std::string        m_strName;
        std::string        m_strSign;
        int                m_nTargetId;
        net::CBuddyMessagePtr   m_pMessageData;
    };

    typedef std::shared_ptr<CUserDataInfo> CUserDataInfoPtr;
   // typedef struct UserDataInfo CUserDataInfo;
}