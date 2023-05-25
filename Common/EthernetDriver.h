#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h> //for inet_pton function
#include <string>

namespace network
{
	constexpr int BUFFER_SIZE = 60000;
	constexpr int IP_SIZE = 16;
	constexpr int PORT_SIZE = 4;

	/* ---------- CommunicationInfo Struct ---------- */
	struct CommunicationInfo
	{
		CommunicationInfo(const std::string& localIP, const unsigned int& localPort)
		{
			this->localIP = localIP;
			this->localPort = localPort;
		}
	public:
		std::string localIP;
		unsigned int localPort;

	};

	/* --------- EthernetDriver Class --------- */
	class EthernetDriver
	{
	public:
		virtual bool initEthernetDriver(CommunicationInfo& commuInfo) = 0;
		virtual std::string receiveMessage() = 0;

		void closeSocket(SOCKET socket);
		std::string getRemoteIP() const;
		SOCKET m_local_socket = INVALID_SOCKET;
		
	protected:
		struct sockaddr_in m_local_address;
		struct sockaddr_in m_remote_address;
	};
}