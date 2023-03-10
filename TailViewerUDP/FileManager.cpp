#include "FileManager.h"

namespace tail_viewer
{
	void FileManager::writeMessageToFile(std::string message, std::ofstream& file) const
	{
		file << message;
	}

	void FileManager::writeMessageToFile(std::string message, std::string remote_ip)
	{
		auto itr = m_fileDescriptors.find(remote_ip); //Should always be found-'createLogFileDescriptor' func created it.
		writeMessageToFile(message, *(itr->second));
		(itr->second)->flush();
	}

	void FileManager::createLogFileDescriptor(std::string remote_ip)
	{
		string rmtIP =remote_ip;
		/* Creating the path and folders (if not exists): */
		// 1. Create folder/path: the content of 'logFileDefaultPath'
		stringstream createPathString;
		createPathString << logFileDefaultPath;
		fs::create_directories(createPathString.str());

		// 2. Create folder/path of the date in 'logFileDefaultPath'\date
		struct tm newtime;
		time_t ltm = time(0);
		localtime_s(&newtime, &ltm);
		createPathString << newtime.tm_mday << "-" << newtime.tm_mon + 1 << "-" << newtime.tm_year + 1900;
		fs::create_directories(createPathString.str());

		// 3. Create folder/path of the sender ip in 'logFileDefaultPath'\date\ip
		createPathString << "\\" << rmtIP;
		fs::create_directories(createPathString.str());

		// If file descriptor does not exists in map, create file and add it to map:
		auto itr = m_fileDescriptors.find(rmtIP);
		if (itr == m_fileDescriptors.end())
		{
			createPathString << "\\" << "input_from_udp.txt";
			auto fileName = createPathString.str();
			std::ofstream* newFile = new std::ofstream(fileName, std::ios_base::app);

			m_fileDescriptors.insert({ rmtIP, newFile }); //insert the new file descriptor to the map
			newFile->flush();
		}
	}
}