#include "UDPClientConnection.hpp"
#include <sys/socket.h>
#include <cstdio>
#include <cstring>
UDPClientConnection::UDPClientConnection(std::string ipAddress, uint64_t portNumber)
 : m_IpAdress { ipAddress }, m_PortNumber { portNumber } 
{
}

void UDPClientConnection::Initialize()
{
    if ((m_SocketFDescriptor = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Socket Creation Failed!\n");
        exit(1);
    }

    memset(&m_ServerAddress, 0, sizeof(m_ServerAddress));

    m_ServerAddress.sin_family = AF_INET;
    m_ServerAddress.sin_port = htons(m_PortNumber);
    m_ServerAddress.sin_addr.s_addr = inet_addr(m_IpAdress.c_str());
}

void UDPClientConnection::Send(const std::string &data)
{
    sendto(m_SocketFDescriptor, (const char *)data.c_str(), data.size(),
        MSG_CONFIRM, (const struct sockaddr *) &m_ServerAddress, 
            sizeof(m_ServerAddress));
}