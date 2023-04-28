#pragma once
#include <iostream>
//#include "TailViewerUDPServer.h"
#include "../TailViewerUDP/TailViewerUDPServer.h"
//#include <FileManager.h>
#include "../TailViewerUDP/FileManager.h"
#include <thread>
#include "server.h"

using namespace tail_viewer;
using namespace network;

volatile std::thread::id tailviewerThreadID; //to stop this one using it's id??? still needed??

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