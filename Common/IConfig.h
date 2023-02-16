#pragma once
#include <string>
class IConfig
{
public:
	virtual ~IConfig() {}
	virtual std::string get_ip() = 0;
	virtual std::string get_port() = 0;
};