#include "CUserBusinessCenter.h"
#include <ProtocolData/rpc_proEnum.h>

#define TRUE true
#define FALSE true

namespace PC
{
    using namespace protocol;
    CBuddyInfo::CBuddyInfo(void)
    {
        Reset();
        //FillFakeData();
    }

    CBuddyInfo::~CBuddyInfo(void)
    {

    }

    void CBuddyInfo::Reset()
    {
        m_uUserID = 0;
        m_strAccount = (L"");
        m_nTeamIndex = 0;
        m_strNickName = (L"");
        m_strMarkName = (L"");
        m_nFace = 0;
        m_strCustomFace = (L"");
        m_nStatus = STATUS_OFFLINE;
        m_nClientType = CLIENT_TYPE_UNKNOWN;
        m_strSign = (L"");
        m_nGender = 1;
        m_nBirthday = 0;
        m_strMobile = (L"");
        m_strEmail = (L"");
        m_strAddress = (L"");
        m_uMsgID = 0;
        m_bUseCustomFace = FALSE;
        m_bCustomFaceAvailable = FALSE;

        m_nTeamIndex = 0;
    }

    void CBuddyInfo::FillFakeData()
    {
        m_uUserID = 0;
        m_nTeamIndex = 0;
        m_strNickName = (L"孙悟空");
        m_strMarkName = (L"");
        m_nFace = 0;
        m_nStatus = STATUS_OFFLINE;
        m_strSign = (L"观乎其上,得乎其中,观乎其中,得乎其下。");
        m_nBirthday = 0;
        m_strMobile = (L"");
        m_strEmail = (L"balloonwj@UTalk.com");
        m_strAddress = (L"上海市闵行区东川路555号");
        m_uMsgID = 0;
        m_bUseCustomFace = FALSE;
        m_bCustomFaceAvailable = FALSE;
    }

    void CBuddyInfo::SetBuddyInfo(CBuddyInfo* lpBuddyInfo)
    {
        if (NULL == lpBuddyInfo)
            return;

        m_strAccount = lpBuddyInfo->m_strAccount;
        m_strNickName = lpBuddyInfo->m_strNickName;
        m_nFace = lpBuddyInfo->m_nFace;
        m_strCustomFace = lpBuddyInfo->m_strCustomFace;
        m_nGender = lpBuddyInfo->m_nGender;
        m_nBirthday = lpBuddyInfo->m_nBirthday;
        m_strMobile = lpBuddyInfo->m_strMobile;
        m_strEmail = lpBuddyInfo->m_strEmail;
        m_strAddress = lpBuddyInfo->m_strAddress;
        m_strSign = lpBuddyInfo->m_strSign;
    }


    //CBuddyTeamInfo==========================================
    CBuddyTeamInfo::CBuddyTeamInfo(void)
    {
        Reset();
    }

    CBuddyTeamInfo::~CBuddyTeamInfo(void)
    {

    }

    void CBuddyTeamInfo::Reset()
    {
        m_nIndex = 0;
        m_nSort = 0;
        m_strName = (L"");

        m_arrBuddyInfo.clear();
    }

    int CBuddyTeamInfo::GetBuddyCount()
    {
        return m_arrBuddyInfo.size();
    }

    int CBuddyTeamInfo::GetOnlineBuddyCount()
    {
        int nCount = 0;
        for (int i = 0; i < (int)m_arrBuddyInfo.size(); i++)
        {
            CBuddyInfo* lpBuddyInfo = m_arrBuddyInfo[i];
            if (lpBuddyInfo != NULL && lpBuddyInfo->m_nStatus != STATUS_OFFLINE && lpBuddyInfo->m_nStatus != STATUS_INVISIBLE)
                nCount++;
        }
        return nCount;
    }

    CBuddyInfo* CBuddyTeamInfo::GetBuddy(int nIndex)
    {
        if (nIndex >= 0 && nIndex < (int)m_arrBuddyInfo.size())
            return m_arrBuddyInfo[nIndex];
        else
            return NULL;
    }

    void CBuddyTeamInfo::Sort()
    {
        CBuddyInfo* lpBuddyInfo1, *lpBuddyInfo2;
        bool bExchange;
        int nCount;

        nCount = (int)m_arrBuddyInfo.size();
        for (int i = 0; i < nCount - 1; i++)
        {
            bExchange = FALSE;
            for (int j = nCount - 1; j > i; j--)
            {
                lpBuddyInfo1 = m_arrBuddyInfo[j - 1];
                lpBuddyInfo2 = m_arrBuddyInfo[j];
                if (lpBuddyInfo1 != NULL && lpBuddyInfo2 != NULL)
                {
                    if (lpBuddyInfo2->m_nStatus > lpBuddyInfo1->m_nStatus)
                    {
                        m_arrBuddyInfo[j - 1] = lpBuddyInfo2;
                        m_arrBuddyInfo[j] = lpBuddyInfo1;
                        bExchange = TRUE;
                    }
                }
            }
            if (!bExchange)
                break;
        }
    }


    //CBuddyList=============================
    CBuddyList::CBuddyList(void)
    {
        Reset();
    }

    CBuddyList::~CBuddyList(void)
    {
        Reset();
    }

    void CBuddyList::Reset()
    {
        m_nRetCode = 0;

        for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
        {
            CBuddyTeamInfo* lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
            if (lpBuddyTeamInfo != NULL)
                delete lpBuddyTeamInfo;
        }
        m_arrBuddyTeamInfo.clear();
    }

