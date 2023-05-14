#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H

#include <QMenu>
#include <QMap>

class CustomMenu : public QMenu
{
	Q_OBJECT

public:
	CustomMenu(QWidget *parent = 0);
	~CustomMenu();

private:
	

public:
	void addCustomMenu(const QString& text, const QString& icon, const QString& zhName);
	QAction* getAction(const QString& qsName);

private:
	QMap<QString, QAction*> m_menuActionMap;
};

#endif // CUSTOMMENU_H
