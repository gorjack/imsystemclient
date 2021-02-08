#include "rpc_structs.h"
#include <protocolstream.h>
#include <Msg.h>
#include <utils/ZlibUtil.h>
#include <jsoncpp/reader.h>
#include <IULog.h>
#include <boost/format.hpp>
#include <utils/EncodeUtil.h>
#include <winlog/IULog.h>
#include <utils/strings.h>
#include <sstream>

namespace net
{
    CRegisterRequest::CRegisterRequest(const char* strAcc, const char* nickName, const char* passWd)
    {
        memcpy(m_szAccountName, strAcc, strlen(strAcc) + 1);
        memcpy(m_szNickName, nickName, strlen(nickName) + 1);
        memcpy(m_szPassword, passWd, strlen(passWd) + 1);
    }

    CRegisterRequest::~CRegisterRequest()
    {

    }

    void CRegisterRequest::encodePackage(std::string& str) const
    {
        char szRegisterInfo[256] = { 0 };
        sprintf_s(szRegisterInfo,
            256,
            "{\"username\": \"%s\", \"nickname\": \"%s\", \"password\": \"%s\"}",
            m_szAccountName,
            m_szNickName,
            m_szPassword);

        std::string outbuf;
        net::BinaryStreamWriter writeStream(&outbuf);
        writeStream.WriteInt32(protocol::msg_type_register);
        writeStream.WriteInt32(0);
        std::string data = szRegisterInfo;
        writeStream.WriteString(data);
        writeStream.Flush();

        std::string strDestBuf;
        if (!ZlibUtil::CompressBuf(outbuf, strDestBuf))
        {
            LOG_ERROR("compress error");
            return;
        }
        protocol::msg header;
        header.compressflag = 1;
        header.originsize = outbuf.length();
        header.compresssize = strDestBuf.length();

        str.append((const char*)&header, sizeof(header));
        str.append(strDestBuf);

        return;
    }

    void CRegisterResult::decodePackage(const std::string& data)
    {
        //{"code": 0, "msg": "ok"}
        Json::Reader JsonReader;
        Json::Value JsonRoot;
        if (JsonReader.parse(data, JsonRoot))
        {
            if (!JsonRoot["code"].isNull() && JsonRoot["code"].isInt())
            {
                int nRetCode = JsonRoot["code"].asInt();
                if (nRetCode == 0)
                    m_nResultCode = protocol::REGISTER_SUCCESS;
                else if (nRetCode == 101)
                    m_nResultCode = protocol::REGISTER_EXIST;
            }
        }
    }

    CLoginRequest::CLoginRequest()
    {
        memset(m_szAccountName, 0, sizeof(m_szAccountName));
        memset(m_szPassword, 0, sizeof(m_szPassword));
        m_nStatus = STATUS_ONLINE;
        m_nLoginType = LOGIN_USE_MOBILE_NUMBER;
    }

    CLoginRequest::CLoginRequest(const char* accStr, const char* passwd, int type, int status)
    {
        memcpy(m_szAccountName, accStr, strlen(accStr) + 1);
        memcpy(m_szPassword, passwd, strlen(passwd) + 1);
        m_nLoginType = type;
        m_nStatus = status;
    }

    CLoginRequest::~CLoginRequest()
    {

    }

    void CLoginRequest::encodePackage(std::string& str) const
    {
        char szLoginInfo[256] = { 0 };
        sprintf_s(szLoginInfo,
            ARRAYSIZE(szLoginInfo),
            "{\"username\": \"%s\", \"password\": \"%s\", \"clienttype\": %d, \"status\": %d}",
            m_szAccountName,
            m_szPassword,
            m_nLoginType,
            m_nStatus);

        std::string outbuf;
        net::BinaryStreamWriter writeStream(&outbuf);
        writeStream.WriteInt32(protocol::msg_type_login);
        writeStream.WriteInt32(0);
        writeStream.WriteCString(szLoginInfo, strlen(szLoginInfo));
        writeStream.Flush();

        LOG_INFO("Request logon: Account=%s, Password=*****, Status=%d, LoginType=%d.", m_szAccountName, m_szPassword, m_nStatus, m_nLoginType);

        std::string strDestBuf;
        if (!ZlibUtil::CompressBuf(outbuf, strDestBuf))
        {
            LOG_ERROR("compress error");
            return;
        }
        protocol::msg header;
        memset(&header, 0, sizeof(header));
        header.compressflag = 1;
        header.originsize = outbuf.length();
        header.compresssize = strDestBuf.length();

        str.append((const char*)&header, sizeof(header));
        str.append(strDestBuf);
        return;
    }


