#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <PanelChatWindow/UserDataInfo.h>

struct InfoMessageIData
{
    QString strImage;
    QString strName;
    QString strMessage;
};

class PANELBASEWIDGET_EXPORT CUserInfoMessageIDataWidget : public QWidget
{
public:
    CUserInfoMessageIDataWidget(QWidget *parent = NULL);
    ~CUserInfoMessageIDataWidget();

    void setUiByData(const UC::CUserDataInfoPtr& data);
    
    void createUi();

    QLabel              *m_pUserHeadImag;
    QLabel              *m_pUserName;
    QLabel              *m_pUserMessage;
    UC::CUserDataInfoPtr   m_pData;
};

class PANELBASEWIDGET_EXPORT QCustomFloatWidget : public QWidget
{
    Q_OBJECT

public:
    QCustomFloatWidget(QWidget *parent = Q_NULLPTR);


    void addData(const UC::CUserDataInfoPtr& data);
    void addDatas(const std::vector<InfoMessageIData>& data);

Q_SIGNALS:
    void sigAddChatUser(const UC::CUserDataInfoPtr&);

protected Q_SLOTS:
    void slotItemDoubleClicked(QListWidgetItem* pItem);
protected:
    void resizeEvent(QResizeEvent *event);

private:
    void createUi();


    QListWidget             *m_pMsgInfoList;
};
