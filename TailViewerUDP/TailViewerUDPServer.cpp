#include "TailViewerUDPServer.h"

namespace tail_viewer
{
	network::UDPListenerDriver udpListener;


	SOCKET TailViewerUDPServer::initTVServer(const IConfig& config) {
		network::CommunicationInfo cmi1 = network::CommunicationInfo(config.get_TVserver_ip(), config.get_TVserver_port());
		udpListener.initEthernetDriver(&cmi1);
		return udpListener.m_local_socket;
	}

	void TailViewerUDPServer::runTailViewerServer()
	{		
		FileManager logsFilesManager;

		while (true)
		{
			cout << "TailViewer Server is waiting for message...\n";
			string msg = udpListener.receiveMessage();

			//Check if need to reset server
			if (udpListener.m_resetServer)
			{
				FileConfig fconfig = FileConfig();
				this->initTVServer(fconfig);
				cout << "Server was reseted.\n";
				continue;
			}
			std::cout << "\nServer received: " << msg << "\n";

			//Create paths
			string rmtIP = udpListener.getRemoteIP();
			logsFilesManager.createLogFileDescriptor(rmtIP);
			logsFilesManager.writeMessageToFile(msg, rmtIP);
		}
	}
}