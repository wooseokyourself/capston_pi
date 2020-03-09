#include "socket.hpp"

int
tcp_connect (int af, char* servip, unsigned short port) {
	struct sockaddr_in servaddr;
	int  s;
	// 소켓 생성
	if ((s = socket(af, SOCK_STREAM, 0)) < 0)
		return -1;
	// 채팅 서버의 소켓주소 구조체 servaddr 초기화
	bzero ((char *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = af;
	inet_pton (AF_INET, servip, &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	// 연결요청
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		return -1;
	return s;
}


/*
	struct protocol data 파일을 입력받은 뒤 소켓을 생성하여 서버로 보내기.
*/
void
SendBuffer (std::vector<unsigned char> vec) {
	/*	소켓 프로그래밍 셋팅 */
	struct sockaddr_in server;
	int sock;
	sock = tcp_connect(AF_INET, IP, PORT);
	if (sock == -1) {
		printf("tcp_connect fail");
		exit(1);
	}

	int sent;
	char buf[MAXBUFSIZE];

	/*	서버에 vec.size() 전송 */
	size_t bufSize = vec.size();
	#ifdef DEBUG
	printf ("vec.size() 전송중... 전송할 버퍼 사이즈: %d\n", sizeof(bufSize));
	#endif
	sent = send (sock, (size_t *) &bufSize, sizeof(bufSize), 0);
	ASSERT (sent == sizeof (vec.size()));

	/*	서버에 vec 전송 */
	#ifdef DEBUG
	printf ("vec 전송중... 전송할 버퍼 사이즈: %d\n", vec.size() * sizeof(unsigned char));
	#endif
	sent = 0;
	
	
	for (int i=0; i<vec.size(); i++) {
		sent += send (sock, &vec[i], sizeof(unsigned char), 0);
		// printf ("[%d] send Value: %d\n", i, data.buf[i]);
	}

	// sent = send (sock, &data.buf[0], bufSize, 0);

	ASSERT (sent == vec.size() * sizeof(unsigned char));
	#ifdef DEBUG
	printf ("data.buf 전송완료.\n");
	#endif
}
