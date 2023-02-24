#pragma once
#include "EthernetDriver.h"

namespace udp
{
	class UDPListenerDriver : public EthernetDriver
	{
	public:
		bool initDriver(CommunicationInfo* commuInfo) override;
		std::string receiveMessage() override;
		//UDPListenerDriver() = default; //////////temp
		//~UDPListenerDriver() = default;//////////temp 

		char buffer[BUFFER_SIZE];

	};
}

