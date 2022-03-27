#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_
#include "UDPClientConnection.hpp"
class Logger
{
public:
    static void InitLogger(const String &ipAddres, uint64_t portNumber);
    static void LOG_DEBUG(String data, ...);
    static void LOG_WARNING(String data, ...);
    static void LOG_ERROR(String data, ...);
    static void LOG_FATAL(String data, ...);


private:
    static String GetTime();
    static UDPClientConnection *m_Connection;
};
#endif