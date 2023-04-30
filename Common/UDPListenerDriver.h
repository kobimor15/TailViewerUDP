#pragma once
#include "EthernetDriver.h"

namespace network
{
	class UDPListenerDriver : public EthernetDriver
	{
	public:
		bool initEthernetDriver(CommunicationInfo& commuInfo) override;
		std::string receiveMessage() override;

		char buffer[BUFFER_SIZE];
		bool m_resetServer = true;
	};
}