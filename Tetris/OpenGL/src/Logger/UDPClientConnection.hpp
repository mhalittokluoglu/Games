#ifndef _UDPCLIENTCONNECTION_HPP_
#define _UDPCLIENTCONNECTION_HPP_
#include "String.hpp"
#include <arpa/inet.h>

class UDPClientConnection
{
public:
    UDPClientConnection(String ipAddress, uint64_t portNumber);
    void Initialize();
    void Send(const String &data);
    
private:
    struct sockaddr_in m_ServerAddress;
    int64_t m_SocketFDescriptor;
    String m_IpAdress;
    uint64_t m_PortNumber;
};
#endif