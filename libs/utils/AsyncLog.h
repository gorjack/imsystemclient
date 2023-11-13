/** 
 * @desc:   异步日志类，AsyncLog.h
 * @author: zhangyl
 * @date:   2019.04.13
 */

#ifndef __ASYNC_LOG_H__
#define __ASYNC_LOG_H__

#include <windows.h>
#include <stdio.h>
#include <string>
#include <list>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>


#define LOG_API

enum LOG_LEVEL_ASYNC
{
    LOG_LEVEL_TRACE_ASYNC,
    LOG_LEVEL_DEBUG_ASYNC,
    LOG_LEVEL_INFO_ASYNC,
    LOG_LEVEL_WARNING_ASYNC,
    LOG_LEVEL_ERROR_ASYNC,    //用于业务错误
    LOG_LEVEL_SYSERROR_ASYNC, //用于技术框架本身的错误
    LOG_LEVEL_FATAL_ASYNC,    //FATAL 级别的日志会让在程序输出日志后退出
    LOG_LEVEL_CRITICAL_ASYNC  //CRITICAL 日志不受日志级别控制，总是输出
};


//TODO: 多增加几个策略
//注意：如果打印的日志信息中有中文，则格式化字符串要用_T()宏包裹起来，
//e.g. LOGI(_T("GroupID=%u, GroupName=%s, GroupName=%s."), lpGroupInfo->m_nGroupCode, lpGroupInfo->m_strAccount.c_str(), lpGroupInfo->m_strName.c_str());
#define LOGT(...)    CAsyncLog::output(LOG_LEVEL_TRACE_ASYNC, __FILE__, __LINE__, __VA_ARGS__)
#define LOGD(...)    CAsyncLog::output(LOG_LEVEL_DEBUG_ASYNC, __FILE__, __LINE__, __VA_ARGS__)
#define LOGI(...)    CAsyncLog::output(LOG_LEVEL_INFO_ASYNC, __FILE__, __LINE__, __VA_ARGS__)
#define LOGW(...)    CAsyncLog::output(LOG_LEVEL_WARNING_ASYNC, __FILE__, __LINE__,__VA_ARGS__)
#define LOGE(...)    CAsyncLog::output(LOG_LEVEL_ERROR_ASYNC, __FILE__, __LINE__, __VA_ARGS__)
#define LOGSYSE(...) CAsyncLog::output(LOG_LEVEL_SYSERROR_ASYNC, __FILE__, __LINE__, __VA_ARGS__)
#define LOGF(...)    CAsyncLog::output(LOG_LEVEL_FATAL_ASYNC, __FILE__, __LINE__, __VA_ARGS__)        //为了让FATAL级别的日志能立即crash程序，采取同步写日志的方法
#define LOGC(...)    CAsyncLog::output(LOG_LEVEL_CRITICAL_ASYNC, __FILE__, __LINE__, __VA_ARGS__)     //关键信息，无视日志级别，总是输出

//用于输出数据包的二进制格式
#define LOG_DEBUG_BIN(buf, buflength) CAsyncLog::outputBinary(buf, buflength)

class UTILS_EXPORT CAsyncLog
{
public:
    static bool init(const char* pszLogFileName = nullptr, bool bTruncateLongLine = false, int64_t nRollSize = 10 * 1024 * 1024);
	static void uninit();

    static void setLevel(LOG_LEVEL_ASYNC nLevel);
    static bool isRunning();
	
	//不输出线程ID号和所在函数签名、行号
	//static bool output(long nLevel, const char* pszFmt, ...);
	//输出线程ID号和所在函数签名、行号	
    static bool output(long nLevel, const char* pszFileName, int nLineNo, const char* pszFmt, ...);

    static bool outputBinary(unsigned char* buffer, size_t size);

private:
    CAsyncLog() = delete;
    ~CAsyncLog() = delete;

    CAsyncLog(const CAsyncLog& rhs) = delete;
    CAsyncLog& operator=(const CAsyncLog& rhs) = delete;

    static void makeLinePrefix(long nLevel, std::string& strPrefix);
    static void getTime(char* pszTime, int nTimeStrLength);
    static bool createNewFile(const char* pszLogFileName);
    static bool writeToFile(const std::string& data);
    //让程序主动崩溃
    static void crash();

    static const char* ullto4Str(int n);
    static char* formLog(int& index, char* szbuf, size_t size_buf, unsigned char* buffer, size_t size);

    static void writeThreadProc();
	
private:
	static bool		                        m_bToFile;			    //日志写入文件还是写到控制台  
	static FILE*                            m_hLogFile;
    static std::string                      m_strFileName;          //日志文件名
    static std::string                      m_strFileNamePID;    //文件名中的进程id
    static bool                             m_bTruncateLongLog;     //长日志是否截断
    static LOG_LEVEL_ASYNC                        m_nCurrentLevel;        //当前日志级别
    static int64_t                          m_nFileRollSize;        //单个日志文件的最大字节数
    static int64_t                          m_nCurrentWrittenSize;  //已经写入的字节数目
    static std::list<std::string>           m_listLinesToWrite;     //待写入的日志
    static std::unique_ptr<std::thread>     m_spWriteThread;
    static std::mutex                       m_mutexWrite;
    static std::condition_variable          m_cvWrite;
    static bool                             m_bExit;                //退出标志
    static bool                             m_bRunning;             //运行标志
};

#endif // !__ASYNC_LOG_H__