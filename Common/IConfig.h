#pragma once
#include <string>

namespace udp
{
	class IConfig
	{
	public:
		virtual ~IConfig() {}
		virtual std::string get_TVserver_ip() const = 0;
		virtual unsigned int get_TVserver_port() const = 0;
	};
}