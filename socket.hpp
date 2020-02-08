#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/sendfile.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLINE 511
#define MAXBUF	1024

#define IP      "58.237.17.126"
#define PORT    9001

void
error_handling (char *);

int
tcp_connect (int, char *, unsigned short);

bool
SendImage (string);