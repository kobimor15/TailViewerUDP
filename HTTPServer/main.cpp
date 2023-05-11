#pragma once
#include <iostream>
#include "../TailViewerUDP/TailViewerUDPServer.h"
#include "../TailViewerUDP/FileManager.h"
#include <thread>
#include "server.h"

using namespace tail_viewer;
using namespace network;

void runTVServer()
{
	TailViewerUDPServer tailViewerServer(tvSocket);
	tailViewerServer.runTailViewerServer();
}

int main()
{
	std::thread httpServerThread(runHTTPServer);
	std::thread tailViewerServerThread(runTVServer);
	while (true)
	{	
	}
	return 0;
}