    void CLoginResult::decodePackage(const std::string& strReturnData)
    {
        m_LoginResultCode = LOGIN_FAILED;
        {
            //{"code": 0, "msg" : "ok", "userid" : 8}
            Json::Reader JsonReader;
            Json::Value JsonRoot;
            if (JsonReader.parse(strReturnData, JsonRoot) && !JsonRoot["code"].isNull() && JsonRoot["code"].isInt())
            {
                int nRetCode = JsonRoot["code"].asInt();

                if (nRetCode == 0)
                {
                    if (!JsonRoot["userid"].isInt() || !JsonRoot["username"].isString() || !JsonRoot["nickname"].isString() ||
                        !JsonRoot["facetype"].isInt() || !JsonRoot["gender"].isInt() || !JsonRoot["birthday"].isInt() ||
                        !JsonRoot["signature"].isString() || !JsonRoot["address"].isString() ||
                        !JsonRoot["customface"].isString() || !JsonRoot["phonenumber"].isString() ||
                        !JsonRoot["mail"].isString())
                    {
                        LOG_ERROR(("login failed, login response json is invalid, json=%s"), strReturnData.c_str());
                        m_LoginResultCode = LOGIN_FAILED;
                    }
                    else
                    {
                        m_LoginResultCode = LOGIN_SUCCESS;
                        m_uAccountID = JsonRoot["userid"].asInt();
                        strcpy_s(m_szAccountName, ARRAYSIZE(m_szAccountName), JsonRoot["username"].asCString());
                        strcpy_s(m_szNickName, ARRAYSIZE(m_szNickName), JsonRoot["nickname"].asCString());
                        m_nStatus = JsonRoot["status"].asInt();
                        m_nFace = JsonRoot["facetype"].asInt();
                        m_nGender = JsonRoot["gender"].asInt();
                        m_nBirthday = JsonRoot["birthday"].asInt();
                        strcpy_s(m_szSignature, ARRAYSIZE(m_szSignature), JsonRoot["signature"].asCString());
                        strcpy_s(m_szAddress, ARRAYSIZE(m_szAddress), JsonRoot["address"].asCString());
                        strcpy_s(m_szCustomFace, ARRAYSIZE(m_szCustomFace), JsonRoot["customface"].asCString());
                        strcpy_s(m_szPhoneNumber, ARRAYSIZE(m_szPhoneNumber), JsonRoot["phonenumber"].asCString());
                        strcpy_s(m_szMail, ARRAYSIZE(m_szMail), JsonRoot["mail"].asCString());
                    }
                }
                else if (nRetCode == 102)
                    m_LoginResultCode = LOGIN_UNREGISTERED;
                else if (nRetCode == 103)
                    m_LoginResultCode = LOGIN_PASSWORD_ERROR;
                else
                    m_LoginResultCode = LOGIN_FAILED;
            }
        }
    }

    //class CFindFriendRequest
    CFindFriendRequest::CFindFriendRequest()
    {
        memset(m_szAccountName, 0, sizeof(m_szAccountName));
        m_nType = 0;
    }

    CFindFriendRequest::~CFindFriendRequest()
    {

    }

    void CFindFriendRequest::encodePackage(std::string& str, int32_t nSeq) const
    {
        //std::string strTemp;
        char szData[64] = { 0 };
        sprintf_s(szData, 64, "{\"type\": %d, \"username\": \"%s\"}", m_nType, m_szAccountName);

        //std::string outbuf;
        net::BinaryStreamWriter writeStream(&str);
        writeStream.WriteInt32(protocol::msg_type_finduser);
        writeStream.WriteInt32(nSeq);
        writeStream.WriteCString(szData, strlen(szData));
        writeStream.Flush();

        appendPackageHeader(str);
        LOG_INFO("Request to find friend, type=%d, accountName=%s", m_nType, m_szAccountName);

    }

