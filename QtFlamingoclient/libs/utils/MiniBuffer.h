#pragma once
#include <stdint.h>
#include <stdio.h>


//typedef BOOL bool;
//typedef PSTR char*;
//typedef TRUE true;

//�����ڳ����������Զ��ͷŵ������ڴ���
class CMiniBuffer
{
public:
    //FIXME: ��int64_tǿ��ת����int32���ܻ�������(����ڴ���ʵ���䲻������!!)
	CMiniBuffer(int64_t nSize, bool bAutoRelease = true);
	~CMiniBuffer();

	void Release();

	int64_t GetSize();
	char* GetBuffer();
	
    //������Ҫʹ��char* �ĵط�������ֱ��ʹ��CMiniBuffer����
	operator char*(); 
	
	void EnableAutoRelease(bool bAutoRelease);
    bool IsAutoRelease();

private:
    bool	m_bAutoRelease;
    int64_t	m_nSize;
	char*	m_pData;
};