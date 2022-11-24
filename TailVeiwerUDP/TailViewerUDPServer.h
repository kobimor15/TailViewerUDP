#pragma once
#include "..\Common\udpBasics.h"
#include <fstream> //for files
#include <map>

//#define BACKLOG 2 ///////---todo check how many

namespace udp
{
	class TailViewerUDPServer : udpBasics
	{
	public:
		void init(CommunicationInfo* commuInfo);
		void recvMessageFrom();
		void splitMessage(char* original_message, Message* fixedMessage); //Split the message to text, ip, port.
		void writeMessageToFile(Message* message, std::ofstream* file) const;


		std::map<std::string, std::ofstream*> fileDescriptors;

		char buffer[BUFFER_SIZE];
	};
}