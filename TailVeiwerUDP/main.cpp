#include "TailViewerUDPServer.h"
#include <fstream> //for files
#include <map>
#include <string>
#include <sstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;
using namespace std;

//void closeFiles(udp::TailViewerUDPServer udpServer); //Closing all files

int main()
{
	/* Get the ip and port from the configuration file */

	/* Config file should be at C:\\logs\config, and should look like: ip_address \n port */
	ifstream configFile("C:\\logs\\config\\config.cfg");
	string serverIP, serverPortString;
	if (configFile.good())
	{
		getline(configFile, serverIP);
		getline(configFile, serverPortString);
	}
	unsigned int ServerPort = stoi(serverPortString);
	//configFile.close(); // Close config file --------NO NEED TO CLOSE

	udp::CommunicationInfo cmi1 = udp::CommunicationInfo(serverIP, EMPTY_IP, ServerPort, EMPTY_PORT);
	udp::TailViewerUDPServer udpServer = udp::TailViewerUDPServer();
	udpServer.init(&cmi1); //Initialize server

	while (true)
	{
		cout << "Server is waiting for message...";
		udpServer.recvMessageFrom();
		udp::Message msg = udp::Message();////always create new message?? or work with the same one, as buffer??
		udpServer.splitMessage(udpServer.buffer, &msg); //Split the message to several parts

		//Creating the folders and path:
		// Create folder C:\\log
		stringstream createPathString;
		createPathString << "C:\\logs\\";
		fs::create_directories(createPathString.str()); 

		//Create foder of the sender ip in C:\\log\ip
		createPathString << msg.m_senderIP;
		auto firstDirName = createPathString.str();
		fs::create_directories(firstDirName); 

		//Create folder of the date in C:\\logs\ip\date
		struct tm newtime;
		time_t ltm = time(0);
		localtime_s(&newtime, &ltm);
		createPathString << "\\" << newtime.tm_mday << "-" << newtime.tm_mon << "-" << newtime.tm_year+1900;
		
		fs::create_directories(createPathString.str()); 

		auto itr = udpServer.fileDescriptors.find(msg.m_senderIP);
		if (itr != udpServer.fileDescriptors.end()) //enter if exists in the map
		{
			udpServer.writeMessageToFile(&msg, (itr->second));
			(itr->second)->flush();
		}
		else //case not exists in the map, create the file
		{
			createPathString << "\\" << "input_from_udp.txt";
			auto fileName = createPathString.str();
			std::ofstream* newFile = new std::ofstream(fileName,std::ios_base::app);

			//insert the new file descriptor to the map
			udpServer.fileDescriptors.insert({ msg.m_senderIP, newFile });
			
			udpServer.writeMessageToFile(&msg, newFile);
			newFile->flush();
		}
	}
}

//void closeFiles(udp::TailViewerUDPServer udpServer)
//{
//	
//
//	/* Close each of the files in the map that in the udp server */
//	map<std::string, std::ofstream*>::iterator it;
//
//	for (it = udpServer.fileDescriptors.begin(); it != udpServer.fileDescriptors.end(); it++)
//	{
//		if ((*it->second).good())
//		{
//			std::cout << "FILE IS OPEN\n";
//		}
//		it->second->close();
//		if ((*it->second).good())
//		{
//			std::cout << "FILE CLOSED, OK!!\n";
//		}
//	}
//}