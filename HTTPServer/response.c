#include "server.h"

void updateHTMLFile(char* buf, char* data, char* nameOnHTML);

char* get_full_path(char* name)
{
	char filename[1024] = { 0 };
	getcwd(filename, 1024); //This func get the full path of this project on this pc.

	// "add '\\' if not have it
	if ((filename[strlen(filename)] != '\\') &&
		(name[strlen(name)] != '/') &&
		(name[strlen(name)] != '\\'))
	{
		strcat(filename, "\\");
	}

	// switch '/' chars to '\\'
	int i;
	for (i = 0; name[i]; i++)
		if (name[i] == '/')
			name[i] = '\\';

	// add the html file name to the project folder path
	strcat(filename, name);
	return _strdup(filename);
}

RESPONSE* GetResponse(REQUEST* request)
{
	RESPONSE* response;

	response = malloc(sizeof(RESPONSE));
	response->error = 0;
	response->filename = request->value; //put html file name from the GET request
	response->filepath = get_full_path(request->value); //get full path of the html file
	response->header = get_header(response);

	return response;
}

int SendResponse(SOCKET sock, RESPONSE* response)
{
	if (response->error) {
		send(sock, DEFAULT_ERROR_404, strlen(DEFAULT_ERROR_404), 0);
		return 1;
	}

	FILE* f = fopen(response->filepath, "rb");
	char buf[1024] = { 0 };
	int msg_len;

	if (!f) {
		send(sock, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n", 57, 0);
		return 1;
	}

	send(sock, response->header, strlen(response->header), 0);

	int result = 0;
	while ((result = fread(buf, 1, 1024, f)) > 0)
	{
		//Get ip and port from config.cfg file:
		FILE* cfgFile;
		cfgFile = fopen("C:\\logs\\config\\config.cfg", "r");
		if (cfgFile == NULL) {
			printf("Error opening file\n");
			getchar();
			exit(1);
		}
		char cfgFileIP[30], cfgFilePort[10];
		fgets(cfgFileIP, 30, cfgFile);
		cfgFileIP[strlen(cfgFileIP) - 1] = cfgFileIP[strlen(cfgFileIP)]; // remove '\n'
		fgets(cfgFilePort, 10, cfgFile);
		fclose(cfgFile);


		//Update the html content from the config.cfg file:
		char* HTML_IP = "ipvalue";
		char* HTML_PORT = "portvalue";
		char* tempBuffer = malloc(sizeof(char) * 1024);
		strcpy(tempBuffer, buf);
		updateHTMLFile(tempBuffer, cfgFileIP, HTML_IP);
		updateHTMLFile(tempBuffer, cfgFilePort, HTML_PORT);
		strcpy(buf, tempBuffer);
		free(tempBuffer);


		//Send the response:
		msg_len = send(sock, buf, result, 0);

		if (msg_len == SOCKET_ERROR) {
			//error_live("send()");
			printf("Error sending data, reconnecting...\n");
			closesocket(sock);
			return -1;
		}
		else if (!msg_len)
		{
			printf("Client closed connection\n");
			closesocket(sock);
			return 0;
			//WSACleanup();
		}
	}

	printf("Served file: %s\n", response->filepath);

	return 1;
}

void updateHTMLFile(char* buf, char* data, char* nameOnHTML)
{
	char* placeholder_start = strstr(buf, nameOnHTML);
	if (placeholder_start != NULL) {
		char* placeholder_end = placeholder_start + strlen(nameOnHTML);
		size_t prefix_size = placeholder_start - buf;
		size_t suffix_size = strlen(placeholder_end);
		size_t data_size = strlen(data);
		char* new_data = (char*)malloc(prefix_size + data_size + suffix_size + 1);
		memcpy(new_data, buf, prefix_size);
		memcpy(new_data + prefix_size, data, data_size);
		memcpy(new_data + prefix_size + data_size, placeholder_end, suffix_size + 1);
		strcpy(buf, new_data);
		free(new_data);
	}
	else {
		///DO NOTHING
	}
}