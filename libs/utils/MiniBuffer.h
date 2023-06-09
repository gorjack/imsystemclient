#pragma once
#include <stdint.h>
#include <stdio.h>


//typedef BOOL bool;
//typedef PSTR char*;
//typedef TRUE true;

//可以在出了作用域自动释放的迷你内存类
class CMiniBuffer
{
public:
    //FIXME: 将int64_t强制转换成int32可能会有问题(大的内存其实分配不出来的!!)
	CMiniBuffer(int64_t nSize, bool bAutoRelease = true);
	~CMiniBuffer();

	void Release();

	int64_t GetSize();
	char* GetBuffer();
	
    //所有需要使用char* 的地方都可以直接使用CMiniBuffer对象
	operator char*(); 
	
	void EnableAutoRelease(bool bAutoRelease);
    bool IsAutoRelease();

private:
    bool	m_bAutoRelease;
    int64_t	m_nSize;
	char*	m_pData;
};