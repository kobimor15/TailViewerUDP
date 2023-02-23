#pragma once
#include <fstream> //for files
#include <map>
#include <string>
#include <sstream>
#include <filesystem>
#include "..\Common\UDPDriver.h"
//#include <ctime>

namespace fs = std::filesystem;
using namespace std;

namespace udp
{
	class FileManager
	{
	public:
		void writeMessageToFile(std::string message, std::ofstream* file) const;
		//void createLogFilePath();

		std::map<std::string, std::ofstream*> m_fileDescriptors;
	};
}
