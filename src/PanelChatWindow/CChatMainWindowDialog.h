#ifndef CCHATMAINWINDOWDIALOG_H
#define CCHATMAINWINDOWDIALOG_H

#include <QtWidgets/QDialog>
#include "CChatMessageWindowWidget.h"
#include "UserDataInfo.h"
#include <ProtocolData/rpc_structs.h>
#include <utils/CSingletonT.h>

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

class PANELCHATWINDOW_EXPORT CChatMainWindowDialog : public QDialog, public utils::CSingletonT<CChatMainWindowDialog>
{
    Q_OBJECT
public:
    explicit CChatMainWindowDialog(QWidget *parent = nullptr);

    void addBuddyChatWindow(const UC::CUserDataInfoPtr& user);

public Q_SLOTS:
    void slotClose();
    void slotShowCurrentWindow(QListWidgetItem* nIndex);
    void handleAllTypeMessage(const net::CBuddyMessagePtr& pData);

protected:
    void paintEvent(QPaintEvent *event);
private:

    void createUi();
    QListWidget                             *m_pUserDataList = NULL;
    QMap<QListWidgetItem*, CChatMessageWindowWidget*>     m_mapIndex2BuddyWindow;
    QMap<int, CChatMessageWindowWidget*>                  m_mapId2BuddyWindow;

    QStackedWidget                          *m_pStackWidget = NULL;
    XP::CSplitContainer                     *m_pSplit = NULL;
    QSet<int>                                m_setId;      //用于判断是否重复点了item
};

#endif 