    int CBuddyList::GetBuddyTeamCount()
    {
        return m_arrBuddyTeamInfo.size();
    }

    CBuddyTeamInfo* CBuddyList::GetBuddyTeam(int nTeamIndex)
    {
        if (nTeamIndex >= 0 && nTeamIndex < (int)m_arrBuddyTeamInfo.size())
            return m_arrBuddyTeamInfo[nTeamIndex];
        else
            return NULL;
    }

    CBuddyTeamInfo* CBuddyList::GetBuddyTeamByIndex(int nIndex)
    {
        for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
        {
            CBuddyTeamInfo* lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
            if (lpBuddyTeamInfo != NULL && nIndex == lpBuddyTeamInfo->m_nIndex)
                return lpBuddyTeamInfo;
        }
        return NULL;
    }

    int CBuddyList::GetBuddyTotalCount()
    {
        size_t nTotalBuddyCount = 0;

        size_t nTeamCount = GetBuddyTeamCount();
        for (size_t i = 0; i < nTeamCount; ++i)
        {
            nTotalBuddyCount += GetBuddyCount(i);
        }

        return nTotalBuddyCount;
    }


    int CBuddyList::GetBuddyCount(int nTeamIndex)
    {
        CBuddyTeamInfo* lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
        if (lpBuddyTeamInfo != NULL)
            return lpBuddyTeamInfo->GetBuddyCount();
        else
            return 0;
    }

    int CBuddyList::GetOnlineBuddyCount(int nTeamIndex)
    {
        CBuddyTeamInfo* lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
        if (lpBuddyTeamInfo != NULL)
            return lpBuddyTeamInfo->GetOnlineBuddyCount();
        else
            return 0;
    }

    CBuddyInfo* CBuddyList::GetBuddy(int nTeamIndex, int nIndex)
    {
        CBuddyTeamInfo* lpBuddyTeamInfo = GetBuddyTeam(nTeamIndex);
        if (lpBuddyTeamInfo != NULL)
            return lpBuddyTeamInfo->GetBuddy(nIndex);
        else
            return NULL;
    }

    CBuddyInfo* CBuddyList::GetBuddy(UINT nUTalkUin)
    {
        for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
        {
            CBuddyTeamInfo* lpBuddyTeamInfo = m_arrBuddyTeamInfo[i];
            if (lpBuddyTeamInfo != NULL)
            {
                for (int j = 0; j < (int)lpBuddyTeamInfo->m_arrBuddyInfo.size(); j++)
                {
                    CBuddyInfo* lpBuddyInfo = lpBuddyTeamInfo->m_arrBuddyInfo[j];
                    //if (lpBuddyInfo != NULL && lpBuddyInfo->m_nUTalkUin == nUTalkUin)
                    if (lpBuddyInfo != NULL && lpBuddyInfo->m_uUserID == nUTalkUin)
                        return lpBuddyInfo;
                }
            }
        }
        return NULL;
    }


    void CBuddyList::SortBuddyTeam()
    {
        CBuddyTeamInfo* lpBuddyTeamInfo1, *lpBuddyTeamInfo2;
        bool bExchange;
        int nCount;

        nCount = (int)m_arrBuddyTeamInfo.size();
        for (int i = 0; i < nCount - 1; i++)
        {
            bExchange = FALSE;
            for (int j = nCount - 1; j > i; j--)
            {
                lpBuddyTeamInfo1 = m_arrBuddyTeamInfo[j - 1];
                lpBuddyTeamInfo2 = m_arrBuddyTeamInfo[j];
                if (lpBuddyTeamInfo1 != NULL && lpBuddyTeamInfo2 != NULL)
                {
                    if (lpBuddyTeamInfo2->m_nSort < lpBuddyTeamInfo1->m_nSort)
                    {
                        m_arrBuddyTeamInfo[j - 1] = lpBuddyTeamInfo2;
                        m_arrBuddyTeamInfo[j] = lpBuddyTeamInfo1;
                        bExchange = TRUE;
                    }
                }
            }
            if (!bExchange)
                break;
        }
    }

    void CBuddyList::SortBuddy()
    {
        for (int i = 0; i < (int)m_arrBuddyTeamInfo.size(); i++)
        {
            CBuddyTeamInfo* lpTeamInfo = m_arrBuddyTeamInfo[i];
            if (lpTeamInfo != NULL)
                lpTeamInfo->Sort();
        }
    }

    bool CBuddyList::AddBuddyTeam(CBuddyTeamInfo* lpBuddyTeamInfo)
    {
        if (NULL == lpBuddyTeamInfo)
            return FALSE;
        lpBuddyTeamInfo->m_nIndex = m_arrBuddyTeamInfo.size();
        m_arrBuddyTeamInfo.push_back(lpBuddyTeamInfo);
        return TRUE;
    }

    bool CBuddyList::IsTeamNameExist(tstring& pszTeamName)
    {
        CBuddyTeamInfo* pTeamInfo = NULL;
        size_t nTeamCount = m_arrBuddyTeamInfo.size();
        for (size_t i = 0; i < nTeamCount; ++i)
        {
            pTeamInfo = m_arrBuddyTeamInfo[i];
            if (pTeamInfo == NULL)
                continue;;

            if (pTeamInfo->m_strName == pszTeamName)
                return TRUE;
        }

        return FALSE;
    }
}