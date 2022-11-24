#pragma once
#include "..\Common\udpBasics.h"
#include <iostream>

namespace udp
{
	class Client : udpBasics
	{
	public:
		void init(CommunicationInfo* commuInfo);
		std::string createMessage(std::string msg);
		void sendMessageToServer(std::string msg);
		void recvMessage();
		std::string putInstructionInMessage(Instructions ins);
		
	protected:
		CommunicationInfo* m_commuInfo;

	private:
		char clientBuffer[BUFFER_SIZE];
	};

}