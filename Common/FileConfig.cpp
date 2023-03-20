#include "FileConfig.h"

namespace network_config
{
	FileConfig::FileConfig()
	{
		std::ifstream configFile(configFileDefaultPath);
		std::string serverIP, serverPortString;
		if (configFile.good())
		{
			getline(configFile, m_serverIP);
			getline(configFile, serverPortString);
			if (serverPortString.find_first_not_of("0123456789") != std::string::npos)
			{
				std::cout << "Error - port not made of digits only.\n";
				getchar();
				exit(1);
			}
			m_serverPort = stoi(serverPortString);
			if (m_serverPort < 1024 || m_serverPort > 49151)
			{
				std::cout << "Error - invalid port.\n";
				getchar();
				exit(1);
			}
		}
		else
		{
			std::cout << "Error - can't open config file.\n";
			getchar();
			exit(1);
		}
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