    CFindFriendResult::CFindFriendResult()
    {
        m_nResultCode = FIND_FRIEND_FAILED;
        m_uAccountID = 0;
        memset(m_szAccountName, 0, sizeof(m_szAccountName));
        memset(m_szNickName, 0, sizeof(m_szNickName));
    }

    CFindFriendResult::~CFindFriendResult()
    {

    }

    bool CFindFriendResult::decodePackage(const std::string& data)
    {
        Json::Reader JsonReader;
        Json::Value JsonRoot;
        if (!JsonReader.parse(data, JsonRoot))
        {
            return false;
        }

        if (JsonRoot["code"].isNull() || JsonRoot["code"].asInt() != 0 || !JsonRoot["userinfo"].isArray())
            return false;

        if (JsonRoot["userinfo"].size() == 0)
            m_nResultCode = FIND_FRIEND_NOT_FOUND;
        else
        {
            m_nResultCode = FIND_FRIEND_FOUND;
            m_uAccountID = JsonRoot["userinfo"][(UINT)0]["userid"].asInt();
            strcpy_s(m_szAccountName, ARRAYSIZE(m_szAccountName), JsonRoot["userinfo"][(UINT)0]["username"].asCString());
            strcpy_s(m_szNickName, ARRAYSIZE(m_szNickName), JsonRoot["userinfo"][(UINT)0]["nickname"].asCString());
        }

        return true;
    }

    IData::IData()
    {

    }

    IData::~IData()
    {

    }

    void IData::appendPackageHeader(std::string& strBuffer) const
    {
        std::string strDestBuf;
        if (!ZlibUtil::CompressBuf(strBuffer, strDestBuf))
        {
            LOG_ERROR("Compress error.");
            return;
        }

        //插入包头
        int32_t length = (int32_t)strBuffer.length();
        protocol::msg header;
        header.compressflag = 1;
        header.originsize = length;
        header.compresssize = (int32_t)strDestBuf.length();

        std::string strSendBuf;
        strSendBuf.append((const char*)&header, sizeof(header));
        strSendBuf.append(strDestBuf);

        std::swap(strBuffer, strSendBuf);
    }

    COperateFriendRequest::COperateFriendRequest()
    {
        m_uAccountID = 0;
        m_uCmd = -1;
    }

    COperateFriendRequest::~COperateFriendRequest()
    {

    }

    void COperateFriendRequest::encodePackage(std::string& str, int32_t nSeq) const
    {
        char szData[64] = { 0 };
        if (m_uCmd == Apply)
        {
            sprintf_s(szData, 64, "{\"userid\": %d, \"type\": 1}", m_uAccountID);
        }
        else if (m_uCmd == Agree || m_uCmd == Refuse)
        {
            sprintf_s(szData, 64, "{\"userid\": %d, \"type\": 3, \"accept\": %d}", m_uAccountID, m_uCmd != Agree ? 0 : 1);
        }
        else if (m_uCmd == Delete)
        {
            sprintf_s(szData, 64, "{\"userid\": %d, \"type\": 4}", m_uAccountID);
        }

        net::BinaryStreamWriter writeStream(&str);
        writeStream.WriteInt32(protocol::msg_type_operatefriend);
        writeStream.WriteInt32(nSeq);
        std::string data = szData;
        writeStream.WriteCString(szData, strlen(szData));
        writeStream.Flush();

        appendPackageHeader(str);
        LOG_INFO("Request to operate friend, type=%d, accountId=%u", m_uCmd, m_uAccountID);
    }

    COperateFriendResult::COperateFriendResult()
    {
        m_uAccountID = 0;
        m_uCmd = -1;
        memset(m_szAccountName, 0, sizeof(m_szAccountName));
        memset(m_szNickName, 0, sizeof(m_szNickName));
    }

    COperateFriendResult::~COperateFriendResult()
    {

    }

