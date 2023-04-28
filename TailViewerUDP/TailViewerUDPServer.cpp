#include "TailViewerUDPServer.h"
#include <thread> //for sleep
#include <chrono> //for sleep

namespace tail_viewer
{
	network::UDPListenerDriver udpListener;

	/* Implementation of the function that declared at: HTTPServer->server.h */
	extern "C"
	{
		void ResetTVServer() {
			closesocket(udpListener.m_local_socket);
		}
	}

	/* Initializes TV server and runs it */
	void TailViewerUDPServer::runTailViewerServer()
	{		
		FileManager logsFilesManager;

		while (true)
		{
			//Check if need to reset server (at first time, get reset on default)
			if (udpListener.m_resetServer)
			{
				while(true) ////ADDED WITH DOR
				{
					FileConfig fconfig = FileConfig();
					bool initSucceeded = this->initTVServer(fconfig);
					if (!initSucceeded)
						std::this_thread::sleep_for(std::chrono::seconds(3));
					else
						break;
				}
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

	/* Initializes ethernet driver, set 'tvSocket' and returns true if succeeded */
	bool TailViewerUDPServer::initTVServer(const IConfig& config) {
		network::CommunicationInfo cmi1 = network::CommunicationInfo(config.get_TVserver_ip(), config.get_TVserver_port());
		bool valid = udpListener.initEthernetDriver(&cmi1);
		if (!valid) {
			*tvSocketLOC = INVALID_SOCKET;
			return false;
		}
		*tvSocketLOC = udpListener.m_local_socket;
		return true;
	}
}