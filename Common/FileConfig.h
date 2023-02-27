#pragma once
#include "IConfig.h"
#include <fstream> //for files
#include <filesystem>
#include <sstream>
#include <string>

namespace network_config
{
	const std::string configFileDefaultPath = "C:\\logs\\config\\config.cfg";
	
	class FileConfig : public IConfig
	{
	public:
		FileConfig();
		std::string get_TVserver_ip() const override;
		unsigned int get_TVserver_port() const override;
	private:
		std::string m_serverIP;
		unsigned int m_serverPort;
	};
}