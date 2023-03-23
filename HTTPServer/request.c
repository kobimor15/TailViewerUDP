#include <winsock2.h>
#include <stdio.h>
#include "server.h"

int get_request_type(char* buf)
{
    char retval[10] = { 0 };
    sscanf(buf, "%s ", &retval);

    if (!strcmp(retval, "GET"))
        return GET;
    else if (!strcmp(retval, "POST"))
        return POST;
    else if (!strcmp(retval, "PUT"))
        return PUT;
    else
        return RQ_UNDEF;
}

char* get_request_value(char* buf)
{
    char retval[100] = { 0 };

    sscanf(buf, "%s %s ", &retval, &retval);  // tee hee

    if (retval[strlen(retval) - 1] == '/')
        strcat(retval, "tv-server-config.html");

    return _strdup(retval);
}

char* getIPInput(char* buf)
{
    char retval[20] = { 0 };
    for (int i = strlen(buf) - 40; i < strlen(buf) - 7; i++)
    {
        if (buf[i] == 'i' && buf[i + 1] == 'p' && buf[i + 2] == '=')
        {
            int j = i;
            int k = 0;
            while (buf[j] != '&')
            {
                retval[k] = buf[j];
                k++;
                j++;
            }
            retval[j] = '\0';
            return retval;
        }
    }
    printf("ERROR-There is no valid IP.....");
    getch();
    exit(1);

}

char* getPortInput(char* buf)
{
    char retval[5] = { 0 };
    for (int i = strlen(buf) - 30; i < strlen(buf) - 4; i++)
    {
        if (buf[i] == 'p' && buf[i + 1] == 'o' && buf[i + 2] == 'r' && buf[i + 3] == 't' && buf[i + 4] == '=')
        {
            int j = i;
            int k = 0;
            while (buf[j] != '&')
            {
                retval[k] = buf[j];
                k++;
                j++;
            }
            retval[j] = '\0';
            return retval;
        }
    }
    printf("ERROR-There is no valid port.....");
    getch();
    exit(1);

}

REQUEST* GetRequest(SOCKET sock)
{
    REQUEST* request;
    int msg_len;
    char buf[REQUEST_SIZE];

    msg_len = recv(sock, buf, sizeof(buf), 0);
    //printf("Bytes Received: %d, message: %s from %s\n", msg_len, buf, inet_ntoa(client.sin_addr));

    request = malloc(sizeof(REQUEST));
    request->type = get_request_type(buf); // GET=1, POST=2, PUT=3, by the enum.
    request->value = get_request_value(buf); // gets the html file name
    request->length = msg_len;

    //KOBI
    if (request->type == POST)
    {
        request->ip_input = getIPInput(buf);
        request->port_input = getPortInput(buf);
    }

    return request;
}