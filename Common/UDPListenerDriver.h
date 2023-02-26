#pragma once
#include "EthernetDriver.h"

namespace udp //NETWORK
{
	class UDPListenerDriver : public EthernetDriver
	{
	public:
		bool initDriver(CommunicationInfo* commuInfo) override;
		std::string receiveMessage() override;

		char buffer[BUFFER_SIZE];

	};
}