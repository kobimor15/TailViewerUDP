#pragma once
#include "..\Common\FileConfig.h"
#include "..\Common\UDPListenerDriver.h"
#include "FileManager.h"

using namespace std;

namespace udp
{
	class TailViewerUDPServer
	{
	public:
		TailViewerUDPServer() = default;
		void runTailViewerServer(const IConfig& config);
	};
}