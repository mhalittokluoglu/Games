#include "UDPClientConnection.hpp"
#include <cstdio>
#include <cstring>

UDPClientConnection::UDPClientConnection(std::string ipAddress, uint64_t portNumber)
 : m_IpAdress { ipAddress }, m_PortNumber { portNumber } 
{
#pragma comment(lib, "ws2_32.lib");
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. SA not initialized!, %d", WSAGetLastError());
        exit(1);
    }
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
        0, (const struct sockaddr *) &m_ServerAddress, 
            sizeof(m_ServerAddress));
}