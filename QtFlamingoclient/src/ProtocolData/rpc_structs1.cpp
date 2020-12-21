#include "rpc_structs.h"
#include <unique>

const string& CRegisterParam::serializationRegistP()
{
    char rData[256] = { 0 };
    sprintf_s(rData,
        256,
        "{\"username\": \"%s\", \"nickname\": \"%s\", \"password\": \"%s\"}",
        m_szAccountName,
        m_szNickName,
        m_szPassword);


    std::string outbuf;
    net::BinaryStreamWriter writeStream(&outbuf);
    writeStream.WriteInt32(msg_type_register);
    writeStream.WriteInt32(0);
    std::string data = rData;
    writeStream.WriteString(data);
    writeStream.Flush();

    std::string strDestBuf;
    if (!ZlibUtil::CompressBuf(outbuf, strDestBuf))
    {
        LOG_ERROR("compress error");
        return false;
    }
    msg header;
    header.compressflag = 1;
    header.originsize = outbuf.length();
    header.compresssize = strDestBuf.length();

    std::string strSendBuf;
    strSendBuf.append((const char*)&header, sizeof(header));
    strSendBuf.append(strDestBuf);

    return strSendBuf;
}

void CRegisterResult::deserializationRegistRe(char *reStr, int nSize)
{
    std::unique_ptr<protocol::msg> msgPtr(new protocol::msg);
    memset(msgPtr, 0, sizeof(msgPtr));
    
    //char *strTemp = new char[sizeof(protocol::msg)];
    //memcpy(reStr, strTemp, sizeof(protocol::msg));

    msgPtr->compressflag = (char)reStr;
    msgPtr->originsize = (int32_t)(reStr + 1);
    msgPtr->compresssize = (int32_t)(reStr + 5);
    msgPtr->reserved = (int32_t)(reStr + 21);
}
