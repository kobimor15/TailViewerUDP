#include "server.h"

//void run(char* ip, unsigned int* port, int* flag)
void run()
{
	int addr_len;
	struct sockaddr_in local, client_addr;

	SOCKET sock, msg_sock;
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR)
		error_die("WSAStartup()");

	//Semaphore init:
	m_semaphore = CreateSemaphore(NULL, 1, 1, NULL);
	if (m_semaphore == NULL)
	{
		error_die("Error - Semaphore initailization failed.");
	}

	// Fill in the address structure
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(DEFAULT_PORT);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
		error_die("socket()");

	if (bind(sock, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)
		error_die("bind()");

listen_goto:

	if (listen(sock, 10) == SOCKET_ERROR)
		error_die("listen()");

	printf("Waiting for connection...\n");

	int count = 0;


	WaitForSingleObject(m_semaphore, INFINITE);
	m_flag = 0; /////////////////
	ReleaseSemaphore(m_semaphore, 1, NULL);




	forever
	{
		addr_len = sizeof(client_addr);
		msg_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);

		if (msg_sock == INVALID_SOCKET || msg_sock == -1)
			error_die("accept()");

		char strAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &client_addr.sin_addr, strAddress, sizeof(strAddress));
		printf("Connected to %s:%d\n", strAddress, htons(client_addr.sin_port));

		REQUEST* request = GetRequest(msg_sock);
		
		if (request->length == 0)
			continue;
		
		if (request->type == POST)
		{
			printf("\nReceived from client: IP = %s , port = %u\n", request->ip_input, request->port_input);


			WaitForSingleObject(m_semaphore, INFINITE);
			m_flag = 1; //if flag is on, so the TV server need to restart itself, because ip and port updated.
			ReleaseSemaphore(m_semaphore, 1, NULL);
		
		}
		else
			printf("\nClient requested %d %s\n", request->type, request->value);


		RESPONSE* response = GetResponse(request);
		int sent = SendResponse(msg_sock, response);

		closesocket(msg_sock);

		if (sent == 0)
			break;
		else if (sent == -1)
			goto listen_goto;

	}

	WSACleanup();
}