    bool COperateFriendResult::decodePackage(const std::string& strMsg)
    {
        //{"userid": 9, "type": 2, "username": "xxx"}
        Json::Reader JsonReader;
        Json::Value JsonRoot;
        if (!JsonReader.parse(strMsg, JsonRoot))
        {
            return false;
        }

        if (!JsonRoot["userid"].isInt() || !JsonRoot["type"].isInt() != 0 || !JsonRoot["username"].isString())
            return false;

        LOG_INFO("Recv operate friend request");
        int userid = JsonRoot["userid"].asInt();
        int type = JsonRoot["type"].asInt();
        std::string username = JsonRoot["username"].asString();
        //收到加好友请求
        if (type == 2)
        {
            m_uCmd = Apply;
            m_uAccountID = userid;
            strcpy_s(m_szAccountName, ARRAYSIZE(m_szAccountName), username.c_str());

            return true;
        }
        //收到加好友结果
        else if (type == 3)
        {
            if (!JsonRoot["accept"].isInt())
                return false;

            int accept = JsonRoot["accept"].asInt();

            m_uCmd = (accept != 0 ? Agree : Refuse);
            m_uAccountID = userid;
            strcpy_s(m_szAccountName, ARRAYSIZE(m_szAccountName), username.c_str());
            return true;
        }
        //删除好友或者退群
        else if (type == 5)
        {
            m_uCmd = Delete;
            m_uAccountID = userid;
            strcpy_s(m_szAccountName, ARRAYSIZE(m_szAccountName), username.c_str());
            return true;
        }

        return true;
    }

    bool CUserBasicInfoResult::decodePackage(const std::string& strMsg)
    {
        Json::Reader JsonReader;
        Json::Value JsonRoot;
        if (!JsonReader.parse(strMsg, JsonRoot))
        {
            return FALSE;
        }

        if (JsonRoot["code"].isNull() || JsonRoot["code"].asInt() != 0 || !JsonRoot["userinfo"].isArray())
            return FALSE;

        LOG_INFO("Recv user basic info, info count=%u:", JsonRoot["userinfo"].size());

        UserBasicInfoPtr pUserBasicInfo;
        UINT nTeamCount = (UINT)JsonRoot["userinfo"].size();

        std::string strTeamName;
        for (UINT i = 0; i < nTeamCount; ++i)
        {
            strTeamName = JsonRoot["userinfo"][(UINT)i]["teamname"].asString();

            std::list<UserBasicInfoPtr> friendList;

            if (!JsonRoot["userinfo"][(UINT)i]["members"].isArray())
                continue;

            for (UINT j = 0; j < JsonRoot["userinfo"][(UINT)i]["members"].size(); ++j)
            {
                pUserBasicInfo = boost::make_shared<UserBasicInfo>();
                //memset(pUserBasicInfo, 0, sizeof(UserBasicInfo));

                pUserBasicInfo->uAccountID = JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["userid"].asUInt();

#ifdef _DEBUG
                //为了调试方便加上userid
                sprintf_s(pUserBasicInfo->szAccountName, 32, "%s - %d", JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["username"].asString().c_str(), pUserBasicInfo->uAccountID);
#else
                sprintf_s(pUserBasicInfo->szAccountName, 32, "%s", JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["username"].asString().c_str(), pUserBasicInfo->uAccountID);
#endif
                //账户名
                //strcpy_s(pUserBasicInfo->szAccountName, ARRAYSIZE(pUserBasicInfo->szAccountName), pUserInfo[i].user);
                //昵称
                strcpy_s(pUserBasicInfo->szNickName, ARRAYSIZE(pUserBasicInfo->szNickName), JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["nickname"].asString().c_str());
                //备注名
                strcpy_s(pUserBasicInfo->szMarkName, ARRAYSIZE(pUserBasicInfo->szMarkName), JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["markname"].asString().c_str());
                //签名
                strcpy_s(pUserBasicInfo->szSignature, ARRAYSIZE(pUserBasicInfo->szSignature), JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["signature"].asString().c_str());
                //地址
                strcpy_s(pUserBasicInfo->szAddress, ARRAYSIZE(pUserBasicInfo->szAddress), JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["address"].asString().c_str());
                //自定义头像
                strcpy_s(pUserBasicInfo->customFace, ARRAYSIZE(pUserBasicInfo->customFace), JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["customface"].asString().c_str());
                //电话
                strcpy_s(pUserBasicInfo->szPhoneNumber, ARRAYSIZE(pUserBasicInfo->szPhoneNumber), JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["phonenumber"].asString().c_str());
                //邮箱
                strcpy_s(pUserBasicInfo->szMail, ARRAYSIZE(pUserBasicInfo->szMail), JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["mail"].asString().c_str());

                pUserBasicInfo->nStatus = JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["status"].asInt();
                pUserBasicInfo->clientType = JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["clienttype"].asInt();
                //头像ID
                pUserBasicInfo->uFaceID = JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["facetype"].asInt();
                //性别
                pUserBasicInfo->nGender = JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["gender"].asInt();
                //生日
                pUserBasicInfo->nBirthday = JsonRoot["userinfo"][(UINT)i]["members"][(UINT)j]["birthday"].asInt();

                friendList.push_back(pUserBasicInfo);
            }

            m_mapUserBasicInfo[strTeamName] = friendList;
        }
    }

