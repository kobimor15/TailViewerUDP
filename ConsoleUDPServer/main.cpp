#include <iostream>
#include "..\TailViewerUDP\TailViewerUDPServer.h"
//#include "TailViewerUDPServer.h"
#include "..\TailViewerUDP\FileManager.h"
//#include <FileManager.h>

using namespace tail_viewer;
using namespace network;

int main()
{
	TailViewerUDPServer tailViewerServer;
	FileConfig fconfig = FileConfig();
	tailViewerServer.runTailViewerServer(fconfig);
}