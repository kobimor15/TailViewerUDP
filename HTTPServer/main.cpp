#pragma once
#include <iostream>
//#include "TailViewerUDPServer.h"
#include "../TailViewerUDP/TailViewerUDPServer.h"
//#include <FileManager.h>
#include "../TailViewerUDP/FileManager.h"

#include <thread>

#include "server.h"
//#include "response.c"
//#include "request.c"
//#include "error.c"
//#include "defaults.c"

using namespace tail_viewer;
using namespace network;

int main()
{
	//std::thread threadObj(run);
	run();
	//std::cout << "hi";
	return 0;
}