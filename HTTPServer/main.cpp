#pragma once
#include <iostream>
#include "../TailViewerUDP/TailViewerUDPServer.h"
#include "../TailViewerUDP/FileManager.h"
#include <thread>
#include "server.h"

using namespace tail_viewer;
using namespace network;

int main()
{
	std::thread httpServerThread(runHTTPServer);
	while (true)
	{	
		TailViewerUDPServer tailViewerServer(tvSocket);
		tailViewerServer.runTailViewerServer();
	}
	return 0;
}