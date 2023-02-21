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
		std::string get_ip() override;
		unsigned int get_port() override;
	};
}