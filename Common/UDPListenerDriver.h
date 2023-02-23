#pragma once
#include "EthernetDriver.h"

namespace udp
{
	class UDPListenerDriver : public EthernetDriver
	{
	public:
		bool initDriver(CommunicationInfo* commuInfo) override;
		//UDPListenerDriver() = default; //////////temp
		//~UDPListenerDriver() = default;//////////temp 


	};
}

