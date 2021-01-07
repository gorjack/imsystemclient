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

struct FileTransferProgress
{
    QString         m_strFileName;
    QString         m_strPullFileName;
    QString         m_strFileSize;
    int             m_nPercent;
    QString         m_strFileState;

    //          这里加一个文件类型用图片展示
};
