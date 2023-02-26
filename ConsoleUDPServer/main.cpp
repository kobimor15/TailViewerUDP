#include <iostream>
#include "TailViewerUDPServer.h"
#include <FileManager.h>

using namespace udp;

int main()
{
	TailViewerUDPServer tailViewerServer;
	FileConfig fc = FileConfig();
	tailViewerServer.runTailViewerServer(fc);
}