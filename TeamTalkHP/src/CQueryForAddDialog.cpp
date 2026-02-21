#include "CQueryForAddDialog.h"
#include "CConfirmAddFriendDG.h"
#include "UserClientCenter/CUserClientCenter.h"
#include <ProtocolData/rpc_structs.h>
#include <ProtocolData/rpc_proEnum.h>
#include <QtWidgets/QMessageBox>

CQueryForAddDialog::CQueryForAddDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.m_pAddFirendBtn, SIGNAL(clicked()), this, SLOT(slotFindFriend()));
	connect(this, SIGNAL(sigOnFindFirendCallBack()), this, SLOT(slotOnFindFirendCallBack()));

	connect(this, SIGNAL(sigOnAddFirendCB()), this, SLOT(slotOnAddFirendCB()));
	m_pConfirmAddFriendDG = new CConfirmAddFriendDG(this);
	CUserClientCenter::instance()->registCallBack(protocol::msg_type_finduser, std::bind(&CQueryForAddDialog::onHandleFindFirend, this, std::placeholders::_1));
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
		QMessageBox::information(this, QObject::tr("Hint"), QObject::tr("The client has not connected to the server yet"));
	}
}

void CQueryForAddDialog::slotOnFindFirendCallBack()
{
	net::CFindFriendResultPtr pDataPtr = std::make_shared<net::CFindFriendResult>();
	pDataPtr->decodePackage(m_strBuffer);

	long nResultCode = pDataPtr->m_nResultCode;

	if (nResultCode == protocol::FIND_FRIEND_NOT_FOUND)
		QMessageBox::information(this, QObject::tr("Hint"), QObject::tr("The account you are looking for does not exist!"));
	else if (nResultCode == protocol::FIND_FRIEND_FAILED)
		QMessageBox::information(this, QObject::tr("Hint"), QObject::tr("Network failure, account search failed!"));
	else if (nResultCode == protocol::FIND_FRIEND_FOUND)
	{
		//QMessageBox::information(this, QObject::tr("Hint"), QObject::tr("Your request has been sent please wait"));
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
		m_pConfirmAddFriendDG->setWindowTitle(QObject::tr("Add friend"));
		QString msg = QString(QObject::tr("%1 requests to add you as a friend, do you agree?")).arg(pAddFriendInfo->m_szAccountName);

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
		QString msg = QString(QObject::tr("%1 declined the friend request")).arg(pAddFriendInfo->m_szAccountName);
		m_pConfirmAddFriendDG->setWindowTitle(QObject::tr("Decline friend request"));
		m_pConfirmAddFriendDG->setInfoMsg(msg);
		m_pConfirmAddFriendDG->exec();
	}
	else if (pAddFriendInfo->m_uCmd == protocol::Agree)
	{
		QString msg = QString(QObject::tr("You and %1 are already friends, let's start chatting")).arg(pAddFriendInfo->m_szAccountName);
		m_pConfirmAddFriendDG->setWindowTitle(QObject::tr("Added friend successfully"));
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
