#include "socket.hpp"

int
tcp_connect (int af, char* servip, unsigned short port) {
	printf ("tcp_connect called\n");
	struct sockaddr_in servaddr;
	int s;
	// Create a socket.
	printf ("create a socket\n");
	if ((s = socket(af, SOCK_STREAM, 0)) < 0)
		return -1;
	memset (&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = af;
	inet_pton (AF_INET, servip, &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	// Connection request
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		return -1;

	printf ("connection success!\n");
	return s;
}

/*
	Returns false if connection fails.
	Otherwise, returns true.
*/
bool
SendBuffer (char* IP, unsigned short PORT, std::vector<unsigned char> vec) {
	// Set socket.
	struct sockaddr_in server;
	int sock;
	sock = tcp_connect(AF_INET, IP, PORT);
	if (sock == -1) {
		printf("tcp_connect fail");
		return false;
	}

	int sent;

	// Send @vec.size()
	size_t bufSize = vec.size();
	sent = send (sock, (size_t *) &bufSize, sizeof(bufSize), 0);
	ASSERT (sent == sizeof(vec.size()));

	// Send @vec
	sent = 0;
	for (int i=0; i<vec.size(); i++) {
		sent += send (sock, &vec[i], sizeof(unsigned char), 0);
	}
	ASSERT (sent == vec.size());

	return true;
}
