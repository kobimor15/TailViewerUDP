#include "TailViewerUDPServer.h"

namespace udp
{
	void TailViewerUDPServer::runTailViewerServer(const IConfig& config)
	{		
		// ------ Config by file ------
		udp::CommunicationInfo cmi1 = udp::CommunicationInfo(config.get_TVserver_ip(), config.get_TVserver_port());
		UDPListenerDriver udpListener;
		udpListener.initDriver(&cmi1);
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