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
volatile bool g_interrupt_flag = false;
volatile std::thread::id tailviewerThreadID;

void runTailViewerServer()
{
	TailViewerUDPServer tailViewerServer;
	FileConfig fconfig = FileConfig();
	tvSocket = tailViewerServer.init(fconfig);
	tailViewerServer.runTailViewerServer();
}

int main()
{
	std::thread httpServerThread(run);
	//TailViewerUDPServer tailViewerServer;
	//FileConfig fconfig = FileConfig();
	//tailViewerServer.runTailViewerServer(fconfig);

	std::thread tailViewerServerThread(runTailViewerServer);
	//tailviewerThreadID = tailViewerServerThread.get_id();
	while (true)
	{
		
	}
	
		
	



	
	//int i = 0;
	//while (true)
	//{
	//	if(i%10000000 == 0)
	//		std::cout << i;
	//	i++;
	//}
	return 0;
}