#pragma once
#include "..\Common\udpBasics.h"
#include <iostream>

namespace udp
{

	char buffer[BUFFER_SIZE];

	class Client : udpBasics
	{
	public:
		void init(CommunicationInfo* commuInfo);
		std::string createMessage(std::string msg);
		void sendMessageToServer(std::string msg);
		int recvMessage();
		std::string putInstructionInMessage(Instructions ins);


	protected:
		CommunicationInfo* m_commuInfo;
		
	};

}