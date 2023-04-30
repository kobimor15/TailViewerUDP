#include "UDPListenerDriver.h"

namespace network
{
	bool UDPListenerDriver::initEthernetDriver(CommunicationInfo& commuInfo)
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
			std::cout << "Error - WSAStartup failed. Error num:" << WSAGetLastError() << "\n";
			//getchar();
			//exit(1);
			return false;
		}

		int error_code;

		/* Specify an address for the socket: */
		//memset(&m_local_address, 0, sizeof(sockaddr_in));
		m_local_address.sin_family = AF_INET; //for Ipv4
		m_local_address.sin_port = htons(commuInfo.localPort);
		std::string local_IP = commuInfo.localIP;
		error_code = inet_pton(AF_INET, local_IP.c_str(), &(m_local_address.sin_addr));
		if (error_code <= 0)
		{
			std::cout << "Error - failed to convert ip address to struct in_addr. Error num:" << WSAGetLastError() << "\n";
			//getchar();
			//exit(1);
			return false;
		}

		/* Bind: */
		error_code = bind(m_local_socket, (struct sockaddr*)&m_local_address, sizeof(m_local_address));
		if (error_code == -1)
		{
			std::cout << "Error - bind failed. Error num:" << WSAGetLastError() << "\n";
			//getchar();
			//exit(1);
			return false;
		}
		return true;
	}

	std::string UDPListenerDriver::receiveMessage()
	{
		int sizeOfClientAddr = sizeof(struct sockaddr_in);
		memset(&m_remote_address, 0, sizeof(m_remote_address));
		int n = recvfrom(m_local_socket, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&m_remote_address, &sizeOfClientAddr);
		if (n == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error == WSAEINTR) //Means the socket closed - the recv call was interrupted
			{
				printf("recv interrupted\n");
				this->m_resetServer = true; // reset tailviewer server. reread ip and port.
			}
			else
			{
				// Handle other errors
				printf("recv error %d\n", error);
			}
		}
		buffer[n] = '\0';
		std::string buf = buffer;
		return buf;
	}
}