#include "Logger.hpp"
#include <cstdarg>
#include <chrono>
#include <cstring>
UDPClientConnection *Logger::m_Connection = nullptr;

void Logger::InitLogger(const char *ipAddres, uint64_t portNumber)
{
#ifdef LOG_ENABLED
    m_Connection = new UDPClientConnection(ipAddres, portNumber);
    m_Connection->Initialize();
    LOG_DEBUG("Logger Initialized!");
#endif
}

void Logger::LogDebug(const char *data, ...)
{
#ifdef LOG_ENABLED
    char temp[1024];
    memset(temp, 0, sizeof(temp));
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    std::string logMessage = temp;
    logMessage = "0" + logMessage + GetTime();
    m_Connection->Send(logMessage);
#endif
}

void Logger::LogWarning(const char *data, ...)
{
#ifdef LOG_ENABLED
    char temp[1024];
    memset(temp, 0, sizeof(temp));
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    std::string logMessage = temp;
    logMessage = "1" + logMessage + GetTime();
    m_Connection->Send(logMessage);
#endif
}

void Logger::LogError(const char *data, ...)
{
#ifdef LOG_ENABLED
    char temp[1024];
    memset(temp, 0, sizeof(temp));
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    std::string logMessage = temp;
    logMessage = "2" + logMessage + GetTime();
    m_Connection->Send(logMessage);
#endif
}

void Logger::LogFatal(const char *data, ...)
{
#ifdef LOG_ENABLED
    char temp[1024];
    memset(temp, 0, sizeof(temp));
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    std::string logMessage = temp;
    logMessage = "3" + logMessage + GetTime();
    m_Connection->Send(logMessage);
#endif
}

std::string Logger::GetTime()
{
    time_t currentTime = time(0);
    tm* timeLocal = localtime(&currentTime);
    char buffer[50] = { 0 };
    strftime(buffer, sizeof(buffer), "%Y:%m:%d %H:%M:%S:", timeLocal);
    std::string currentSystemTime;
    currentSystemTime = buffer;
    int64_t currentTimeInMiliSec = currentTime * 1000;
    auto millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int64_t miliSec = millisec_since_epoch - currentTimeInMiliSec;
    if (miliSec > 999)
    {
        miliSec -= 1000;
    }
    char miliSecString[4] = "000";
    if (miliSec < 10)
    {
        sprintf(&miliSecString[2], "%d", (int32_t)miliSec);
    }
    else if (miliSec < 100)
    {
        sprintf(&miliSecString[1], "%d", (int32_t)miliSec);
    }
    else
    {
        sprintf(miliSecString, "%d", (int32_t)miliSec);
    }
    currentSystemTime = currentSystemTime + miliSecString;
    currentSystemTime = currentSystemTime + " -> ";
    return currentSystemTime;
}