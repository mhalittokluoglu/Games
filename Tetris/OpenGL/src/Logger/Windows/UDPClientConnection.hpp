#ifndef _UDPCLIENTCONNECTION_HPP_
#define _UDPCLIENTCONNECTION_HPP_
#include <string>
#include <WinSock2.h>

class UDPClientConnection
{
public:
    UDPClientConnection(std::string ipAddress, uint64_t portNumber);
    void Initialize();
    void Send(const std::string &data);
    
private:
    struct sockaddr_in m_ServerAddress;
    int64_t m_SocketFDescriptor;
    std::string m_IpAdress;
    uint64_t m_PortNumber;
};
#endif