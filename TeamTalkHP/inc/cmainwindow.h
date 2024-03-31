#ifndef CCMAINWINDOW_H
#define CCMAINWINDOW_H

#include "BasicWindow.h"
#include "ui_cmainwindow.h"
#include "UserClientCenter/CUserBusinessCenter.h"

class QTreeWidgetItem;
class CMainWindow : public BasicWindow
{
	Q_OBJECT

public:
    CMainWindow(QString userName, QWidget *parent = nullptr);
	~CMainWindow();

public:
	//���õȼ�
	void setLevelPixmap(int level);
	//����ͷ��
	void setHeadPixmap();
	//�����û�����
	void setUserName(const QString& username);
	//����״̬�����˵�ͼ��
	void setStatusMenuIcon();
	//�������APPӦ��
	QWidget* addOtherAppExtension(const QString& apppath, const QString& appName);
	//��ʼ�������б�
	void initContactTree();

	void onOperateFriends(const std::string& req);

Q_SIGNALS:
	void sigOnAddFirendCB(const std::string&);

private slots:
	void onItemExpanded(QTreeWidgetItem * item);
	void onItemCollapsed(QTreeWidgetItem * item);
	void onItemClicked(QTreeWidgetItem * item, int column);
	void onItemDoubleClicked(QTreeWidgetItem *, int);
	void onAppIconCliked();

	void slotOnAddFirendCB(const std::string&);
	void slotOnAddFirendBtnClicked(bool);

private:
	void initControl();
	void initStrangerTree();
	void addMyFriendInfo(QTreeWidgetItem* pRootGroupItem, PC::CBuddyInfo*);
	void addStarngerInfo(QTreeWidgetItem* pRootGroupItem);
	void updateSeachStyle();

private:
	void resizeEvent(QResizeEvent *event) override;
	bool eventFilter(QObject *watched, QEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

private:
	Ui::CMainWindowClass ui;

	QString m_strUserName;
};

#endif // CCMAINWINDOW_H
