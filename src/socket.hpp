#ifndef SOCKET
#define SOCKET

#include "common.hpp"

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

int
tcp_connect (int af, char* servip, unsigned short port);

void
SendBuffer (char* IP, unsigned short PORT, std::vector<unsigned char> data);

#endif
