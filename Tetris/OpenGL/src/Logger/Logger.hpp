#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#define LOG_DEBUG(...)      Logger::LogDebug(__VA_ARGS__)
#define LOG_WARNING(...)    Logger::LogWarning(__VA_ARGS__)
#define LOG_ERROR(...)      Logger::LogError(__VA_ARGS__)
#define LOG_FATAL(...)      Logger::LogFatal(__VA_ARGS__)

#ifdef LINUX_SYSTEM
#include "Linux/UDPClientConnection.hpp"
#endif

#ifdef WINDOWS_SYSTEM
#include "Windows/UDPClientConnection.hpp"
#endif

class Logger
{
public:
    static void InitLogger(const char *ipAddres, uint64_t portNumber);
    static void LogDebug(const char *data, ...);
    static void LogWarning(const char *data, ...);
    static void LogError(const char *data, ...);
    static void LogFatal(const char *data, ...);


private:
    static std::string GetTime();
    static UDPClientConnection *m_Connection;
};
#endif