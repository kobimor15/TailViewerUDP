#include "UDPListenerDriver.h"

namespace udp
{
	bool UDPListenerDriver::initDriver(CommunicationInfo* commuInfo)
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

		/* Bind: */
		error_code = bind(m_local_socket, (struct sockaddr*)&m_local_address, sizeof(m_local_address));
		if (error_code == -1)
		{
			std::cout << "Error - bind failed. Error:" << WSAGetLastError() << "\n";
			getchar();
			exit(1);
		}
	}
}