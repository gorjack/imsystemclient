#include "custommenu.h"
#include "commonutils.h"

#include <QPainter>
#include <QStyleOption>

CustomMenu::CustomMenu(QWidget *parent)
	: QMenu(parent)
{
	setAttribute(Qt::WA_TranslucentBackground);
	CommonUtils::loadStyleSheet(this, "Menu");
}

CustomMenu::~CustomMenu()
{

}

void CustomMenu::addCustomMenu(const QString& qsName, const QString& icon, const QString& zhName)
{
	QAction *pAction = addAction(QIcon(icon), zhName);
	m_menuActionMap.insert(qsName, pAction);
}

QAction* CustomMenu::getAction(const QString& qsName)
{
	return m_menuActionMap[qsName];
}