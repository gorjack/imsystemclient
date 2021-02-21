#include "QCustomFloatWidget.h"
#include <QtWidgets/QHBoxLayout>


CUserInfoMessageIDataWidget::CUserInfoMessageIDataWidget(QWidget *parent /*= NULL*/)
    :QWidget(parent)
{
    createUi();
    setFixedHeight(64);
}

CUserInfoMessageIDataWidget::~CUserInfoMessageIDataWidget()
{

}

void CUserInfoMessageIDataWidget::setUiByData(const UC::CUserDataInfoPtr& data)
{
    m_pData = data;
    //m_pUserHeadImag->setPixmap();
    m_pUserName->setText(QString::fromStdString(data->m_strName));
    if (NULL != data->m_pMessageData)
    {
        m_pUserMessage->setText(QString::number(data->m_pMessageData->msgCount()));
    }
}

void CUserInfoMessageIDataWidget::createUi()
{
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    {
        m_pUserHeadImag = new QLabel(this);
        m_pUserHeadImag->setFixedSize(40, 40);
        m_pUserHeadImag->setStyleSheet("border-radius: 20px;  border:1px solid black;background:red");

        m_pUserName = new QLabel(this);
        m_pUserMessage = new QLabel(this);
        m_pUserMessage->setFixedSize(20, 20);
        m_pUserMessage->setStyleSheet("border-radius: 10px;  border:1px solid black;background:red; color:white");


        pLayout->addWidget(m_pUserHeadImag, 0, Qt::AlignVCenter);
        pLayout->addWidget(m_pUserName, 0, Qt::AlignTop);
        pLayout->addStretch(1);
        pLayout->addWidget(m_pUserMessage, 0, Qt::AlignTop);
    }
    setLayout(pLayout);
}


QCustomFloatWidget::QCustomFloatWidget(QWidget *parent)
    : QWidget(parent)
{
    createUi();

    connect(m_pMsgInfoList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotItemDoubleClicked(QListWidgetItem*)));
    setFixedWidth(300);
}

void QCustomFloatWidget::addData(const UC::CUserDataInfoPtr& data)
{
    CUserInfoMessageIDataWidget *pWidget = new CUserInfoMessageIDataWidget(this);
    pWidget->setUiByData(data);
    QListWidgetItem *pItem = new QListWidgetItem(m_pMsgInfoList);
    pItem->setSizeHint(pWidget->size());
    m_pMsgInfoList->setItemWidget(pItem, pWidget);

    int nCount = m_pMsgInfoList->count();
    m_pMsgInfoList->setFixedHeight(nCount * 64);

    setFixedHeight(nCount * 64);
}

void QCustomFloatWidget::addDatas(const std::vector<InfoMessageIData>& data)
{

}

void QCustomFloatWidget::slotItemDoubleClicked(QListWidgetItem* pItem)
{
    CUserInfoMessageIDataWidget *pWidget = dynamic_cast<CUserInfoMessageIDataWidget *>(m_pMsgInfoList->itemWidget(pItem));
    if (NULL != pWidget)
    {
        emit sigAddChatUser(pWidget->m_pData);
    }
    pWidget->deleteLater();
    int nRow = m_pMsgInfoList->row(pItem);
    m_pMsgInfoList->takeItem(nRow);

    int nCount = m_pMsgInfoList->count();
    m_pMsgInfoList->setFixedHeight(nCount * 64);

    setFixedHeight(nCount * 64);
}

void QCustomFloatWidget::resizeEvent(QResizeEvent *event)
{
    int nCount = m_pMsgInfoList->count();
    m_pMsgInfoList->setFixedHeight(nCount * 64);

    setFixedHeight(nCount * 64);
    QWidget::resizeEvent(event);
}

void QCustomFloatWidget::createUi()
{
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    {
        pLayout->setContentsMargins(0, 0, 0, 0);
        pLayout->setMargin(0);
        m_pMsgInfoList = new QListWidget(this);
        m_pMsgInfoList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pLayout->addWidget(m_pMsgInfoList);
    }
    setLayout(pLayout);
}

