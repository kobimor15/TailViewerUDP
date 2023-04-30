#pragma once
#include "IConfig.h"
#include <fstream> //for files
#include <filesystem>
#include <sstream>
#include <string>
#include <iostream>

namespace network_config
{
	const std::string configFileDefaultPath = "C:\\logs\\config\\config.cfg";
	
	class FileConfig : public IConfig
	{
	public:
		//FileConfig();
		FileConfig() = default;
		bool initFileConfig();
		std::string getTVserverIP() const override;
		unsigned int getTVserverPort() const override;
	private:
		std::string m_serverIP;
		unsigned int m_serverPort;
	};
}