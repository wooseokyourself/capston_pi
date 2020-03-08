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
SendBuffer (struct protocol data) {
	/*	소켓 프로그래밍 셋팅 */
	struct sockaddr_in server;
	int sock;
	sock = tcp_connect(AF_INET, IP, PORT);
	if (sock == -1) {
		printf("tcp_connect fail");
		exit(1);
	}

	char buf[MAXBUF];

	/*	서버에 dataSize 전송 */  // 이 dataSize를 먼저 전송하는 것이 필요한 건지는 아직 모름.
	size_t dataSize = sizeof(struct protocol);
	send (sock, &dataSize, sizeof(dataSize), 0); // 구조체를 전송하기 전에 dataSize를 먼저 전송
	
	/*	서버에 struct protocol data 전송 */
	#ifdef DEBUG
	printf ("struct protocol data 전송중... 사이즈: %d\n", sizeof(data));
	#endif
	//	int sent = sendfile (sock, (struct protocol*) &data, sizeof(data));
	int sent = send (sock, (struct protocol*) &data, sizeof(data), 0);
	ASSERT (sent == sizeof (struct protocol));
	#ifdef DEBUG
	printf ("struct protocol data 전송완료. 전송된 사이즈: %d\n", sent);
	#endif
}
