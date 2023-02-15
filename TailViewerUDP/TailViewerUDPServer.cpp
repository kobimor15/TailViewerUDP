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
		memset(&m_remote_address, 0, sizeof(m_remote_address));
		int n = recvfrom(m_local_socket, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&m_remote_address, &sizeOfClientAddr);
		buffer[n] = '\0';
		std::cout << "\nServer received: " << buffer << "\n";
	}

	void TailViewerUDPServer::writeMessageToFile(std::string message, std::ofstream* file) const
	{
		*file << message;
	}

	void TailViewerUDPServer::runTailViewerServer()
	{

		/* Get the ip and port from the configuration file */
		//Config file should be at C:\\logs\config, and should look like: "ip_address \n port"
		ifstream configFile("C:\\logs\\config\\config.cfg");
		string serverIP, serverPortString;
		if (configFile.good())
		{
			getline(configFile, serverIP);
			getline(configFile, serverPortString);
		}
		unsigned int ServerPort = stoi(serverPortString);

		udp::CommunicationInfo cmi1 = udp::CommunicationInfo(serverIP, EMPTY_IP, ServerPort, EMPTY_PORT);
		udp::TailViewerUDPServer udpServer = udp::TailViewerUDPServer();
		udpServer.init(&cmi1); //Initialize server

		while (true)
		{
			cout << "Server is waiting for message...";
			udpServer.recvMessageFrom();
			string msg;
			msg = udpServer.buffer;

			/* Creating the path and folders (if not exists): */
			// 1. Create folder C:\\logs
			stringstream createPathString;
			createPathString << "C:\\logs\\";
			fs::create_directories(createPathString.str());

			// 2. Create folder of the date in C:\\logs\date
			struct tm newtime;
			time_t ltm = time(0);
			localtime_s(&newtime, &ltm);
			createPathString << newtime.tm_mday << "-" << newtime.tm_mon+1 << "-" << newtime.tm_year + 1900;
			fs::create_directories(createPathString.str());

			// 3. Create folder of the sender ip in C:\\logs\date\ip
			struct sockaddr_in rmtAddr = udpServer.getRemoteAddress();
			char senderIP[INET_ADDRSTRLEN] = "";
			struct sockaddr_in addr_in = (struct sockaddr_in)rmtAddr;
			inet_ntop(AF_INET, &(addr_in.sin_addr), senderIP, INET_ADDRSTRLEN); //Convert the ip to readable text
			createPathString << "\\" << senderIP;
			fs::create_directories(createPathString.str());

			// Add/Search in map:
			auto itr = udpServer.fileDescriptors.find(senderIP);
			if (itr != udpServer.fileDescriptors.end()) //enter if exists in the map
			{
				udpServer.writeMessageToFile(msg, (itr->second));
				(itr->second)->flush();
			}
			else //case not exists in the map, create the file
			{
				createPathString << "\\" << "input_from_udp.txt";
				auto fileName = createPathString.str();
				std::ofstream* newFile = new std::ofstream(fileName, std::ios_base::app);

				udpServer.fileDescriptors.insert({ senderIP, newFile }); //insert the new file descriptor to the map
				udpServer.writeMessageToFile(msg, newFile);
				newFile->flush();
			}
		}
	}
}