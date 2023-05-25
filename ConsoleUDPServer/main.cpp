#include <iostream>
//#include "TailViewerUDPServer.h"
#include "../TailViewerUDP/TailViewerUDPServer.h"
//#include <FileManager.h>
#include "../TailViewerUDP/FileManager.h"

using namespace tail_viewer;
using namespace network;

SOCKET tvSocketConsole;

int main()
{
	TailViewerUDPServer tailViewerServer(tvSocketConsole);
	FileConfig fconfig = FileConfig();
	tailViewerServer.initTVServer(fconfig);
	tailViewerServer.runTailViewerServer();
}