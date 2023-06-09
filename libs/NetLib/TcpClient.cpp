#include <stdio.h>  // snprintf
#include <functional>

#include "TcpClient.h"
#include <AsyncLog.h>
#include "Platform.h"
#include "EventLoop.h"
#include "Sockets.h"
#include "Connector.h"

using namespace net;

// TcpClient::TcpClient(EventLoop* loop)
//   : loop_(loop)
// {
// }

// TcpClient::TcpClient(EventLoop* loop, const string& host, uint16_t port)
//   : loop_(CHECK_NOTNULL(loop)),
//     serverAddr_(host, port)
// {
// }

namespace net
{
    namespace detail
    {

        void removeConnection(EventLoop* loop, const TcpConnectionPtr& conn)
        {
            loop->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
        }

        void removeConnector(const ConnectorPtr& connector)
        {
            //connector->
        }

    }

    void TcpClient::setAddress(const string& ip, uint16_t& port)
    {
        connector_->setAddress(ip, port);
    }

    const std::string TcpClient::getAddress()
    {
        return connector_->serverAddress().toIpPort();
    }

    void TcpClient::setErrorMegCallBack(const ErrorMessageCallBack&cb)
    {
        m_errorCallbackCB = cb;
        connector_->setErrorCallback(m_errorCallbackCB);
    }
}


TcpClient::TcpClient(EventLoop* loop,
    const InetAddress& serverAddr,
    const std::string& nameArg)
    : loop_(loop),
    connector_(new Connector(loop, serverAddr)),
    name_(nameArg),
    connectionCallback_(defaultConnectionCallback),
    messageCallback_(defaultMessageCallback),
    retry_(false),
    connect_(true),
    nextConnId_(1)
{
    connector_->setNewConnectionCallback(
        std::bind(&TcpClient::newConnection, this, std::placeholders::_1));
    // FIXME setConnectFailedCallback
    LOGD("TcpClient::TcpClient[%s] - connector 0x%x", name_.c_str(), connector_.get());
}

TcpClient::~TcpClient()
{
    LOGD("TcpClient::~TcpClient[%s] - connector 0x%x", name_.c_str(), connector_.get());
    TcpConnectionPtr conn;
    bool unique = false;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        unique = connection_.unique();
        conn = connection_;
    }
    if (conn)
    {
        //assert(loop_ == conn->getLoop());
        if (loop_ != conn->getLoop())
            return;

        // FIXME: not 100% safe, if we are in different thread
        CloseCallback cb = std::bind(&detail::removeConnection, loop_, std::placeholders::_1);
        loop_->runInLoop(std::bind(&TcpConnection::setCloseCallback, conn, cb));
        if (unique)
        {
            conn->forceClose();
        }
    }
    else
    {
        connector_->stop();
        // FIXME: HACK
        // loop_->runAfter(1, boost::bind(&detail::removeConnector, connector_));
    }
}

void TcpClient::connect()
{
    LOGD("<====start connecting to====> %s",  connector_->serverAddress().toIpPort().c_str());
    connect_ = true;
    connector_->start();
}

bool TcpClient::isConnected()
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (NULL != connection_)
    {
        return true;
    }

    return false;
}

void TcpClient::disconnect()
{
    connect_ = false;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (connection_)
        {
            connection_->shutdown();
        }
    }
}

void TcpClient::disconnectFull()
{
    connect_ = false;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (connection_)
        {
            connection_->forceClose();
        }

        if (connector_)
        {
            //这里有个问题 要是之前的connect close出问题了， connector不知道连接状态是啥， 这里是异步的。 但只有这么做下一次connect的时候才不会卡住
            connector_->disconnectState();
        }
    }
}

void TcpClient::stop()
{
    connect_ = false;
    connector_->stop();
}

void TcpClient::newConnection(int sockfd)
{
    loop_->assertInLoopThread();
    InetAddress peerAddr(sockets::getPeerAddr(sockfd));
    char buf[32];
    snprintf(buf, sizeof buf, ":%s#%d", peerAddr.toIpPort().c_str(), nextConnId_);
    ++nextConnId_;
    string connName = name_ + buf;

    InetAddress localAddr(sockets::getLocalAddr(sockfd));
    // FIXME poll with zero timeout to double confirm the new connection
    // FIXME use make_shared if necessary
    TcpConnectionPtr conn(new TcpConnection(loop_, connName, sockfd, localAddr, peerAddr));
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setErrorMegCallBack(m_errorCallbackCB);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(std::bind(&TcpClient::removeConnection, this, std::placeholders::_1)); // FIXME: unsafe
    
    {
        std::unique_lock<std::mutex> lock(mutex_);
        connection_ = conn;
    }

    conn->connectEstablished();
    LOGD(" <====success connecting to====> %s, address=>%p", connector_->serverAddress().toIpPort().c_str(), this);

}

void TcpClient::removeConnection(const TcpConnectionPtr& conn)
{
    loop_->assertInLoopThread();
    //assert(loop_ == conn->getLoop());
    if (loop_ != conn->getLoop())
        return;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        //assert(connection_ == conn);
        if (connection_ != conn)
            return;

        connection_.reset();
    }

    loop_->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    if (retry_ && connect_)
    {
        LOGD( "TcpClient::connect[%s] - Reconnecting to %s", name_.c_str(), connector_->serverAddress().toIpPort().c_str());
        connector_->restart();
    }
}

