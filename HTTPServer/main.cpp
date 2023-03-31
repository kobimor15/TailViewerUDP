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

void runTailViewerServer()
{
	TailViewerUDPServer tailViewerServer;
	FileConfig fconfig = FileConfig();
	tailViewerServer.runTailViewerServer(fconfig);
}

int main()
{
	std::thread httpServerThread(run);

	//TailViewerUDPServer tailViewerServer;
	//FileConfig fconfig = FileConfig();
	//tailViewerServer.runTailViewerServer(fconfig);

	std::thread tailViewerServerThread(runTailViewerServer);
	
	while (true)
	{
		if (m_flag == 1)
		{
			//tailViewerServerThread
		}
	}
	
		
		
		/*do {

	} while (true);*/

	
	//int i = 0;
	//while (true)
	//{
	//	if(i%10000000 == 0)
	//		std::cout << i;
	//	i++;
	//}
	return 0;
}