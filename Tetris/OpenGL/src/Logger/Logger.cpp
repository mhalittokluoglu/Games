#include "Logger.hpp"
#include <cstdarg>
#include <chrono>
UDPClientConnection *Logger::m_Connection = nullptr;

void Logger::InitLogger(const String &ipAddres, uint64_t portNumber)
{
    m_Connection = new UDPClientConnection(ipAddres, portNumber);
    m_Connection->Initialize();
    LOG_DEBUG("Logger Initialized!");
}


void Logger::LOG_DEBUG(String data, ...)
{
    String temp;
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    String currentSystemTime = GetTime();
    sprintf(data, "0%s%s\n", static_cast<char*>(currentSystemTime), static_cast<char*>(temp)); // 0 Indicating INFO
    data.UpdateSize();
    m_Connection->Send(data);
}

void Logger::LOG_WARNING(String data, ...)
{
    String temp;
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    String currentSystemTime = GetTime();
    sprintf(data, "1%s%s\n", static_cast<char*>(currentSystemTime), static_cast<char*>(temp)); // 0 Indicating INFO
    data.UpdateSize();
    m_Connection->Send(data);
}

void Logger::LOG_ERROR(String data, ...)
{
    String temp;
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    String currentSystemTime = GetTime();
    sprintf(data, "2%s%s\n", static_cast<char*>(currentSystemTime), static_cast<char*>(temp)); // 0 Indicating INFO
    data.UpdateSize();
    m_Connection->Send(data);
}

void Logger::LOG_FATAL(String data, ...)
{
    String temp;
    va_list args;

    va_start(args, data);
    vsprintf(temp, data, args);
    va_end(args);
 
    String currentSystemTime = GetTime();
    sprintf(data, "3%s%s\n", static_cast<char*>(currentSystemTime), static_cast<char*>(temp)); // 0 Indicating INFO
    data.UpdateSize();
    m_Connection->Send(data);
}

String Logger::GetTime()
{
    time_t currentTime = time(0);
    tm* timeLocal = localtime(&currentTime);
    char buffer[50] = { 0 };
    strftime(buffer, sizeof(buffer), "%Y:%m:%d %H:%M:%S:", timeLocal);
    String currentSystemTime;
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