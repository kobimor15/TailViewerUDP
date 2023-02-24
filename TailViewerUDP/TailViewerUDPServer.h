#pragma once
//#include "..\Common\UDPDriver.h"
#include "..\Common\FileConfig.h"
#include "..\Common\UDPListenerDriver.h"
#include "FileManager.h"
//#include <fstream> //for files
//#include <map>
//#include <string>
//#include <sstream>
//#include <filesystem>
//#include <ctime>

//namespace fs = std::filesystem;



//enum ConfigurationSource
//{
//	file = 0,
//	httpServer
//};



using namespace std;

namespace udp
{
	//class TailViewerUDPServer : public UDPDriver
	class TailViewerUDPServer
	{
	public:
		TailViewerUDPServer() = default;
		void runTailViewerServer();
		//void init(CommunicationInfo* commuInfo);// moved to UDPListenerDriver
		//void recvMessageFrom(); //moved to UDPListenerDriver
		//void writeMessageToFile(std::string message, std::ofstream* file) const; //moved to FileManager


		////delete, redundant
		//static void runTailViewerServer(); //Starts the server, includ initializing and all.

		//std::map<std::string, std::ofstream*> m_fileDescriptors; //moved to FileManager

		//char buffer[BUFFER_SIZE]; //moved to UDPListenerDriver
	};
}