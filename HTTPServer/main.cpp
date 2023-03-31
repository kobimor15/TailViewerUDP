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

int main()
{
	std::thread threadObj(run);
	int i = 0;
	TailViewerUDPServer tailViewerServer;
	FileConfig fconfig = FileConfig();
	tailViewerServer.runTailViewerServer(fconfig);

	//while (true)
	//{
	//	if(i%10000000 == 0)
	//		std::cout << i;
	//	i++;
	//}
	return 0;
}