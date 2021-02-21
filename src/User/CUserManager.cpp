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
    char szAccountName[32] = { 0 };
    char szNickName[32] = { 0 };
    char szMarkName[32] = { 0 };
    char szSignature[256] = { 0 };
    char szPhoneNumber[32] = { 0 };
    char szMail[32] = { 0 };
    char szAddress[64] = { 0 };

    char szGroupAccount[32];

    CBuddyTeamInfo* pTeamInfo = NULL;
    int nTeamIndex = 0;
    for (const auto& iter : pResult->m_mapUserBasicInfo)
    {
        pTeamInfo = new CBuddyTeamInfo();
        pTeamInfo->m_nIndex = nTeamIndex;
        ++nTeamIndex;
        pTeamInfo->m_strName = iter.first;              //分组名称
        m_BuddyList.m_arrBuddyTeamInfo.push_back(pTeamInfo);

        for (auto& iter2 : iter.second)
        {
            //EncodeUtil::Utf8ToUnicode(iter2->szAccountName, szAccountName, sizeof(szAccountName)/sizeof(wchar_t));
            //EncodeUtil::Utf8ToUnicode(iter2->szNickName, szNickName, sizeof(szNickName) / sizeof(wchar_t));
            //EncodeUtil::Utf8ToUnicode(iter2->szMarkName, szMarkName, sizeof(szNickName) / sizeof(wchar_t));
            //EncodeUtil::Utf8ToUnicode(iter2->szSignature, szSignature, sizeof(szSignature) / sizeof(wchar_t));
            //EncodeUtil::Utf8ToUnicode(iter2->szPhoneNumber, szPhoneNumber, sizeof(szPhoneNumber) / sizeof(wchar_t));
            //EncodeUtil::Utf8ToUnicode(iter2->szMail, szMail, sizeof(szMail) / sizeof(wchar_t));
            //EncodeUtil::Utf8ToUnicode(iter2->szAddress, szAddress, sizeof(szAddress) / sizeof(wchar_t));

            pBuddyInfo = new CBuddyInfo();
            pBuddyInfo->m_uUserID = iter2->uAccountID;
            pBuddyInfo->m_strAccount.append(iter2->szAccountName);
            pBuddyInfo->m_strNickName.append(iter2->szNickName);
            pBuddyInfo->m_strMarkName.append(iter2->szMarkName);
            pBuddyInfo->m_strSign.append(iter2->szSignature);
            pBuddyInfo->m_strMobile.append(iter2->szPhoneNumber); 

            pBuddyInfo->m_strEmail.append(iter2->szMail);
            pBuddyInfo->m_strAddress.append(iter2->szAddress);
            pBuddyInfo->m_nStatus = iter2->nStatus;
            pBuddyInfo->m_nClientType = iter2->clientType;
            pBuddyInfo->m_nFace = iter2->uFaceID;
            pBuddyInfo->m_nBirthday = iter2->nBirthday;
            pBuddyInfo->m_nGender = iter2->nGender;

            pBuddyInfo->m_strCustomFaceName = iter2->customFace;
           //WTODO: TOUXIANG

            pBuddyInfo->m_nTeamIndex = 0;
            pTeamInfo->m_arrBuddyInfo.push_back(pBuddyInfo);
            m_mapAllUsers[pBuddyInfo->m_uUserID] = pBuddyInfo;
        }
    }

    emit sigFinishGetFriendListReq();
#endif
}

PC::CBuddyInfo* CUserManager::getBuddyInfoById(int nId)
{
    if (m_mapAllUsers.find(nId) != m_mapAllUsers.end())
    {
        return m_mapAllUsers[nId];
    }
    return NULL;
}

void CUserManager::setUserId(unsigned int id)
{
    m_nId = id;
}

unsigned int CUserManager::getUserId()
{
    return m_nId;
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
