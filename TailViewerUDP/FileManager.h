#pragma once
#include <fstream> //for files
#include <map>
#include <string>
#include <sstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;
using namespace std;

const std::string logFileDefaultPath = "C:\\logs\\";

namespace tail_viewer
{
	class FileManager
	{
	public:
		FileManager() = default;
		void writeMessageToFile(std::string message, std::ofstream& file) const;
		void writeMessageToFile(std::string message, std::string remote_ip);		
		/// <summary> Creates the log file and adds it to the map (if not exists) </summary>
		void createLogFileDescriptor(std::string remote_ip);

		std::map<std::string, std::ofstream*> m_fileDescriptors;
	};
}
