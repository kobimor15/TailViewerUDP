#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h> //for inet_pton function
#include <string>

namespace network
{
	constexpr int BUFFER_SIZE = 1024;
	constexpr int IP_SIZE = 16;
	constexpr int PORT_SIZE = 4;

	/* ---------- CommunicationInfo Struct ---------- */
	struct CommunicationInfo
	{
		CommunicationInfo(std::string local_IP, unsigned int local_Port)
		{
			localPort = local_Port;
			strcpy_s(localIP, local_IP.c_str());
		}
	public:
		char localIP[IP_SIZE];
		unsigned int localPort;

	};

	/* --------- EthernetDriver Class --------- */
	class EthernetDriver
	{
	public:
		virtual bool initDriver(CommunicationInfo* commuInfo) = 0;
		virtual std::string receiveMessage() = 0;

		void closeSocket(SOCKET socket);
		std::string getRemoteIP();
		struct sockaddr_in getRemoteAddress()
		{
			return m_remote_address;
		}
		SOCKET m_local_socket = INVALID_SOCKET;

	protected:
		struct sockaddr_in m_local_address;
		struct sockaddr_in m_remote_address;
	};
}