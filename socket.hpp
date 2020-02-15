#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <string>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/sendfile.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include "protocol.hpp"

#define MAXLINE 511
#define MAXBUF	1024

#define IP      "58.237.17.126"
#define PORT    9001

int
tcp_connect (int af, char* servip, unsigned short port);

void
SendBuffer (struct protocol data);