#pragma once
#include <fstream> //for files
#include <map>
#include <string>
#include <sstream>
#include <filesystem>
#include "..\Common\UDPDriver.h"
#include <ctime>

namespace fs = std::filesystem;
using namespace std;

const std::string logFileDefaultPath = "C:\\logs\\";

namespace udp
{
	class FileManager
	{
	public:
		FileManager() = default;
		void writeMessageToFile(std::string message, std::ofstream* file) const;
		void writeMessageToFile(std::string message, std::string remote_ip);
		//void writeMessageToFile(std::string message, char* remote_ip);
		void createLogFileDescriptor(std::string remote_ip);
		//void createLogFileDescriptor(char* remote_ip);

		std::map<std::string, std::ofstream*> m_fileDescriptors;
	};
}
