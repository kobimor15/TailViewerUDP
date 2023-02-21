#include "FileConfig.h"

namespace udp
{
	std::string FileConfig::get_ip()
	{		
		//Config file should be at C:\\logs\config, and should look like: "ip_address \n port"
		std::ifstream configFile("C:\\logs\\config\\config.cfg");
		std::string serverIP;
		if (configFile.good())
			getline(configFile, serverIP);
		return serverIP;
	}

	unsigned int FileConfig::get_port()
	{
		std::ifstream configFile("C:\\logs\\config\\config.cfg");
		std::string temp, serverPortString;
		if (configFile.good())
		{
			getline(configFile, temp);//ignore ip line
			getline(configFile, serverPortString);
		}
		unsigned int serverPort = stoi(serverPortString);
		return serverPort;
	}
}