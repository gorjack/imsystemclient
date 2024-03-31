/**
 *  ui资源管理类
 */

#ifndef XP_UIRESOURCE_CUIRESOURCE_H
#define XP_UIRESOURCE_CUIRESOURCE_H

#include <utils/CSingletonT.h>
#include <QIcon>
#include <QPixmap>


class CImageCenter;
class CUiResource : public utils::CSingletonT<CUiResource>
{
public:
	CUiResource();
	virtual ~CUiResource();


	void parseImage(QString qsDir);
	void reParseImage(QString qsDir, QString qsKey);

	QPixmap* getPixmap(QString qsKey) const;
	const QIcon* getIcon(QString qsKey) const;


	QString getImageSheet(QString qsKey) const;
protected:
	CImageCenter* m_pImageCenter;
};


#define TT_PIXMAP(arg)  CUiResource::instance()->getPixmap(arg)
#define TT_ICON(arg)    CUiResource::instance()->getIcon(arg)
#endif
