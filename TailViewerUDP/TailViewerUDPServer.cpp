#include "TailViewerUDPServer.h"

namespace tail_viewer
{
	void TailViewerUDPServer::runTailViewerServer(const IConfig& config)
	{		
		// ------ Config by file ------
		network::CommunicationInfo cmi1 = network::CommunicationInfo(config.getTVserverIP(), config.getTVserverPort());
		network::UDPListenerDriver udpListener;
		udpListener.initDriver(cmi1);
		FileManager logsFilesManager;

		while (true)
		{
			cout << "Server is waiting for message...";
			string msg = udpListener.receiveMessage();
			std::cout << "\nServer received: " << msg << "\n";

			//Create paths
			string rmtIP = udpListener.getRemoteIP();
			logsFilesManager.createLogFileDescriptor(rmtIP);
			logsFilesManager.writeMessageToFile(msg, rmtIP);
		}
	}
}