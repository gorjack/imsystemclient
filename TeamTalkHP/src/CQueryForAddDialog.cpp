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
		QMessageBox::information(this, "��ʾ", "�ͻ��˻�û���Ϸ�����");
	}
}

void CQueryForAddDialog::slotOnFindFirendCallBack()
{
	net::CFindFriendResultPtr pDataPtr = std::make_shared<net::CFindFriendResult>();
	pDataPtr->decodePackage(m_strBuffer);

	long nResultCode = pDataPtr->m_nResultCode;

	if (nResultCode == protocol::FIND_FRIEND_NOT_FOUND)
		QMessageBox::information(this, "��ʾ", "�����ҵ��˻������ڣ�");
	else if (nResultCode == protocol::FIND_FRIEND_FAILED)
		QMessageBox::information(this, "��ʾ", "������ϣ������˻�ʧ�ܣ�");
	else if (nResultCode == protocol::FIND_FRIEND_FOUND)
	{
		QMessageBox::information(this, "��ʾ", "���������ѷ�����ȴ�");
		addFirend(pDataPtr->m_uAccountID);
	}
}

void CQueryForAddDialog::slotOnAddFirendCB()
{
	net::COperateFriendResultPtr pAddFriendInfo = std::make_shared<net::COperateFriendResult>();
	pAddFriendInfo->decodePackage(m_strBuffer);

	//���˼��Լ�
	if (pAddFriendInfo->m_uCmd == protocol::Apply)
	{
		m_pConfirmAddFriendDG->setWindowTitle(QString::fromLocal8Bit("�Ӻ���"));
		QString msg = QString(" %1 �������Ϊ����,  �Ƿ�ͬ��").arg(pAddFriendInfo->m_szAccountName);

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
		QString msg = QString(" %1 �ܾ��˼Ӻ�������").arg(pAddFriendInfo->m_szAccountName);
		m_pConfirmAddFriendDG->setWindowTitle(QString::fromLocal8Bit("�ܾ���������"));
		m_pConfirmAddFriendDG->setInfoMsg(msg);
		m_pConfirmAddFriendDG->exec();
	}
	else if (pAddFriendInfo->m_uCmd == protocol::Agree)
	{
		QString msg = QString(" ���� %1 �Ѿ��Ǻ���������ʼ�����").arg(pAddFriendInfo->m_szAccountName);
		m_pConfirmAddFriendDG->setWindowTitle(QString::fromLocal8Bit("�ɹ��Ӻ���"));
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
