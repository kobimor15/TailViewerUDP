#pragma once
#include "..\Common\udpBasics.h"
#include <iostream>

namespace udp
{
	class Client : udpBasics
	{
	public:
		void init(CommunicationInfo* commuInfo);
		void sendMessageToServer(std::string msg);

	protected:
		CommunicationInfo* m_commuInfo;

	private:
		char clientBuffer[BUFFER_SIZE];
	};
}