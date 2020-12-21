#ifndef CCHATMAINWINDOWDIALOG_H
#define CCHATMAINWINDOWDIALOG_H

#include <QtWidgets/QDialog>
#include "CChatMessageWindowWidget.h"
#include "UserDataInfo.h"

class QListWidget;
class QStackedWidget;
class CUserDataWidgetItem;
class QPushButton;
class QListView;
class QLabel;
namespace XP
{
    class CSplitContainer;
}

class CShowRightWidget : public QWidget
{
public:
    CShowRightWidget(QWidget*parent = NULL);

protected:
    void resizeEvent(QResizeEvent *event);
    void createUi();

    QLabel           *m_pTitleWidget = NULL;
    QListView        *m_pContent = NULL;
};


class PANELCHATWINDOW_EXPORT CChatMainWindowDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CChatMainWindowDialog(QWidget *parent = nullptr);

    void addBuddyChatWindow(const UC::CUserDataInfo& user);

protected Q_SLOTS:
    void slotClose();
    void slotShowCurrentWindow(QListWidgetItem* nIndex);

protected:
    void paintEvent(QPaintEvent *event);
private:

    void createUi();
    QListWidget                             *m_pUserDataList = NULL;
    QStackedWidget                          *m_pStackWidget = NULL;
    XP::CSplitContainer                     *m_pSplit = NULL;
    QMap<QListWidgetItem*, CChatMessageWindowWidget*>     m_mapIndex2BuddyWindow;
    QSet<int>                                m_setId;      //用于判断是否重复点了item
    CShowRightWidget                        *m_pRightWidget = NULL;
};

#endif 