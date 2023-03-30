#include <iostream>
//#include "TailViewerUDPServer.h"
#include "../TailViewerUDP/TailViewerUDPServer.h"
//#include <FileManager.h>
#include "../TailViewerUDP/FileManager.h"
#include "server.h"
#include <thread>

using namespace tail_viewer;
using namespace network;

int main()
{
	//std::thread threadObj(run);
	run();
	return 0;
}