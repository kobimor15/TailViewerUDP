#include "Client.h"
#include <string>
#include <fstream> //for files
#include <sstream>

#define CLIENT_IP "101.156.216.111"
#define CLIENT_PORT 9876

int main()
{
	static int m_number_for_debug = 1; // ---Just for debugging
	
	/* Get the server ip and port from the configuration file */

	/* Config file should be at C:\\logs\config, and should look like: ip_address \n port */
	std::ifstream configFile("C:\\logs\\config\\config.cfg");
	std::string serverIP, serverPortString;
	if (configFile.good())
	{
		getline(configFile, serverIP);
		getline(configFile, serverPortString);
	}
	unsigned int ServerPort = stoi(serverPortString);
	configFile.close();

	udp::CommunicationInfo comInfo = udp::CommunicationInfo(CLIENT_IP, serverIP, CLIENT_PORT, ServerPort);
	udp::Client client;
	client.init(&comInfo);

	while (true)
	{
		std::cout << "Press any key to send message.\n";
		getchar();
		
		std::stringstream sstream;

		/*sstream << "CLIENT_SENDING_MSG" << m_number_for_debug << "101.156.216.5629876";*/
		sstream << "CLIENT_SENDING_MSG" << m_number_for_debug << CLIENT_IP << CLIENT_PORT; //template is: CLIENT_SENDING_MSG101.156.216.5629876
		client.sendMessageToServer(sstream.str());
		m_number_for_debug++;
		/*client.sendMessageToServer("CLIENT_SENDING_MSG101.156.216.5629876");*/
		

		std::cout << "Message sent.\n";
	}
	std::cout << "Client sent the message";
}