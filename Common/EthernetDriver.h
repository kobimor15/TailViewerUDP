#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h> //for inet_pton function
#include <string>

//delete both
//constexpr unsigned int EMPTY_PORT = 1;
//constexpr char EMPTY_IP[] = "0.0.0.0";

namespace udp
{
	constexpr int BUFFER_SIZE = 1024;
	constexpr int IP_SIZE = 16;
	constexpr int PORT_SIZE = 4;

	/* ---------- CommunicationInfo Struct ---------- */
	struct CommunicationInfo
	{
		// TODO: no need of remote port and remote ip?
	//	CommunicationInfo(std::string local_IP, std::string remote_IP, unsigned int local_Port, unsigned int remote_Port)
	//	{
	//		localPort = local_Port;
	//		remotePort = remote_Port;
	//		strcpy_s(localIP, local_IP.c_str());
	//		strcpy_s(remoteIP, remote_IP.c_str());
	//	}
	//public:
	//	char localIP[IP_SIZE];
	//	char remoteIP[IP_SIZE];
	//	unsigned int localPort;
	//	unsigned int remotePort;



		// TODO: maybe no need? we can get this data from the file and thats it..
		CommunicationInfo(std::string local_IP, unsigned int local_Port)
		{
			localPort = local_Port;
			strcpy_s(localIP, local_IP.c_str());
		}
	public:
		char localIP[IP_SIZE];
		unsigned int localPort;

	};

	/* ---------- EthernetDriver Class ---------- */
	class EthernetDriver
	{
	public:
		virtual bool initDriver(CommunicationInfo* commuInfo) = 0;
		virtual std::string receiveMessage() = 0;

		void closeSocket(SOCKET socket);
		std::string getRemoteIP();
		struct sockaddr_in getRemoteAddress() //Getter
		{
			return m_remote_address;
		}
		
	protected:
		SOCKET m_local_socket = INVALID_SOCKET;
		struct sockaddr_in m_local_address;
		struct sockaddr_in m_remote_address;
	};
}