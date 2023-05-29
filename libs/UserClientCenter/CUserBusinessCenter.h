#ifndef __CUSER_BUSINESS_CENTER__
#define __CUSER_BUSINESS_CENTER__


#include <string>
#include <vector>
#include <memory>

#if /*defined(UNICODE) || defined(_UNICODE)*/false
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

using UINT = unsigned int;

namespace PC
{

    class USER_EXPORT CBuddyInfo			// ������Ϣ
    {
    public:
        CBuddyInfo(void);
        ~CBuddyInfo(void);

    public:
        void Reset();
        void FillFakeData();	//TODO: ���������ݣ���Ϊ�˲��ԣ�ʵ�ʵ�����Ӧ�õȷ������������Ժ�ӷ�������ȡ
        void SetBuddyInfo(CBuddyInfo* lpBuddyInfo);

    public:
        UINT		m_uUserID;			//�û�ID��Ψһ��ʶ���û�
        tstring		m_strAccount;		//�û��˻���
        tstring		m_strPassword;		// ����
        tstring		m_strNickName;		// �ǳ�
        tstring		m_strMarkName;		// ��ע
        long		m_nTeamIndex;		// ��������
        UINT		m_nFace;			// ͷ��
        long		m_nStatus;			// ����״̬
        long        m_nClientType;      // �ͻ�������
        tstring		m_strSign;			// ����ǩ��
        long		m_nGender;			// �Ա�
        long		m_nBirthday;		// ����
        tstring		m_strMobile;		// �ֻ�
        tstring		m_strAddress;		// �û���ַ��Ϣ
        tstring		m_strEmail;
        bool		m_bUseCustomFace;		//�Ƿ�ʹ���Զ���ͷ��
        bool		m_bCustomFaceAvailable;	//�Զ���ͷ���Ƿ����
        tstring		m_strCustomFace;	    // �Զ���ͷ�������ļ�������·�������ز�������Ҫ�ӷ��������أ�
        tstring		m_strRawCustomFace;		//ԭʼ�Զ���ͷ������

        std::string    m_strCustomFaceName;

        UINT		m_uMsgID;			//�Ự��ϢID����ʼֵΪ0��ֻ�������ڴ��в��浵
    };

    typedef std::shared_ptr<CBuddyInfo>     CBuddyInfoPtr;

    class USER_EXPORT CBuddyTeamInfo		// ���ѷ�����Ϣ
    {
    public:
        CBuddyTeamInfo(void);
        ~CBuddyTeamInfo(void);

    public:
        void Reset();
        int GetBuddyCount();
        int GetOnlineBuddyCount();
        CBuddyInfo* GetBuddy(int nIndex);
        void Sort();

    public:
        int m_nIndex;			// ����
        int m_nSort;			// ����˳��
        tstring m_strName;		// ��������
        std::vector<CBuddyInfo*> m_arrBuddyInfo;
    };

    class USER_EXPORT CBuddyList	// �����б�
    {
    public:
        CBuddyList(void);
        ~CBuddyList(void);

    public:
        void Reset();
        int GetBuddyTeamCount();
        CBuddyTeamInfo* GetBuddyTeam(int nTeamIndex);
        CBuddyTeamInfo* GetBuddyTeamByIndex(int nIndex);
        int GetBuddyTotalCount();
        int GetBuddyCount(int nTeamIndex);
        int GetOnlineBuddyCount(int nTeamIndex);
        CBuddyInfo* GetBuddy(int nTeamIndex, int nIndex);
        CBuddyInfo* GetBuddy(UINT nUTalkUin);
        void SortBuddyTeam();
        void SortBuddy();
        bool AddBuddyTeam(CBuddyTeamInfo* lpBuddyTeamInfo);
        bool IsTeamNameExist(tstring& pszTeamName);

    public:
        int m_nRetCode;
        std::vector<CBuddyTeamInfo*> m_arrBuddyTeamInfo;
    };


}


#endif