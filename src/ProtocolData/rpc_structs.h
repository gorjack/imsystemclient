#pragma once
#include <string>
#include "rpc_Enum.h"
#include "rpc_proEnum.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <set>
#include <map>
#include <list>

namespace net
{
    using namespace protocol;
    class PROTOCOLDATA_EXPORT CRegisterRequest
    {
    public:
        CRegisterRequest(const char* strAcc, const char* nickName, const char* passWd);
        ~CRegisterRequest();

        void encodePackage(std::string& str) const;
        
    public:
        char m_szAccountName[64];
        char m_szNickName[64];
        char m_szPassword[64];

    };

    class PROTOCOLDATA_EXPORT CRegisterResult
    {
    public:
        CRegisterResult() = default;
        ~CRegisterResult() = default;

        void decodePackage(const std::string& data);
    public:
        using unit_8 = unsigned char;
        unit_8 m_nResultCode = protocol::REGISTER_FAILED;
    };

    class PROTOCOLDATA_EXPORT CLoginRequest
    {
    public:
        CLoginRequest();
        CLoginRequest(const char* accStr, const char* passwd, int type, int status);
        ~CLoginRequest();

        void encodePackage(std::string& str) const;
    public:
        char		m_szAccountName[64];
        char		m_szPassword[64];
        int 		m_nLoginType;            //登录类型：0表示使用手机号登入，1表示使用账号登入
        int      	m_nStatus;	
    };

    class PROTOCOLDATA_EXPORT CLoginResult
    {
    public:
        using UINT = unsigned int;

        CLoginResult() = default;
        ~CLoginResult() = default;

        void decodePackage(const std::string& data);
    public:
        long m_LoginResultCode;
        UINT m_uAccountID;
        char m_szAccountName[32];
        char m_szNickName[32];
        char m_szSignature[256];
        long m_nFace;
        char m_szCustomFace[64];
        int  m_nGender;
        int  m_nBirthday;
        char m_szAddress[512];
        char m_szPhoneNumber[64];
        char m_szMail[256];
        long m_nStatus;
    };

    class PROTOCOLDATA_EXPORT IData
    {
    public:
        IData();
        ~IData();

        enum SendServeType
        {
            CHAT_SERVER,
            FILE_SERVER,
            IMAGE_SERVER,
        };

        void appendPackageHeader(std::string& str) const ;
        virtual void encodePackage(std::string& str, int32_t nSeq) const {};
        virtual bool decodePackage(const std::string& data) { return true; };

        SendServeType m_nType = CHAT_SERVER;        //此数据要走的服务类型默认未CHAT_SERVER.
    };

    typedef boost::shared_ptr<IData> IDataPtr;

    class PROTOCOLDATA_EXPORT CFindFriendRequest : public IData
    {
    public:
        CFindFriendRequest();
        ~CFindFriendRequest();

        virtual void encodePackage(std::string& str, int32_t nSeq) const override;
    public:
        char m_szAccountName[64];
        long m_nType;				//查找类型
    };

    typedef boost::shared_ptr<CFindFriendRequest> CFindFriendRequestPtr;


    class PROTOCOLDATA_EXPORT CFindFriendResult : public IData
    {
    public:
        CFindFriendResult();
        ~CFindFriendResult();

        bool decodePackage(const std::string& data) override;
    public:
        long m_nResultCode;
        unsigned int m_uAccountID;
        char m_szAccountName[64];
        char m_szNickName[64];
    };
    typedef boost::shared_ptr<CFindFriendResult> CFindFriendResultPtr;

    class PROTOCOLDATA_EXPORT COperateFriendRequest : public IData
    {
    public:
        COperateFriendRequest();
        ~COperateFriendRequest();

        virtual void encodePackage(std::string& str, int32_t nSeq) const override;

    public:
        unsigned int m_uAccountID;
        unsigned int m_uCmd;
    };
    typedef boost::shared_ptr<COperateFriendRequest> COperateFriendRequestPtr;



    class PROTOCOLDATA_EXPORT COperateFriendResult : public IData
    {
    public:
        COperateFriendResult();
        ~COperateFriendResult();

        bool decodePackage(const std::string& data) override;

    public:
        unsigned int m_uAccountID;
        unsigned int m_uCmd;
        char m_szAccountName[64];
        char m_szNickName[64];
    };
    typedef boost::shared_ptr<COperateFriendResult> COperateFriendResultPtr;

    struct UserBasicInfo
    {
        unsigned int  uAccountID;
        char  szAccountName[32];
        char  szNickName[64];
        char  szMarkName[64];
        char  szSignature[256];
        char  szAddress[51225];
        unsigned int  uFaceID;
        int   nStatus;              //在线状态
        int   clientType;           //客户端类型
        char  customFace[64];
        int   nGender;
        int   nBirthday;
        char  szPhoneNumber[64];
        char  szMail[64];
    };

    class PROTOCOLDATA_EXPORT CUserBasicInfoRequest : public IData
    {
    public:
        CUserBasicInfoRequest() = default;
        ~CUserBasicInfoRequest() = default;

