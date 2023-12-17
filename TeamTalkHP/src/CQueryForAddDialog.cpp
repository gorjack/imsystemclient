#include "CQueryForAddDialog.h"
#include "CConfirmAddFriendDG.h"
#include "UserClientCenter/CUserClientCenter.h"
#include <ProtocolData/rpc_structs.h>
#include <ProtocolData/rpc_proEnum.h>
#include <QtWidgets/QMessageBox>
#include <boost/make_shared.hpp>

CQueryForAddDialog::CQueryForAddDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.m_pAddFirendBtn, SIGNAL(clicked()), this, SLOT(slotFindFriend()));
	connect(this, SIGNAL(sigOnFindFirendCallBack()), this, SLOT(slotOnFindFirendCallBack()));

	connect(this, SIGNAL(sigOnAddFirendCB()), this, SLOT(slotOnAddFirendCB()));
	m_pConfirmAddFriendDG = new CConfirmAddFriendDG(this);
	CUserClientCenter::instance()->registCallBack(protocol::msg_type_finduser, std::bind(&CQueryForAddDialog::onHandleFindFirend, this, std::placeholders::_1));
	CUserClientCenter::instance()->registCallBack(protocol::msg_type_operatefriend, std::bind(&CQueryForAddDialog::onAddFirend, this, std::placeholders::_1));
}


void CQueryForAddDialog::addFirend(unsigned int uAccountToAdd)
{
	net::COperateFriendRequestPtr pData(new net::COperateFriendRequest());
	if (NULL != pData)
	{
		pData->m_uCmd = protocol::Apply;
		pData->m_uAccountID = uAccountToAdd;
	}

	bool nRet = CUserClientCenter::instance()->request_async(pData, std::bind(&CQueryForAddDialog::onAddFirend, this, std::placeholders::_1));

}

void CQueryForAddDialog::slotFindFriend()
{
	net::CFindFriendRequestPtr pRequestPtr = std::make_shared<net::CFindFriendRequest>();


	QString strId = ui.m_pIdLineEdit->displayText();
	std::string strTemp(strId.toLatin1());
	strcpy_s(pRequestPtr->m_szAccountName, sizeof(pRequestPtr->m_szAccountName) / sizeof(char), strTemp.data());
	pRequestPtr->m_nType = 1;

	bool nRet = CUserClientCenter::instance()->request_async(pRequestPtr, std::bind(&CQueryForAddDialog::onHandleFindFirend, this, std::placeholders::_1));
	if (!nRet)
	{
		QMessageBox::information(this, "提示", "客户端还没连上服务器");
	}
}

void CQueryForAddDialog::slotOnFindFirendCallBack()
{
	net::CFindFriendResultPtr pDataPtr = std::make_shared<net::CFindFriendResult>();
	pDataPtr->decodePackage(m_strBuffer);

	long nResultCode = pDataPtr->m_nResultCode;

	if (nResultCode == protocol::FIND_FRIEND_NOT_FOUND)
		QMessageBox::information(this, "提示", "您查找的账户不存在！");
	else if (nResultCode == protocol::FIND_FRIEND_FAILED)
		QMessageBox::information(this, "提示", "网络故障，查找账户失败！");
	else if (nResultCode == protocol::FIND_FRIEND_FOUND)
	{
		QMessageBox::information(this, "提示", "您的请求已发送请等待");
		addFirend(pDataPtr->m_uAccountID);
	}
}

void CQueryForAddDialog::slotOnAddFirendCB()
{
	net::COperateFriendResultPtr pAddFriendInfo = std::make_shared<net::COperateFriendResult>();
	pAddFriendInfo->decodePackage(m_strBuffer);

	//别人加自己
	if (pAddFriendInfo->m_uCmd == protocol::Apply)
	{
		m_pConfirmAddFriendDG->setWindowTitle(QString::fromLocal8Bit("加好友"));
		QString msg = QString(" %1 请求加您为好友,  是否同意").arg(pAddFriendInfo->m_szAccountName);

		m_pConfirmAddFriendDG->setInfoMsg(msg);
		int nRet = m_pConfirmAddFriendDG->exec();
		{
			net::COperateFriendRequestPtr pData = std::make_shared<net::COperateFriendRequest>();
			pData->m_uCmd = (nRet == QDialog::Accepted) ? protocol::Agree : protocol::Refuse;
			pData->m_uAccountID = pAddFriendInfo->m_uAccountID;

			CUserClientCenter::instance()->request_async(pData, std::bind(&CQueryForAddDialog::onAddFirend, this, std::placeholders::_1));
		}
	}
	else if (pAddFriendInfo->m_uCmd == protocol::Refuse)
	{
		QString msg = QString(" %1 拒绝了加好友请求").arg(pAddFriendInfo->m_szAccountName);
		m_pConfirmAddFriendDG->setWindowTitle(QString::fromLocal8Bit("拒绝好友请求"));
		m_pConfirmAddFriendDG->setInfoMsg(msg);
		m_pConfirmAddFriendDG->exec();
	}
	else if (pAddFriendInfo->m_uCmd == protocol::Agree)
	{
		QString msg = QString(" 您和 %1 已经是好友啦，开始聊天吧").arg(pAddFriendInfo->m_szAccountName);
		m_pConfirmAddFriendDG->setWindowTitle(QString::fromLocal8Bit("成功加好友"));
		m_pConfirmAddFriendDG->setInfoMsg(msg);
		m_pConfirmAddFriendDG->exec();
	}
}

void CQueryForAddDialog::onHandleFindFirend(const std::string& strMsg)
{
	m_strBuffer = strMsg;
	emit sigOnFindFirendCallBack();
}

void CQueryForAddDialog::onAddFirend(const std::string& strMsg)
{
	m_strBuffer = strMsg;
	emit sigOnAddFirendCB();
}
