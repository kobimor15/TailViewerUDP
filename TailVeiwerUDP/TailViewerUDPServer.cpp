#include "TailViewerUDPServer.h"

namespace udp
{
	
	void TailViewerUDPServer::init(CommunicationInfo* commuInfo)
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		{
			std::cout << "Error - WSAStartup failed. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}

		/* Create the socket: */
		m_local_socket = socket(AF_INET, SOCK_DGRAM, 0);
		if (m_local_socket == INVALID_SOCKET)
		{
			std::cout << "Error - WSAStartup failed. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}

		int error_code;

		/* Specify an address for the socket: */
		m_local_address.sin_family = AF_INET; //for Ipv4
		m_local_address.sin_port = htons(commuInfo->localPort);
		error_code = inet_pton(AF_INET, commuInfo->localIP, &(m_local_address.sin_addr));
		if (error_code <= 0)
		{
			std::cout << "Error - failed to conver ip address to struct in_addr. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}

		//////////////////////CHECK IF I NEED TO DO IT FOR THE DESTINATION. LIKE EDEN DID.
		//m_server_address.sin_family = AF_INET; //for Ipv4
		//m_server_address.sin_port = htons(PORT_SERVER);
		//error_code = inet_pton(AF_INET, commuInfo->remoteIP, &(m_server_address.sin_addr));
		//if (error_code <= 0)
		//{
		//	std::cout << "Error - failed to conver ip address to struct in_addr. Error:" << WSAGetLastError() << "\n";
		//	getchar();
		//	exit(1);
		//}

		/* Bind: */
		error_code = bind(m_local_socket, (struct sockaddr*)&m_local_address, sizeof(m_local_address));
		if (error_code == -1)
		{
			std::cout << "Error - bind failed. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}

	}

	void TailViewerUDPServer::recvMessageFrom()
	{		
		int sizeOfClientAddr = sizeof(struct sockaddr_in);
		int n = recvfrom(m_local_socket, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&m_remote_address, &sizeOfClientAddr);
		buffer[n] = '\0';
		std::cout << "\nServer received: " << buffer << "\n";
	}

	///////////////need to check which file every client sends to. how to represent and how to notice between them.
	void TailViewerUDPServer::writeMessageToFile(Message* message, std::ofstream* file) const
	{
		*file << message->m_cleanMessage << '\n';
	}

	// the original_message build like: "text ip port" (without spaces)
	void TailViewerUDPServer::splitMessage(char* original_message, udp::Message* fixedMessage)
	{
		(*fixedMessage).m_originalMessage = original_message;
		int cleanMessageLen = strlen(original_message) + 1 - IP_SIZE - PORT_SIZE;
		int i;

		// Split IP:
		char* senderIP = new char[IP_SIZE + 1];
		for (i = 0; i < IP_SIZE-1; i++)
		{
			senderIP[i] = original_message[cleanMessageLen + i];
		}
		senderIP[i] = '\0';
		(*fixedMessage).m_senderIP = new char[strlen(senderIP)];
		memcpy((*fixedMessage).m_senderIP, senderIP, strlen(senderIP)+1);
		delete senderIP;

		// Split PORT:
		char senderPORT[PORT_SIZE];
		for (i = 0; i < PORT_SIZE; i++)
		{
			senderPORT[i] = original_message[cleanMessageLen + IP_SIZE - 1 + i];
		}
		(*fixedMessage).m_senderPort = std::stoi(senderPORT);

		// Split message:
		char* cleanMessage = new char[BUFFER_SIZE + 1];
		for (i = 0; i < cleanMessageLen; i++)
		{
			cleanMessage[i] = original_message[i];
		}
		cleanMessage[i] = '\0';
		(*fixedMessage).m_cleanMessage = new char[strlen(cleanMessage)];
		memcpy((*fixedMessage).m_cleanMessage, cleanMessage, strlen(cleanMessage) + 1);
		delete cleanMessage;

	}

}