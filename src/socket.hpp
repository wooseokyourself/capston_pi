#ifndef SOCKET
#define SOCKET

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define ASSERT assert

#define IP      "58.237.17.126"
#define PORT    9001

int
tcp_connect (int af, char* servip, unsigned short port);

void
SendBuffer (std::vector<unsigned char> data);

#endif
