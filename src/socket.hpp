#ifndef SOCKET
#define SOCKET

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <cstring>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include "protocol.hpp"

#define ASSERT assert

#define MAXLINE 511
#define MAXBUF	512

#define IP      "58.237.17.126"
#define PORT    9051

int
tcp_connect (int af, char* servip, unsigned short port);

void
SendBuffer (struct protocol data);

#endif
