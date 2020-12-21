#ifndef __CUSER_NAMAGER__
#define __CUSER_NAMAGER__
#include <utils/CSingletonT.h>
#include <string>
#include <QObject>
#include "CUserBusinessCenter.h"
#include <ProtocolData/rpc_structs.h>


class USER_EXPORT CUserManager : public QObject, public utils::CSingletonT<CUserManager>
{
    Q_OBJECT
public:
    CUserManager();
    ~CUserManager();

    const PC::CBuddyList& getFirendList();
    void queryFirendList();
    void onGetFirendListCallBack(const std::string & data);

Q_SIGNALS:
    void sigFinishGetFriendListReq();

private:
    void ClearUserInfo();

    PC::CBuddyInfo		m_UserInfo;
    PC::CBuddyList		m_BuddyList;

};
#endif