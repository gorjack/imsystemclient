/**
 *  ui资源管理类
 *
 */

#include "CUiResource.h"
#include "CImageCenter.h"
#include <utils/CSingletonT.hpp>
#include <utils/commonFunc.h>

IMPL_SINGLETON_CLASS(CUiResource);

CUiResource::CUiResource()
{
	m_pImageCenter = new CImageCenter();
}

CUiResource::~CUiResource()
{
	utils::safeDeletePtr(m_pImageCenter);
}

void CUiResource::parseImage(QString qsDir)
{
	if (NULL != m_pImageCenter)
	{
		m_pImageCenter->parse(qsDir);
	}
}

void CUiResource::reParseImage(QString qsDir, QString qsKey)
{
	if (NULL != m_pImageCenter)
	{
		m_pImageCenter->reParseImage(qsDir, qsKey);
	}
}

QPixmap* CUiResource::getPixmap(QString qsKey) const
{
	return (NULL != m_pImageCenter) ? m_pImageCenter->getPixmap(qsKey) : NULL;
}

const QIcon* CUiResource::getIcon(QString qsKey) const
{
	return (NULL != m_pImageCenter) ? m_pImageCenter->getIcon(qsKey) : NULL;
}