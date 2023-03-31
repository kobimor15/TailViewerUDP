#include "server.h"

void error_live(const char *s)
{
    fprintf(stderr, "Error: %s failed with error %d\n", s, WSAGetLastError());
    WSACleanup();
}

void error_die(const char *s)
{
    error_live(s);
    CloseHandle(m_semaphore); //added for the semaphore
    exit(EXIT_FAILURE);
}