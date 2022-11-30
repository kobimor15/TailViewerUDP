#pragma once
#include "..\Common\udpBasics.h"
#include <fstream> //for files
#include <map>

namespace udp
{
	class TailViewerUDPServer : public udpBasics
	{
	public:
		void init(CommunicationInfo* commuInfo);
		void recvMessageFrom();
		void writeMessageToFile(std::string message, std::ofstream* file) const;

		std::map<std::string, std::ofstream*> fileDescriptors;

		char buffer[BUFFER_SIZE];
	};
}