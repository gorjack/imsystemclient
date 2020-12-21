#pragma once

#include <stdint.h>

namespace protocol {

    //客户端类型
    enum CLIENT_TYPE
    {
        CLIENT_TYPE_UNKNOWN = 0,
        CLIENT_TYPE_PC = 1,
        CLIENT_TYPE_IOS = 2,
        CLIENT_TYPE_ANDROID = 3
    };

    //包是否压缩过
    enum
    {
        PACKAGE_UNCOMPRESSED,
        PACKAGE_COMPRESSED
    };

    enum LOGIN_TYPE
    {
        LOGIN_USE_MOBILE_NUMBER = 0,	//使用手机号登录
        LOGIN_USE_ACCOUNT = 1,	//使用账号登录
    };

    enum LOGIN_RESULT_CODE	// 登录结果代码
    {
        LOGIN_SUCCESS,				// 登录成功
        LOGIN_FAILED,				// 登录失败
        LOGIN_UNREGISTERED,			// 用户未注册
        LOGIN_PASSWORD_ERROR,		// 密码错误
        LOGIN_USER_CANCEL_LOGIN,	// 用户取消登录
        LOGIN_SERVER_REFUSED,		// 服务器拒绝
        LOGIN_SERVER_NOT_RESPONSE	// 服务器未响应
    };

    enum REGISTER_RESULT_CODE	//注册结果代码
    {
        REGISTER_SUCCESS,				//注册成功
        REGISTER_EXIST,					//账号已经存在
        REGISTER_FAILED,				//注册失败
        REGISTER_SERVER_NOT_RESPONSE	//服务器未响应
    };

    //在线状态
    enum ONLINE_STATUS
    {
        STATUS_OFFLINE = 0,			//离线
        STATUS_ONLINE = 1,			//在线
        STATUS_INVISIBLE = 2,			//隐身
        STATUS_BUSY = 3,			//忙碌
        STATUS_AWAY = 4,			//离开
        STATUS_MOBILE_ONLINE = 5,			//移动版在线
        STATUS_MOBILE_OFFLINE = 6,			//移动版下线
        STATUS_BOTH = 7			//手机和电脑同时在线
    };

    enum ADD_FRIEND_RESULT	//添加好友结果
    {
        FIND_FRIEND_NOT_FOUND,
        FIND_FRIEND_FOUND,
        FIND_FRIEND_FAILED,

        ADD_FRIEND_SUCCESS,
        ADD_FRIEND_FAILED
    };

    //加好友状态
    enum OPERATE_FRIEND
    {
        Apply,
        Agree,
        Refuse,
        Delete
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

    //文件下载返回结果码
    enum FILE_DOWNLOAD_RETCODE
    {
        FILE_DOWNLOAD_FAILED,
        FILE_DOWNLOAD_SUCCESS,
        FILE_DOWNLOAD_USERCANCEL	//用户取消下载
    };

    //文件上传返回结果码
    enum FILE_UPLOAD_RETCODE
    {
        FILE_UPLOAD_FAILED,
        FILE_UPLOAD_SUCCESS,
        FILE_UPLOAD_USERCANCEL		//用户取消上传
    };
}