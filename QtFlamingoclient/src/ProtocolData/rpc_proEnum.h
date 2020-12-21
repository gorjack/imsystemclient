#pragma once

#include <stdint.h>

namespace protocol {

    //�ͻ�������
    enum CLIENT_TYPE
    {
        CLIENT_TYPE_UNKNOWN = 0,
        CLIENT_TYPE_PC = 1,
        CLIENT_TYPE_IOS = 2,
        CLIENT_TYPE_ANDROID = 3
    };

    //���Ƿ�ѹ����
    enum
    {
        PACKAGE_UNCOMPRESSED,
        PACKAGE_COMPRESSED
    };

    enum LOGIN_TYPE
    {
        LOGIN_USE_MOBILE_NUMBER = 0,	//ʹ���ֻ��ŵ�¼
        LOGIN_USE_ACCOUNT = 1,	//ʹ���˺ŵ�¼
    };

    enum LOGIN_RESULT_CODE	// ��¼�������
    {
        LOGIN_SUCCESS,				// ��¼�ɹ�
        LOGIN_FAILED,				// ��¼ʧ��
        LOGIN_UNREGISTERED,			// �û�δע��
        LOGIN_PASSWORD_ERROR,		// �������
        LOGIN_USER_CANCEL_LOGIN,	// �û�ȡ����¼
        LOGIN_SERVER_REFUSED,		// �������ܾ�
        LOGIN_SERVER_NOT_RESPONSE	// ������δ��Ӧ
    };

    enum REGISTER_RESULT_CODE	//ע��������
    {
        REGISTER_SUCCESS,				//ע��ɹ�
        REGISTER_EXIST,					//�˺��Ѿ�����
        REGISTER_FAILED,				//ע��ʧ��
        REGISTER_SERVER_NOT_RESPONSE	//������δ��Ӧ
    };

    //����״̬
    enum ONLINE_STATUS
    {
        STATUS_OFFLINE = 0,			//����
        STATUS_ONLINE = 1,			//����
        STATUS_INVISIBLE = 2,			//����
        STATUS_BUSY = 3,			//æµ
        STATUS_AWAY = 4,			//�뿪
        STATUS_MOBILE_ONLINE = 5,			//�ƶ�������
        STATUS_MOBILE_OFFLINE = 6,			//�ƶ�������
        STATUS_BOTH = 7			//�ֻ��͵���ͬʱ����
    };

    enum ADD_FRIEND_RESULT	//��Ӻ��ѽ��
    {
        FIND_FRIEND_NOT_FOUND,
        FIND_FRIEND_FOUND,
        FIND_FRIEND_FAILED,

        ADD_FRIEND_SUCCESS,
        ADD_FRIEND_FAILED
    };

    //�Ӻ���״̬
    enum OPERATE_FRIEND
    {
        Apply,
        Agree,
        Refuse,
        Delete
    };

    enum CONTENT_TYPE
    {
        CONTENT_TYPE_UNKNOWN,			    // δ֪��Ϣ����
        CONTENT_TYPE_TEXT,				    // �ı����ͣ�����ͼ�Ļ������ͣ�
        CONTENT_TYPE_IMAGE_CONFIRM,			// ͼƬ�ϴ��ɹ����ȷ����Ϣ����  pcר�� ��pc���ϴ�ͼƬ�ɹ��� ��������Ϣ ����ȥ����  pc��app�˶�Ҫ����
        CONTENT_TYPE_FILE,				    // �յ����ѷ��͹������ļ�
        CONTENT_TYPE_SHAKE_WINDOW,			// ���ڶ���  pcר��
        CONTENT_TYPE_MOBILE_IMAGE,			// app�˷�����ͼƬ  ��app�˷��͵�ͼƬ��Ϣ���Ѿ��ϴ��òŻᷢ�͵���һ��  pc�ӵ�������Ϳ���ֱ����ʾ��

        CONTENT_TYPE_FONT_INFO,				//pcר�ã��ƶ��˺���
        CONTENT_TYPE_FACE,					//pcר�ã��ƶ��˺���
        CONTENT_TYPE_CHAT_IMAGE,			//pcר�ã��ƶ��˺���

        CONTENT_TYPE_REMOTE_DESKTOP         //Զ������
    };

    //�ļ����ط��ؽ����
    enum FILE_DOWNLOAD_RETCODE
    {
        FILE_DOWNLOAD_FAILED,
        FILE_DOWNLOAD_SUCCESS,
        FILE_DOWNLOAD_USERCANCEL	//�û�ȡ������
    };

    //�ļ��ϴ����ؽ����
    enum FILE_UPLOAD_RETCODE
    {
        FILE_UPLOAD_FAILED,
        FILE_UPLOAD_SUCCESS,
        FILE_UPLOAD_USERCANCEL		//�û�ȡ���ϴ�
    };
}