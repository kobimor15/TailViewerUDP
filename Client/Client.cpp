#include "Client.h"

namespace udp
{
	void Client::init(CommunicationInfo* commuInfo)
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

		memset(&m_remote_address, 0, sizeof(m_remote_address));
		m_remote_address.sin_family = AF_INET;
		m_remote_address.sin_port = htons(commuInfo->remotePort);
		int error_code = inet_pton(AF_INET, commuInfo->remoteIP, &(m_remote_address.sin_addr));
		if (error_code <= 0)
		{
			std::cout << "Error - failed to convert ip address to struct in_addr. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}

		m_local_address.sin_family = AF_INET;
		m_local_address.sin_port = htons(commuInfo->localPort);
		error_code = inet_pton(AF_INET, commuInfo->localIP, &(m_local_address.sin_addr));
		if (error_code <= 0)
		{
			std::cout << "Error - failed to convert ip address to struct in_addr. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}
	}

	void Client::sendMessageToServer(std::string msg)
	{
		const char* c_msg = msg.c_str();
		int error_code = sendto(m_local_socket, c_msg, strlen(c_msg), 0, (struct sockaddr*)(&m_remote_address), sizeof(m_remote_address));
		if (error_code == -1)
		{
			std::cout << "Error - failed to send message. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}
		if (error_code != strlen(c_msg))
		{
			std::cout << "Warning! - Some of the data may not sent successfully.\n";
			getchar();
			exit(1);
		}
	}
}