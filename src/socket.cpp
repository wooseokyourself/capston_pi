#include "socket.hpp"

ssize_t
Recv (int sock, const void *buf, ssize_t size, ssize_t unit) {
	ssize_t recvd = 0;
	ssize_t yet = size;
	while (recvd < size) {
		if ( 0 < yet && yet < MAXBUFSIZE )  /* 아직 받지않은 데이터가 MAXBUFSIZE보다 작은 경우 */
			recvd += recv (sock, (void *) (buf + recvd/unit), yet, 0);
		else /* 받아야 할 데이터가 MAXBUFSIZE보다 큰 경우 */
			recvd += recv (sock, (void *) (buf + recvd/unit), MAXBUFSIZE, 0);

		yet = size - recvd;
	}
	return recvd;
}


int
tcp_connect (int af, char* servip, unsigned short port) {
	struct sockaddr_in servaddr;
	int s;
	// Create a socket.
	if ((s = socket(af, SOCK_STREAM, 0)) < 0)
		return -1;
	memset (&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = af;
	inet_pton (AF_INET, servip, &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	// Connection request
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		return -1;

	return s;
}

bool
recv_notification (int sock) {
	// Get notification to take a picture.
	bool notification = false;
	int recvd = Recv (sock, &notification, sizeof(notification), sizeof(bool));
	ASSERT (recvd == sizeof(notification));

	return notification;
}

bool
recv_terminate (int sock) {
	bool terminate;
	int recvd = Recv (sock, &terminate, sizeof(terminate), sizeof(bool));
	ASSERT (recvd == sizeof(terminate));
	return terminate;
}

/*
	Returns false if connection fails.
	Otherwise, returns true.
*/
void
SendBuffer (char* IP, unsigned short PORT, std::vector<unsigned char>& vec, int camId) {
	// Set socket.
	struct sockaddr_in server;
	int sock;
	sock = tcp_connect(AF_INET, IP, PORT);
	ASSERT (sock != -1);

	int sent;
	
	// Send camId
	sent = send (sock, &camId, sizeof(int), 0);
	ASSERT (sent == sizeof(int));

	while (true) {
		if (recv_terminate (sock))
			break;

		// Receive notification
		if (recv_notification(sock)) {
			printf ("Got notification! take a picture.\n");
			vec = ImageProcessing(); // Take a picture.
		}
		else // terminate
			break;

		// Send @vec.size()
		sent = 0;
		size_t bufSize = vec.size();
		sent = send (sock, (size_t *) &bufSize, sizeof(bufSize), 0);
		ASSERT (sent == sizeof(vec.size()));

		// Send @vec
		sent = 0;
		for (int i=0; i<vec.size(); i++) {
			sent += send (sock, &vec[i], sizeof(unsigned char), 0);
		}
		ASSERT (sent == vec.size());
	}
}
