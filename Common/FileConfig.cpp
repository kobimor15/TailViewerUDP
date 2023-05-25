#include "FileConfig.h"
#include <winsock2.h> //To get local pc's ip
#include <ws2tcpip.h> //To get local pc's ip

namespace network_config
{
	// This function gets the local PC's ip, if it's not written in config.cfg file.
	std::string get_local_ip() {
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			std::cout << "Error - WSAStartup failed.\n";
			return "error";
		}
		char hostname[256];
		if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
			std::cout << "Error - Failed to get the hostname.\n";
			WSACleanup();
			return "error";
		}
		struct addrinfo* result = nullptr;
		struct addrinfo* ptr = nullptr;
		struct addrinfo hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		if (getaddrinfo(hostname, nullptr, &hints, &result) != 0) {
			std::cout << "Error - Failed to get the address info.\n";
			WSACleanup();
			return "error";
		}

		for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
			char ipAddr[INET_ADDRSTRLEN];
			struct sockaddr_in* sockaddr = reinterpret_cast<struct sockaddr_in*>(ptr->ai_addr);
			const char* ipAddress = inet_ntop(AF_INET, &(sockaddr->sin_addr), ipAddr, INET_ADDRSTRLEN);
			if (ipAddress != nullptr) {
				return ipAddress;
				break;
			}
		}
		freeaddrinfo(result);
		WSACleanup();
	}

	bool createNewConfigFile()
	{
		//Open config.cfg file for write:
		std::ofstream configFileForWrite(configFileDefaultPath, std::ios::app);
		if (!configFileForWrite.is_open()) {
			std::cout << "Error - Failed to open the file for writing." << std::endl;
			return false;
		}
		//Write local PC's ip and default port in it:
		std::string serverIP = get_local_ip();
		if (serverIP == "error")
		{
			std::cout << "Error - can't get the current PC's ip. enter it manually in config.cfg file.";
			return false;
		}
		configFileForWrite << serverIP << std::endl;
		configFileForWrite << DEFAULT_PORT;
		configFileForWrite.close();
		return true;
	}

	bool FileConfig::initFileConfig()
	{
		std::ifstream configFile(configFileDefaultPath);
		std::string serverIP, serverPortString;
		if (configFile.good())
		{
			getline(configFile, m_serverIP);
			getline(configFile, serverPortString);
			if (m_serverIP == "") //If the file is empty, get the current PC's ip, and put default port.
			{
				//Create config.cfg file and put the current PC's IP and a default port:
				if (createNewConfigFile() == true)
				{
					std::ifstream configFile(configFileDefaultPath);
					if (!configFile.good())
					{
						std::cout << "Error - Failed to open the file." << std::endl;
						return false;
					}
					getline(configFile, m_serverIP);
					getline(configFile, serverPortString);
					m_serverPort = stoi(serverPortString);
					return true; // No need to check validation, because it received manually.
				}
				else //Case of error in opening file or getting the IP
					return false;
			}
			else //Case not empty content or not empty file - check validation
			{
				if (serverPortString.find_first_not_of("0123456789") != std::string::npos)
				{
					std::cout << "Error - port not made of digits only. Try to edit port.\n";
					return false;
				}
				m_serverPort = stoi(serverPortString);
				if (m_serverPort < 1024 || m_serverPort > 49151)
				{
					std::cout << "Error - invalid port: port out of range. Try to edit port.\n";
					return false;
				}
			}
		}
		else //Case config file not found
		{
			//Create config.cfg file and put the current PC's IP and a default port:
			if (createNewConfigFile() == true)
			{
				std::ifstream configFile(configFileDefaultPath);
				if (!configFile.good())
				{
					std::cout << "Error - Failed to open the file." << std::endl;
					return false;
				}
				getline(configFile, m_serverIP);
				getline(configFile, serverPortString);
				m_serverPort = stoi(serverPortString);
			}
			else //Case of error in opening file or getting the IP
			{
				std::cout << "Error - Can't create config file.\n";
				return false;
			}
		}
		return true;
	}

	std::string FileConfig::getTVserverIP() const
	{		
		return m_serverIP;
	}

	unsigned int FileConfig::getTVserverPort() const
	{
		return m_serverPort;
	}
}