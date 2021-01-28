#pragma once
#include <QString>

enum ChatFileDirection {
    RIGHT_FILE_DIRECTION,    
    LEFT_FILE_DIRECTION,  
};

enum UserLoginStatus
{
    STATUS_LOGINING,
    STATUS_CONNECTING,
    STATUS_CONNECTED,
    STATUS_LOGIN_FINISHED,
    STATUS_ERROR,
    STATUS_GET_USER_LIST,  
};

enum FileTransferStatus
{
    FILE_STATUS_CONNECTING = 6,
    FILE_STATUS_CONNECTED,
    FILE_STATUS_ERROR,
    FILE_STATUS_TRANSFERING,
    FILE_STATUS_SUCCESS,
};

enum ImageTransferStatus
{
    IMAGE_STATUS_CONNECTING = 10,
    IMAGE_STATUS_CONNECTED,
    IMAGE_STATUS_ERROR,
};

enum CONTENT_TYPE
{
    CONTENT_TYPE_UNKNOWN,			    // 未知消息类型
    CONTENT_TYPE_TEXT,				    // 文本类型（包括图文混排类型）
    CONTENT_TYPE_IMAGE_CONFIRM,			// 图片上传成功后的确认消息类型  pc专用 （pc在上传图片成功后 补发的消息 用于去下载  pc和app端都要处理）
    CONTENT_TYPE_FILE,				    // 收到好友发送过来的文件
    CONTENT_TYPE_SHAKE_WINDOW,			// 窗口抖动  pc专用
    CONTENT_TYPE_MOBILE_IMAGE,			// app端发出的图片  （app端发送的图片信息，已经上传好才会发送的这一条  pc接到这个类型可以直接显示）

    CONTENT_TYPE_FONT_INFO,				//pc专用，移动端忽略
    CONTENT_TYPE_FACE,					//pc专用，移动端忽略
    CONTENT_TYPE_CHAT_IMAGE,			//pc专用，移动端忽略

    CONTENT_TYPE_REMOTE_DESKTOP         //远程桌面
};


struct FileTransferProgress
{
    QString         m_strFileName;
    QString         m_strPullFileName;
    QString         m_strFileSize;
    int             m_nPercent;
    QString         m_strFileState;

    //          这里加一个文件类型用图片展示
};

class CFontInfo				// 字体信息
{
public:
    CFontInfo(void) : m_nSize(9), m_clrText(RGB(0, 0, 0)), m_strName(_T("微软雅黑")),
        m_bBold(FALSE), m_bItalic(FALSE), m_bUnderLine(FALSE) {}
    ~CFontInfo(void) {}

public:
    int m_nSize;			// 字体大小
    COLORREF m_clrText;		// 字体颜色
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

class CUserMessageDatas
{
public:
    CUserMessageDatas() = default;
    ~CUserMessageDatas() = default;

    CONTENT_TYPE			        m_nMsgType;
    unsigned int					m_nMsgId;
    unsigned int					m_nMsgId2;
    unsigned int					m_nFromUin;
    unsigned int					m_nToUin;
    unsigned int					m_nReplyIp;
    unsigned __int64			    m_nTime;

    std::vector<std::shared_ptr<CContent>>   m_arrContent;
};
