#pragma once
#include "..\Common\FileConfig.h"
#include "..\Common\UDPListenerDriver.h"
#include "FileManager.h"

using namespace std;
using namespace network_config;

namespace tail_viewer
{
	class TailViewerUDPServer
	{
	public:
		TailViewerUDPServer(SOCKET& s) {
			this->tvSocketLOC = &s;
		}
	
		bool initTVServer(const IConfig& config);
		void runTailViewerServer();
	
	private:
		SOCKET* tvSocketLOC;
	};
}