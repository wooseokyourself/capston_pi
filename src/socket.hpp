#ifndef SOCKET
#define SOCKET

#include "common.hpp"
#include "vision.hpp"

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXBUFSIZE 512

ssize_t
Recv (int sock, const void *buf, ssize_t size, ssize_t unit);

int
tcp_connect (int af, char* servip, unsigned short port);

bool
recv_terminate_flag (const int& sock);

bool
recv_notification (const int& sock);

void
SendBuffer (char* IP, unsigned short PORT, std::vector<unsigned char>& vec, int camId);

#endif
