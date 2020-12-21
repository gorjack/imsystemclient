
#include "MiniBuffer.h"
#include "string.h"
//#include "Utils.h"



#define DEL(p) \
	if(p != NULL) \
	{			  \
		delete p; \
		p = NULL; \
	}

#define DEL_ARR(p) \
	if(p != NULL) \
	{			  \
		delete[] p; \
		p = NULL; \
	}

CMiniBuffer::CMiniBuffer(int64_t nSize, bool bAutoRelease)
{
	//assert(nSize > 0);
	
	m_nSize = nSize;
	m_bAutoRelease = bAutoRelease;

	m_pData = new char[(int)nSize];
	memset(m_pData, 0, (size_t)nSize);
}

CMiniBuffer::~CMiniBuffer()
{
	if(m_bAutoRelease)
		DEL_ARR(m_pData);
}

void CMiniBuffer::Release()
{
	DEL_ARR(m_pData);
	m_nSize = 0;
}

int64_t CMiniBuffer::GetSize()
{
	return m_nSize;
}

char* CMiniBuffer::GetBuffer()
{
	return m_pData;
}

CMiniBuffer::operator char*()
{
	return m_pData;
}
	
void CMiniBuffer::EnableAutoRelease(bool bAutoRelease)
{
	m_bAutoRelease = bAutoRelease;
}

bool CMiniBuffer::IsAutoRelease()
{
	return m_bAutoRelease;
}