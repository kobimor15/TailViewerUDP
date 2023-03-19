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
		}
		else
		{
			std::cout << "Error - can't open config file.\n";
			getchar();
			exit(1);
		}
		m_serverPort = stoi(serverPortString);
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