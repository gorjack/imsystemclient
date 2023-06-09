#pragma once

#include <string>
#include <mutex>
#include "TcpConnection.h"

namespace net
{
    class EventLoop;
    class Connector;
    typedef std::shared_ptr<Connector> ConnectorPtr;

    class EVENTLOOP_EXPORT TcpClient
    {
    public:
        // TcpClient(EventLoop* loop);
        // TcpClient(EventLoop* loop, const string& host, uint16_t port);
        TcpClient(EventLoop* loop, const InetAddress& serverAddr, const string& nameArg);
        ~TcpClient();  // force out-line dtor, for scoped_ptr members.

        bool isConnected();
        void connect();
        void disconnect();
        void disconnectFull();      //完全断开连接 包括connector 和 connection
        void stop();

        TcpConnectionPtr connection() const
        {
            std::unique_lock<std::mutex> lock(mutex_);
            return connection_;
        }

        EventLoop* getLoop() const { return loop_; }
        bool retry() const;
        void enableRetry() { retry_ = true; }

        void setAddress(const string& ip, uint16_t& port);
        const std::string getAddress();
        
        const std::string& name() const
        {
            return name_;
        }

        /// Set connection callback.
        /// Not thread safe.
        void setConnectionCallback(const ConnectionCallback& cb)
        {
            connectionCallback_ = cb;
        }

        /// Set message callback.
        /// Not thread safe.
        void setMessageCallback(const MessageCallback& cb)
        {
            messageCallback_ = cb;
        }

        /// Set write complete callback.
        /// Not thread safe.
        void setWriteCompleteCallback(const WriteCompleteCallback& cb)
        {
            writeCompleteCallback_ = cb;
        }
        void setErrorMegCallBack(const ErrorMessageCallBack&cb);

    private:
        /// Not thread safe, but in loop
        void newConnection(int sockfd);
        /// Not thread safe, but in loop
        void removeConnection(const TcpConnectionPtr& conn);
     
    private:
        EventLoop*              loop_;
        ConnectorPtr            connector_; // avoid revealing Connector
        const std::string       name_;
        ConnectionCallback      connectionCallback_;
        MessageCallback         messageCallback_;
        WriteCompleteCallback   writeCompleteCallback_;
        ErrorMessageCallBack    m_errorCallbackCB;
        bool                    retry_;   // atomic
        bool                    connect_; // atomic
        // always in loop thread
        int                     nextConnId_;
        mutable std::mutex      mutex_;
        TcpConnectionPtr        connection_; // @GuardedBy mutex_
    };

}
