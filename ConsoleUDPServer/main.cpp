#include <iostream>
//#include "TailViewerUDPServer.h"
#include "../TailViewerUDP/TailViewerUDPServer.h"
//#include <FileManager.h>
#include "../TailViewerUDP/FileManager.h"

using namespace tail_viewer;
using namespace network;

int main()
{
	TailViewerUDPServer tailViewerServer;
	FileConfig fconfig = FileConfig();
	tailViewerServer.runTailViewerServer(fconfig);
}