#include "TailViewerUDPServer.h"

namespace tail_viewer
{
	network::UDPListenerDriver udpListener;

	SOCKET TailViewerUDPServer::init(const IConfig& config) {
		network::CommunicationInfo cmi1 = network::CommunicationInfo(config.get_TVserver_ip(), config.get_TVserver_port());
		udpListener.initDriver(&cmi1);
		return udpListener.m_local_socket;
	}
	void TailViewerUDPServer::runTailViewerServer()
	{		
		// ------ Config by file ------

		FileManager logsFilesManager;

		while (true)
		{
			cout << "Server is waiting for message...";
			string msg = udpListener.receiveMessage();
			std::cout << "\nServer received: " << msg << "\n";
			/*
			if(reset_Flag) {
				init(new_config);
				continue;
			}
			*/
			//Create paths
			string rmtIP = udpListener.getRemoteIP();
			logsFilesManager.createLogFileDescriptor(rmtIP);
			logsFilesManager.writeMessageToFile(msg, rmtIP);
		}
	}
}