#include "FileConfig.h"

namespace udp
{
	FileConfig::FileConfig()
	{
		std::ifstream configFile(configFileDefaultPath);
		std::string serverIP, serverPortString;
		if (configFile.good())
		{
			getline(configFile, m_serverIP);//ignore ip line
			getline(configFile, serverPortString);
		}
		m_serverPort = stoi(serverPortString);
	}
	std::string FileConfig::get_TVserver_ip()
	{		
		return m_serverIP;
	}

	unsigned int FileConfig::get_TVserver_port()
	{
		return m_serverPort;
	}
}