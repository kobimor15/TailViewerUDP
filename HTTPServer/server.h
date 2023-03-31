#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <WS2tcpip.h> //for inet_pton function
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define forever while(1)

typedef struct {
    int  type;
    char* value;
    int length;
    char ip_input[22];
    unsigned int port_input;
} REQUEST;

typedef struct {
    char* header;
    char* filename, * filepath;
    int  error;
} RESPONSE;

#define REQUEST_SIZE 4096
#define DEFAULT_PORT 80

#undef DELETE
enum { RQ_UNDEF, GET, POST, PUT } response_types;

extern const char* DEFAULT_ERROR_404;

extern char* get_header(RESPONSE*);
extern REQUEST* GetRequest(SOCKET);
extern RESPONSE* GetResponse(REQUEST*);
extern int SendResponse(SOCKET, RESPONSE*);
extern void error_live(const char*);
extern void error_die(const char*);
extern void run(char* ip, unsigned int* port, int* flag);


#ifdef __cplusplus
}
#endif