        virtual void encodePackage(std::string& str, int32_t nSeq) const override;

    public:
        std::set<unsigned int> m_setAccountID;
    };
    typedef boost::shared_ptr<CUserBasicInfoRequest> CUserBasicInfoRequestPtr;


    class PROTOCOLDATA_EXPORT CUserBasicInfoResult : public IData
    {
    public:
        CUserBasicInfoResult() = default;
        ~CUserBasicInfoResult() = default;

        bool decodePackage(const std::string& data) override;
    public:
        using UserBasicInfoPtr = boost::shared_ptr<UserBasicInfo>;
       // key是分组的名字，value是该组好友的集合
        std::map<std::string, std::list<UserBasicInfoPtr>> m_mapUserBasicInfo;
    };
    typedef boost::shared_ptr<CUserBasicInfoResult> CUserBasicInfoResultPtr;

    class CFontInfo				// 字体信息
    {
    public:
        CFontInfo(void) : m_nSize(9), m_clrText(RGB(0, 0, 0)), m_strName(_T("微软雅黑")),
            m_bBold(FALSE), m_bItalic(FALSE), m_bUnderLine(FALSE) {}
        ~CFontInfo(void) {}

    public:
        int m_nSize;			// 字体大小
        std::string m_clrText;		// 字体颜色
        tstring m_strName;		// 字体名称
        bool m_bBold;			// 是否加粗
        bool m_bItalic;			// 是否倾斜
        bool m_bUnderLine;		// 是否带下划线
    };

    class CCustomFaceInfo		// 自定义表情信息
    {
    public:
        CCustomFaceInfo(void) : m_nFileId(0), m_dwFileSize(0), m_bOnline(TRUE) {}
        ~CCustomFaceInfo(void) {}

    public:
        tstring m_strName;			// 接收自定义表情使用参数(TODO: 这个字段先保留，不要用，留作以后扩展)
        unsigned int   m_nFileId;
        tstring m_strKey;
        tstring m_strServer;

        unsigned long  m_dwFileSize;		// 发送自定义表情使用参数
        tstring m_strFileName;
        tstring m_strFilePath;
        bool	m_bOnline;			//当是文件类型时，该字段代表文件是离线文件还是在线文件
    };

    class CContent				// 消息内容
    {
    public:
        CContent(void) : m_nType(CONTENT_TYPE_UNKNOWN), m_nFaceId(0), m_nShakeTimes(0) {}
        ~CContent(void) {}

    public:
        CONTENT_TYPE	m_nType;			// 内容类型
        CFontInfo		m_FontInfo;			// 字体信息
        tstring			m_strText;			// 文本信息
        int				m_nFaceId;			// 系统表情Id
        int				m_nShakeTimes;		// 窗口抖动次数
        CCustomFaceInfo m_CFaceInfo;		// 自定义表情信息（当发送的是m_nType，m_CFaceInfo是文件的有关信息）
    };

    
    class PROTOCOLDATA_EXPORT CBuddyMessage : public IData
    {
    public:
        CBuddyMessage(void) = default;
        ~CBuddyMessage(void) = default;

        virtual void encodePackage(std::string& str, int32_t nSeq) const override;
        bool decodePackage(const std::string& data) override;

        CONTENT_TYPE			        m_nMsgType;
        std::vector<std::shared_ptr<CContent>>   m_arrContent;

        std::string         m_msgMesText;
        unsigned int        m_nTargetId;
        unsigned int        m_nSendId;          //发送的时候不用填 服务器能自己取到
        unsigned __int64    m_nTime;
    };
    typedef boost::shared_ptr<CBuddyMessage> CBuddyMessagePtr;

    class PROTOCOLDATA_EXPORT CUpdateTeamInfoRequest : public IData
    {
    public:
        CUpdateTeamInfoRequest(void) = default;
        ~CUpdateTeamInfoRequest(void) = default;

        virtual void encodePackage(std::string& str, int32_t nSeq) const override;

        int          m_opType;          //操作类型
        std::wstring m_strNewTeamName;
        std::wstring m_strOldTeamName;
    };
    typedef boost::shared_ptr<CUpdateTeamInfoRequest> CUpdateTeamInfoRequestPtr;

    struct PROTOCOLDATA_EXPORT FileSendResult
    {
        int         errorCode;
        std::string      fileMd5;
        std::string      fileName;
        int64_t     offSetX;
        int64_t     fileSize;
    };

    class PROTOCOLDATA_EXPORT CUpLoadFileRequest : public IData
    {
    public:
        CUpLoadFileRequest(void) { m_nType = FILE_SERVER; };
        ~CUpLoadFileRequest(void) = default;

        static bool decodePackage(const char* inbuf, size_t buflength, FileSendResult& errorCode);
        virtual void encodePackage(std::string& str, int32_t nSeq) const override;

        std::string       m_strMd5;
        std::string       m_strContent;
        std::string       m_strFileName;
        int64_t           m_offsetX;
        int64_t           m_nFileSize;
    };
    typedef boost::shared_ptr<CUpLoadFileRequest> CUpLoadFileRequestPtr;
}