    void CUserBasicInfoRequest::encodePackage(std::string& str, int32_t nSeq) const
    {
        net::BinaryStreamWriter writeStream(&str);
        writeStream.WriteInt32(protocol::msg_type_getofriendlist);
        writeStream.WriteInt32(nSeq);
        std::string dummy;
        writeStream.WriteString(dummy);
        writeStream.Flush();

        appendPackageHeader(str);
    }

    void CBuddyMessage::encodePackage(std::string& str, int32_t nSeq) const
    {
        net::BinaryStreamWriter writeStream(&str);
        writeStream.WriteInt32(protocol::msg_type_chat);
        writeStream.WriteInt32(nSeq);

        std::string strChatContent = R"({"msgText":")";
        strChatContent += m_msgMesText;
        strChatContent += R"("})";
        std::string strFont;

        
        for (int i = 0; i < (int)m_arrContent.size(); i++)
        {
            CContentPtr lpContent = m_arrContent[i];
            if (lpContent == NULL)
                continue;

            if (lpContent->m_nType == CONTENT_TYPE_TEXT)							
            {
                strChatContent += "{\"msgText\":\"";
                strChatContent += lpContent->m_strText;
                strChatContent += ("\"},");
            }
            else if (lpContent->m_nType == CONTENT_TYPE_FONT_INFO)			
            {
                stringstream ss;
                ss << "\"font\":[\"";
                ss << lpContent->m_FontInfo.m_strName << "\",";
                ss << lpContent->m_FontInfo.m_nSize;
                ss << "\"," << lpContent->m_FontInfo.m_clrText << "\",";
                ss << lpContent->m_FontInfo.m_bBold << ",";
                ss << lpContent->m_FontInfo.m_bItalic << ",";
                ss << lpContent->m_FontInfo.m_bUnderLine << "],\"";
                strFont = ss.str();
            }
            else if (lpContent->m_nType == CONTENT_TYPE_FILE)			
            {
                stringstream ss;
                ss << "\"file\":[\"";
                ss << lpContent->m_CFaceInfo.m_strFileName << "\",";
                ss << "\"" << lpContent->m_CFaceInfo.m_strFilePath << "\",";
                ss << lpContent->m_CFaceInfo.m_dwFileSize << "\",";
                ss << lpContent->m_CFaceInfo.m_bOnline << ",";

                strChatContent += ss.str();
            }
        }

        std::string strContent = boost::str(boost::format("{\"msgType\":1,\"time\":%llu,\"clientType\":1,") % time(NULL));
        strContent += strFont;

        strContent += R"("content":[)";
        strContent += strChatContent;
        strContent += R"(]})";


        writeStream.WriteString(strContent);
        writeStream.WriteInt32((int32_t)m_nTargetId);

        writeStream.Flush();

        appendPackageHeader(str);
    }

    bool CBuddyMessage::decodePackage(const std::string& strMsg)
    {
        net::BinaryStreamReader readStream(strMsg.c_str(), strMsg.length());
        int32_t senderId;
        std::string strValue;

        //int seq;
        if (!readStream.ReadInt32(senderId))
        {
            return false;
        }

        int32_t targetid;
        if (!readStream.ReadInt32(targetid))
        {
            return false;
        }

        m_nTargetId = targetid;
        m_nSendId = senderId;

        const char* lpData = strMsg.data();
        unsigned dwSize = strMsg.length();
        if (NULL == lpData || dwSize == 0)
            return false;

        Json::Reader JsonReader;
        Json::Value JsonRoot;
        std::string strText(lpData);

        if (!JsonReader.parse(strText, JsonRoot))
            return false;

        if (!JsonRoot["content"].isArray())
            return false;

        if (JsonRoot["msgType"].isNull() || !JsonRoot["msgType"].isInt())
            return false;

        m_nMsgType = (CONTENT_TYPE)JsonRoot["msgType"].asInt();

        if (JsonRoot["time"].isNull())
            return false;


        m_nTime = JsonRoot["time"].asUInt();

        CContentPtr pContent;
        pContent.reset(new CContent);

        if (!JsonRoot["font"][(UINT)0].isNull())
        {
            strValue = JsonRoot["font"][(UINT)0].asString();
            pContent->m_FontInfo.m_strName = strValue;
        }
        else
            pContent->m_FontInfo.m_strName = ("微软雅黑");

        //字体大小
        if (!JsonRoot["font"][(UINT)1].isNull())
            pContent->m_FontInfo.m_nSize = JsonRoot["font"][(UINT)1].asUInt();
        else
            pContent->m_FontInfo.m_nSize = 12;

        //字体颜色
        if (!JsonRoot["font"][(UINT)2].isNull())
            pContent->m_FontInfo.m_clrText = /*JsonValue["font"][(UINT)2].asUInt()*/"123";
        else
            pContent->m_FontInfo.m_clrText = "8889";

        //是否粗体
        if (!JsonRoot["font"][(UINT)3].isNull())
            pContent->m_FontInfo.m_bBold = JsonRoot["font"][(UINT)3].asInt() != 0 ? true : false;
        else
            pContent->m_FontInfo.m_bBold = false;

        //是否斜体
        if (!JsonRoot["font"][(UINT)4].isNull())
            pContent->m_FontInfo.m_bItalic = JsonRoot["font"][(UINT)4].asInt() != 0 ? true : false;
        else
            pContent->m_FontInfo.m_bItalic = false;

        //是否下划线
        if (!JsonRoot["font"][(UINT)5].isNull())
            pContent->m_FontInfo.m_bUnderLine = JsonRoot["font"][(UINT)5].asInt() != 0 ? true : false;
        else
            pContent->m_FontInfo.m_bUnderLine = false;

        m_arrContent.push_back(pContent);

        std::string strNodeValue;
        int nCount = (int)JsonRoot["content"].size();
        for (int i = 0; i < nCount; ++i)
        {
            if (JsonRoot["content"][i].isNull())
                continue;

            if (!JsonRoot["content"][i]["msgText"].isNull())
            {
                m_msgMesText = JsonRoot["content"][i]["msgText"].asString();
            }

            if (!JsonRoot["content"][i]["msgText"].isNull())
            {
                pContent.reset(new CContent());
                pContent->m_nType = CONTENT_TYPE_TEXT;
                strNodeValue = JsonRoot["content"][i]["msgText"].asString();
                pContent->m_strText = strNodeValue;
                m_arrContent.push_back(pContent);
            }
            else if (!JsonRoot["content"][i]["faceID"].isNull())
            {
                pContent.reset(new CContent());
                pContent->m_nType = CONTENT_TYPE_FACE;
                pContent->m_nFaceId = JsonRoot["content"][i]["faceID"].asInt();
                m_arrContent.push_back(pContent);
            }
            else if (!JsonRoot["content"][i]["shake"].isNull())
            {
                pContent.reset(new CContent());
                pContent->m_nType = CONTENT_TYPE_SHAKE_WINDOW;
                pContent->m_nShakeTimes = JsonRoot["content"][i]["shake"].asInt();
                m_arrContent.push_back(pContent);
            }
            else if (!JsonRoot["content"][i]["pic"].isNull())
            {
                pContent.reset(new CContent());
                pContent->m_nType = CONTENT_TYPE_CHAT_IMAGE;
                strNodeValue = JsonRoot["content"][i]["pic"][(UINT)0].asString();;
                pContent->m_CFaceInfo.m_strFileName = strNodeValue;

                strNodeValue = JsonRoot["content"][i]["pic"][(UINT)1].asString();;
                if (!strNodeValue.empty())
                {
                    pContent->m_CFaceInfo.m_strFilePath = strNodeValue;
                }

                pContent->m_CFaceInfo.m_dwFileSize = JsonRoot["content"][i]["pic"][(UINT)2].asUInt();
                m_arrContent.push_back(pContent);
            }
            else if (!JsonRoot["content"][i]["file"].isNull())
            {
                pContent.reset(new CContent());
                pContent->m_nType = CONTENT_TYPE_FILE;
                strNodeValue = JsonRoot["content"][i]["file"][(UINT)0].asString();;
                pContent->m_CFaceInfo.m_strFileName = strNodeValue;

                strNodeValue = JsonRoot["content"][i]["file"][(UINT)1].asString();;

                pContent->m_CFaceInfo.m_strFilePath = strNodeValue;

                pContent->m_CFaceInfo.m_dwFileSize = JsonRoot["content"][i]["file"][2].asUInt();

                pContent->m_CFaceInfo.m_bOnline = JsonRoot["content"][i]["file"][3].asUInt();
                m_arrContent.push_back(pContent);
            }
            else if (!JsonRoot["content"][i]["remotedesktop"].isNull())
            {
                pContent.reset(new CContent());
                pContent->m_nType = CONTENT_TYPE_REMOTE_DESKTOP;
                m_arrContent.push_back(pContent);
            }
        }
        return true;
    }

    bool CBuddyMessage::parse(const std::string& data)
    {
        std::string strText;
        for (int i = 0; i < data.size(); ++i)
        {
            if (data.at(i) == '/')
            {
                if (data.at(i + 1) == 'o')
                {
                    int nTemp = i + 1;
                    if (handleFontInfo(nTemp, data))
                    {
                        i = nTemp;
                        continue;
                    }
                }
                else if (data.at(i + 1) == 'i')
                {
                    int nTemp = i + 1;
                    if (handleFileInfo(nTemp, data))
                    {
                        i = nTemp;
                        continue;
                    }
                }
            }

            strText += (data.at(i));
        }

        if (!strText.empty())
        {
            CContentPtr lpContent(new CContent);
            lpContent->m_nType = CONTENT_TYPE_TEXT;
            lpContent->m_strText = strText;
            m_arrContent.push_back(lpContent);
        }

        return true;
    }


    bool CBuddyMessage::handleFontInfo(int& p, const std::string& strText)
    {
        int nStart = strText.find("[\"");
        int nEnd = strText.find("\"]");
        p = nEnd;
        if (nStart != string::npos && nEnd != string::npos)
        {
            string strTemp = strText.substr(nStart + 1, nEnd - nStart);

            string fontName;
            int    fontSize;
            string fontColor;
            bool   bBold = false;
            bool   bItalic = false;
            bool   bUnderLine = false;
            int n = utils::string_matches("%s,%d,%s,%d,%d,%d", fontName, &fontSize, &fontColor, &bBold, &bItalic, &bUnderLine);
            if (n != 6)
            {
                return false;
            }

            CContentPtr lpContent(new CContent);
            lpContent->m_nType = CONTENT_TYPE_FONT_INFO;
            lpContent->m_FontInfo.m_nSize = fontSize;
            lpContent->m_FontInfo.m_clrText = fontColor;
            lpContent->m_FontInfo.m_strName = fontName;
            lpContent->m_FontInfo.m_bBold = bBold;
            lpContent->m_FontInfo.m_bItalic = bItalic;
            lpContent->m_FontInfo.m_bUnderLine = bUnderLine;
            m_arrContent.push_back(lpContent);
            return true;
        }

        return false;
    }

    bool CBuddyMessage::handleFileInfo(int& p, const std::string& strText)
    {
        int nStart = strText.find("[\"");
        int nEnd = strText.find("\"]");
        p = nEnd;
        if (nStart != string::npos && nEnd != string::npos)
        {
            string strTemp = strText.substr(nStart + 1, nEnd - nStart);


            string strFileName;
            string strFilePath;
            unsigned long nFileSize;
            bool bOnline = true;

            int n = utils::string_matches("%s,%s,%ul,%d", strFileName, strFilePath, &nFileSize, &bOnline);
            if (n != 4)
            {
                return false;
            }

            CContentPtr lpContent(new CContent);
            lpContent->m_nType = CONTENT_TYPE_FILE;
            lpContent->m_CFaceInfo.m_strFilePath = strFilePath;
            lpContent->m_CFaceInfo.m_strName = strFileName;
            lpContent->m_CFaceInfo.m_strFileName = strFileName;
            lpContent->m_CFaceInfo.m_dwFileSize = nFileSize;
            lpContent->m_CFaceInfo.m_bOnline = bOnline;
            m_arrContent.push_back(lpContent);
            return true;
        }

        return false;
    }

    void CUpdateTeamInfoRequest::encodePackage(std::string& str, int32_t nSeq) const
    {
        net::BinaryStreamWriter writeStream(&str);
        writeStream.WriteInt32(protocol::msg_type_updateteaminfo);
        writeStream.WriteInt32(nSeq);
        std::string dummy;
        writeStream.WriteString(dummy);
        writeStream.WriteInt32(m_opType);
        std::string strUtf8NewTeamName = EncodeUtil::UnicodeToUtf8(m_strNewTeamName);
        writeStream.WriteString(strUtf8NewTeamName);
        std::string strUtf8OldTeamName = EncodeUtil::UnicodeToUtf8(m_strOldTeamName);
        writeStream.WriteString(strUtf8OldTeamName);
        writeStream.Flush();

        appendPackageHeader(str);
    }

    bool CUpLoadFileRequest::decodePackage(const char* inbuf, size_t buflength, FileSendResult& res)
    {
        BinaryStreamReader readStream(inbuf, buflength);
        int32_t cmd;
        if (!readStream.ReadInt32(cmd) || cmd != protocol::msg_type_upload_resp)
        {
            return false;
        }

        int seq;
        if (!readStream.ReadInt32(seq))
        {
            return false;
        }

        if (!readStream.ReadInt32(res.errorCode))
        {
            return false;
        }

        std::string filemd5;
        size_t md5length;
        if (!readStream.ReadString(&res.fileMd5, 0, md5length) || md5length != 32)
        {
            LOG_ERROR(("Failed to upload file: %d as read filemd5 error."), seq);
            return false;
        }

        int64_t offset = -1;
        if (!readStream.ReadInt64(res.offSetX))
        {
            LOG_ERROR(("Failed to upload file: %d as read offset error."), offset);
            return false;
        }

        int64_t filesize = -1;
        if (!readStream.ReadInt64(res.fileSize))
        {
            LOG_ERROR(("Failed to upload file: %d as read filesize error."), filesize);
            return false;
        }

        std::string dummyfiledata;
        size_t filedatalength;
        if (!readStream.ReadString(&dummyfiledata, 0, filedatalength) || filedatalength != 0)
        {
            LOG_ERROR(("Failed to upload file: %s as read dummyfiledata error."));
            return false;
        }

        return true;
    }

    void CUpLoadFileRequest::encodePackage(std::string& outbuf, int32_t nSeq) const
    {
        //std::string outbuf;
        BinaryStreamWriter writeStream(&outbuf);
        writeStream.WriteInt32(protocol::msg_type_upload_req);
        writeStream.WriteInt32(nSeq);
        writeStream.WriteCString(m_strMd5.c_str(), 32);
        writeStream.WriteInt64(m_offsetX);
        writeStream.WriteInt64(m_nFileSize);

        writeStream.WriteString(m_strContent);
        writeStream.Flush();
        file_msg headerx = { outbuf.length() };
        outbuf.insert(0, (const char*)& headerx, sizeof(headerx));

        LOG_INFO("Request to upload file, type=%d, filemd5=%s, size=%d", protocol::msg_type_upload_req, m_strMd5, headerx.packagesize);
    }

}
