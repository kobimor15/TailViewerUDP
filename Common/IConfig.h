#pragma once
#include <string>

namespace network_config
{
	class IConfig
	{
	public:
		virtual ~IConfig() {}
		virtual std::string getTVserverIP() const = 0;
		virtual unsigned int getTVserverPort() const = 0;
	};
}