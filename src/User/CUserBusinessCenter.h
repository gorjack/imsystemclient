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

    class USER_EXPORT CBuddyInfo			// 好友信息
    {
    public:
        CBuddyInfo(void);
        ~CBuddyInfo(void);

    public:
        void Reset();
        void FillFakeData();	//TODO: 填充虚假数据，仅为了测试，实际的数据应该等服务器端完善以后从服务器获取
        void SetBuddyInfo(CBuddyInfo* lpBuddyInfo);

    public:
        UINT		m_uUserID;			//用户ID，唯一标识该用户
        tstring		m_strAccount;		//用户账户名
        tstring		m_strPassword;		// 密码
        tstring		m_strNickName;		// 昵称
        tstring		m_strMarkName;		// 备注
        long		m_nTeamIndex;		// 分组索引
        UINT		m_nFace;			// 头像
        long		m_nStatus;			// 在线状态
        long        m_nClientType;      // 客户端类型
        tstring		m_strSign;			// 个性签名
        long		m_nGender;			// 性别
        long		m_nBirthday;		// 生日
        tstring		m_strMobile;		// 手机
        tstring		m_strAddress;		// 用户地址信息
        tstring		m_strEmail;
        bool		m_bUseCustomFace;		//是否使用自定义头像
        bool		m_bCustomFaceAvailable;	//自定义头像是否可用
        tstring		m_strCustomFace;	    // 自定有头像名（文件名不是路径，本地不存在需要从服务器下载）
        tstring		m_strRawCustomFace;		//原始自定义头像内容

        std::string    m_strCustomFaceName;

        UINT		m_uMsgID;			//会话消息ID，初始值为0，只存在于内存中不存档
    };

    typedef std::shared_ptr<CBuddyInfo>     CBuddyInfoPtr;

    class USER_EXPORT CBuddyTeamInfo		// 好友分组信息
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
        int m_nIndex;			// 索引
        int m_nSort;			// 排列顺序
        tstring m_strName;		// 分组名称
        std::vector<CBuddyInfo*> m_arrBuddyInfo;
    };

    class USER_EXPORT CBuddyList	// 好友列表
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