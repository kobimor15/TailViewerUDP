#include "server.h"

int get_request_type(char* buf)
{
    char retval[10] = { 0 };
    sscanf(buf, "%9s ", &retval);

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
    char retval[1024] = { 0 };
    sscanf(buf, "%s %s ", &retval, &retval);  // tee hee
    if (retval[strlen(retval) - 1] == '/')
        strcat(retval, "tv-server-config.html");

    return _strdup(retval);
}

char* getIPInput(char* buf)
{
    char* ip_start = strstr(buf, "ip=");
    if (ip_start != NULL) 
    {
        char* ip_end = strchr(ip_start, '&');
        if (ip_end == NULL) 
            ip_end = buf + strlen(buf);
        char ip[22];
        int length = ip_end - ip_start - 3;
        strncpy(ip, ip_start + 3, length);
        ip[length] = '\0';

        return ip;
    }
}

unsigned int getPortInput(char* buf)
{
    char* port_str = strstr(buf, "port=");
    if (port_str != NULL) 
    {
        unsigned int port_val;
        if (sscanf(port_str, "port=%u", &port_val) == 1)
            return port_val;
        else
            printf("Failed to extract port value\n");
    }
    else
        printf("No 'port' parameter found\n");
}

REQUEST* GetRequest(SOCKET sock)
{
    REQUEST* request;
    int msg_len;
    char buf[REQUEST_SIZE];

    msg_len = recv(sock, buf, sizeof(buf), 0);

    request = malloc(sizeof(REQUEST));
    request->type = get_request_type(buf); // GET=1, POST=2, PUT=3, by the enum.
    request->value = get_request_value(buf); // gets the html file name
    request->length = msg_len;

    //Get ip and port:
    if (request->type == POST)
    {
        strcpy(request->ip_input, getIPInput(buf));
        request->port_input = getPortInput(buf);
    }
    return request;
}