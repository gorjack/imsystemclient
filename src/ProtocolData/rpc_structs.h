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
        int 		m_nLoginType;            //��¼���ͣ�0��ʾʹ���ֻ��ŵ��룬1��ʾʹ���˺ŵ���
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

        SendServeType m_nType = CHAT_SERVER;        //������Ҫ�ߵķ�������Ĭ��δCHAT_SERVER.
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
        long m_nType;				//��������
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
        int   nStatus;              //����״̬
        int   clientType;           //�ͻ�������
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
       // key�Ƿ�������֣�value�Ǹ�����ѵļ���
        std::map<std::string, std::list<UserBasicInfoPtr>> m_mapUserBasicInfo;
    };
    typedef boost::shared_ptr<CUserBasicInfoResult> CUserBasicInfoResultPtr;

    class CFontInfo				// ������Ϣ
    {
    public:
        CFontInfo(void) : m_nSize(9), m_clrText(RGB(0, 0, 0)), m_strName(_T("΢���ź�")),
            m_bBold(FALSE), m_bItalic(FALSE), m_bUnderLine(FALSE) {}
        ~CFontInfo(void) {}

    public:
        int m_nSize;			// �����С
        std::string m_clrText;		// ������ɫ
        tstring m_strName;		// ��������
        bool m_bBold;			// �Ƿ�Ӵ�
        bool m_bItalic;			// �Ƿ���б
        bool m_bUnderLine;		// �Ƿ���»���
    };

    class CCustomFaceInfo		// �Զ��������Ϣ
    {
    public:
        CCustomFaceInfo(void) : m_nFileId(0), m_dwFileSize(0), m_bOnline(TRUE) {}
        ~CCustomFaceInfo(void) {}

    public:
        tstring m_strName;			// �����Զ������ʹ�ò���(TODO: ����ֶ��ȱ�������Ҫ�ã������Ժ���չ)
        unsigned int   m_nFileId;
        tstring m_strKey;
        tstring m_strServer;

        unsigned long  m_dwFileSize;		// �����Զ������ʹ�ò���
        tstring m_strFileName;
        tstring m_strFilePath;
        bool	m_bOnline;			//�����ļ�����ʱ�����ֶδ����ļ��������ļ����������ļ�
    };

    class CContent				// ��Ϣ����
    {
    public:
        CContent(void) : m_nType(CONTENT_TYPE_UNKNOWN), m_nFaceId(0), m_nShakeTimes(0) {}
        ~CContent(void) {}

    public:
        CONTENT_TYPE	m_nType;			// ��������
        CFontInfo		m_FontInfo;			// ������Ϣ
        tstring			m_strText;			// �ı���Ϣ
        int				m_nFaceId;			// ϵͳ����Id
        int				m_nShakeTimes;		// ���ڶ�������
        CCustomFaceInfo m_CFaceInfo;		// �Զ��������Ϣ�������͵���m_nType��m_CFaceInfo���ļ����й���Ϣ��
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
        unsigned int        m_nSendId;          //���͵�ʱ������ ���������Լ�ȡ��
        unsigned __int64    m_nTime;
    };
    typedef boost::shared_ptr<CBuddyMessage> CBuddyMessagePtr;

    class PROTOCOLDATA_EXPORT CUpdateTeamInfoRequest : public IData
    {
    public:
        CUpdateTeamInfoRequest(void) = default;
        ~CUpdateTeamInfoRequest(void) = default;

        virtual void encodePackage(std::string& str, int32_t nSeq) const override;

        int          m_opType;          //��������
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