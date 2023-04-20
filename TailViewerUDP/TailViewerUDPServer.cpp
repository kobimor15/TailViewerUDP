#include "TailViewerUDPServer.h"

namespace tail_viewer
{
	network::UDPListenerDriver udpListener;


	bool TailViewerUDPServer::initTVServer(const IConfig& config) {
		network::CommunicationInfo cmi1 = network::CommunicationInfo(config.get_TVserver_ip(), config.get_TVserver_port());
		bool valid = udpListener.initEthernetDriver(&cmi1);
		if (!valid) {
			tvSocket = 0;
			return false;
		}
		tvSocket = udpListener.m_local_socket;
		return true;
	}

	void Reset() {
		closesocket(udpListener.m_local_socket);
	}
	/*
	while(true){
				FileConfig fconfig = FileConfig();
				valid = this->initTVServer(fconfig);
				if(!valid) { 
					sleep(1 sec) 
					}
				else{
					break;
				}
	}
	
	*/
	void TailViewerUDPServer::runTailViewerServer()
	{		
		FileManager logsFilesManager;

		while (true)
		{
			//Check if need to reset server
			if (udpListener.m_resetServer)
			{
				//whileee
				FileConfig fconfig = FileConfig();
				this->initTVServer(fconfig);
				cout << "Server was reseted.\n";
				udpListener.m_resetServer = false;
				continue;
			}

			cout << "TailViewer Server is waiting for message...\n";
			string msg = udpListener.receiveMessage();
			std::cout << "\nServer received: " << msg << "\n";

			//Create paths
			string rmtIP = udpListener.getRemoteIP();
			logsFilesManager.createLogFileDescriptor(rmtIP);
			logsFilesManager.writeMessageToFile(msg, rmtIP);
		}
	}
}