#pragma once
#include "IConfig.h"
#include <fstream> //for files
#include <filesystem>
#include <sstream>
#include <string>

namespace udp
{
	const std::string configFileDefaultPath = "C:\\logs\\config\\config.cfg";
	
	class FileConfig : public IConfig
	{
	public:
		FileConfig(); //C-tor
		std::string get_TVserver_ip() override;
		unsigned int get_TVserver_port() override;
	private:
		std::string m_serverIP;
		unsigned int m_serverPort;
	};
}