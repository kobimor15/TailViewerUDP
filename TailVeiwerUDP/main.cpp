#include "TailViewerUDPServer.h"
#include <fstream> //for files
#include <map>
#include <string>
#include <sstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;
using namespace std;

int main()
{
	/* Get the ip and port from the configuration file */
	//Config file should be at C:\\logs\config, and should look like: "ip_address \n port"
	ifstream configFile("C:\\logs\\config\\config.cfg");
	string serverIP, serverPortString;
	if (configFile.good())
	{
		getline(configFile, serverIP);
		getline(configFile, serverPortString);
	}
	unsigned int ServerPort = stoi(serverPortString);

	udp::CommunicationInfo cmi1 = udp::CommunicationInfo(serverIP, EMPTY_IP, ServerPort, EMPTY_PORT);
	udp::TailViewerUDPServer udpServer = udp::TailViewerUDPServer();
	udpServer.init(&cmi1); //Initialize server

	while (true)
	{
		cout << "Server is waiting for message...";
		udpServer.recvMessageFrom();
		string msg;
		msg = udpServer.buffer;
		
		/* Creating the path and folders (if not exists): */
		// 1. Create folder C:\\logs
		stringstream createPathString;
		createPathString << "C:\\logs\\";
		fs::create_directories(createPathString.str()); 

		// 2. Create folder of the date in C:\\logs\date
		struct tm newtime;
		time_t ltm = time(0);
		localtime_s(&newtime, &ltm);
		createPathString  << newtime.tm_mday << "-" << newtime.tm_mon << "-" << newtime.tm_year + 1900;
		fs::create_directories(createPathString.str());

		// 3. Create folder of the sender ip in C:\\logs\date\ip
		struct sockaddr_in rmtAddr = udpServer.getRemoteAddress();
		char senderIP[INET_ADDRSTRLEN] = "";
		struct sockaddr_in addr_in = (struct sockaddr_in)rmtAddr;
		inet_ntop(AF_INET, &(addr_in.sin_addr), senderIP, INET_ADDRSTRLEN); //Convert the ip to readable text
		createPathString << "\\" << senderIP;
		fs::create_directories(createPathString.str());

		// Add/Search in map:
		auto itr = udpServer.fileDescriptors.find(senderIP);
		if (itr != udpServer.fileDescriptors.end()) //enter if exists in the map
		{
			udpServer.writeMessageToFile(msg, (itr->second));
			(itr->second)->flush();
		}
		else //case not exists in the map, create the file
		{
			createPathString << "\\" << "input_from_udp.txt";
			auto fileName = createPathString.str();
			std::ofstream* newFile = new std::ofstream(fileName,std::ios_base::app);

			udpServer.fileDescriptors.insert({ senderIP, newFile }); //insert the new file descriptor to the map
			udpServer.writeMessageToFile(msg, newFile);
			newFile->flush();
		}
	}
}