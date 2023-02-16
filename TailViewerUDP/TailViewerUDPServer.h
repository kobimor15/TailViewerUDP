#pragma once
#include "..\Common\UDPDriver.h"
#include <fstream> //for files
#include <map>
#include <string>
#include <sstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;
using namespace std;

namespace udp
{
	class TailViewerUDPServer : public UDPDriver
	{
	public:
		void init(CommunicationInfo* commuInfo);
		void recvMessageFrom();
		void writeMessageToFile(std::string message, std::ofstream* file) const;

		static void runTailViewerServer(); //Starts the server, includ initializing and all.

		std::map<std::string, std::ofstream*> fileDescriptors;

		char buffer[BUFFER_SIZE];
	};
}