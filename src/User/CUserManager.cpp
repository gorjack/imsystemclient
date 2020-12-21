#include "CUserManager.h"
#include "CFlamingoClientCenter.h"
#include <ProtocolData/rpc_Enum.h>
#include <ProtocolData/rpc_structs.h>
#include <utils/EncodeUtil.h>
#include <utils/CSingletonT.hpp>

IMPL_SINGLETON_CLASS(CUserManager);
CUserManager::CUserManager()
{
    CFlamingoClientCenter::instance()->registCallBack(protocol::msg_type_getofriendlist, std::bind(&CUserManager::onGetFirendListCallBack, this, std::placeholders::_1));
}

CUserManager::~CUserManager()
{

}

const PC::CBuddyList& CUserManager::getFirendList()
{
    return m_BuddyList;
}

void CUserManager::queryFirendList()
{
    net::CUserBasicInfoRequestPtr pData(new net::CUserBasicInfoRequest);

    CFlamingoClientCenter::instance()->request_async(pData);
}

void CUserManager::onGetFirendListCallBack(const std::string & data)
{
    ClearUserInfo();
#if 1
    using namespace net;
    CUserBasicInfoResultPtr pResult(new CUserBasicInfoResult);
    pResult->decodePackage(data);

    using namespace PC;
    CBuddyInfo* pBuddyInfo = NULL;
    wchar_t szAccountName[32] = { 0 };
    wchar_t szNickName[32] = { 0 };
    wchar_t szMarkName[32] = { 0 };
    wchar_t szSignature[256] = { 0 };
    wchar_t szPhoneNumber[32] = { 0 };
    wchar_t szMail[32] = { 0 };
    wchar_t szAddress[64] = { 0 };

    wchar_t szGroupAccount[32];

    CBuddyTeamInfo* pTeamInfo = NULL;
    //CGroupInfo* pGroupInfo = NULL;
    int nTeamIndex = 0;
    for (const auto& iter : pResult->m_mapUserBasicInfo)
    {
        pTeamInfo = new CBuddyTeamInfo();
        pTeamInfo->m_nIndex = nTeamIndex;
        ++nTeamIndex;
        pTeamInfo->m_strName = EncodeUtil::Utf8ToUnicode(iter.first);
        m_BuddyList.m_arrBuddyTeamInfo.push_back(pTeamInfo);

        for (auto& iter2 : iter.second)
        {
            EncodeUtil::Utf8ToUnicode(iter2->szAccountName, szAccountName, sizeof(szAccountName)/sizeof(wchar_t));
            EncodeUtil::Utf8ToUnicode(iter2->szNickName, szNickName, sizeof(szNickName) / sizeof(wchar_t));
            EncodeUtil::Utf8ToUnicode(iter2->szMarkName, szMarkName, sizeof(szNickName) / sizeof(wchar_t));
            EncodeUtil::Utf8ToUnicode(iter2->szSignature, szSignature, sizeof(szSignature) / sizeof(wchar_t));
            EncodeUtil::Utf8ToUnicode(iter2->szPhoneNumber, szPhoneNumber, sizeof(szPhoneNumber) / sizeof(wchar_t));
            EncodeUtil::Utf8ToUnicode(iter2->szMail, szMail, sizeof(szMail) / sizeof(wchar_t));
            EncodeUtil::Utf8ToUnicode(iter2->szAddress, szAddress, sizeof(szAddress) / sizeof(wchar_t));

            pBuddyInfo = new CBuddyInfo();
            pBuddyInfo->m_uUserID = iter2->uAccountID;
            pBuddyInfo->m_strAccount = szAccountName;
            pBuddyInfo->m_strNickName = szNickName;
            pBuddyInfo->m_strMarkName = szMarkName;
            pBuddyInfo->m_strSign = szSignature;
            pBuddyInfo->m_strMobile = szPhoneNumber;

            pBuddyInfo->m_strEmail = szMail;
            pBuddyInfo->m_strAddress = szAddress;
            pBuddyInfo->m_nStatus = iter2->nStatus;
            pBuddyInfo->m_nClientType = iter2->clientType;
            pBuddyInfo->m_nFace = iter2->uFaceID;
            pBuddyInfo->m_nBirthday = iter2->nBirthday;
            pBuddyInfo->m_nGender = iter2->nGender;

            pBuddyInfo->m_strCustomFaceName = iter2->customFace;
           //WTODO: TOUXIANG

            pBuddyInfo->m_nTeamIndex = 0;
            pTeamInfo->m_arrBuddyInfo.push_back(pBuddyInfo);
        }
    }

    emit sigFinishGetFriendListReq();
#endif
}

void CUserManager::ClearUserInfo()
{
    long nMemberCount = 0;
    PC::CBuddyTeamInfo* pBuddyTeamInfo = NULL;
    PC::CBuddyInfo*		pBuddyInfo = NULL;

    while (m_BuddyList.m_arrBuddyTeamInfo.size() > 0)
    {
        long nLast = m_BuddyList.m_arrBuddyTeamInfo.size() - 1;
        nMemberCount = m_BuddyList.m_arrBuddyTeamInfo[nLast]->m_arrBuddyInfo.size();
        for (long j = 0; j < nMemberCount; ++j)
        {
            pBuddyInfo = m_BuddyList.m_arrBuddyTeamInfo[nLast]->m_arrBuddyInfo[j];
            if (pBuddyInfo != NULL)
                delete pBuddyInfo;

        }
        m_BuddyList.m_arrBuddyTeamInfo[nLast]->m_arrBuddyInfo.clear();

        pBuddyTeamInfo = m_BuddyList.m_arrBuddyTeamInfo[nLast];
        if (pBuddyTeamInfo != NULL)
            delete pBuddyTeamInfo;

        //删除最后一个元素
        m_BuddyList.m_arrBuddyTeamInfo.pop_back();
    }
}
