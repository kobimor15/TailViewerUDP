#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h> //for inet_pton function
#include<string>

//#define LOCAL_IP "127.0.0.1"
//#define CLIENT_IP "" //---------temp
//#define PORT_SERVER 8210
#define BACKLOG 2 ///////--------todo check how many

constexpr unsigned int EMPTY_PORT = 1;
constexpr char EMPTY_IP[] = "0.0.0.0";

namespace udp
{
	constexpr int BUFFER_SIZE = 1024;
	constexpr int IP_SIZE = 16;
	constexpr int PORT_SIZE = 4;

	struct CommunicationInfo
	{
		//C-tor
		CommunicationInfo(std::string local_IP, std::string remote_IP, unsigned int local_Port, unsigned int remote_Port)
		{
			localPort = local_Port;
			remotePort = remote_Port;
			strcpy_s(localIP, local_IP.c_str());
			strcpy_s(remoteIP, remote_IP.c_str());
			//memcpy(localIP, local_IP, IP_SIZE);
			//memcpy(remoteIP, remote_IP, IP_SIZE);
		}
	public:
		char localIP[IP_SIZE];
		char remoteIP[IP_SIZE];
		unsigned int localPort;
		unsigned int remotePort;
	};

	struct Message
	{
	public:
		char* m_originalMessage;
		char* m_cleanMessage;
		char* m_senderIP;
		int m_senderPort;
	};

	enum Instructions
	{

	};

	class udpBasics
	{

	public:
		void closeSocket(SOCKET socket);
		
	protected:
		SOCKET m_local_socket = INVALID_SOCKET;
		struct sockaddr_in m_local_address;
		struct sockaddr_in m_remote_address;

	};
}

