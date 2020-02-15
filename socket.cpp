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
	성공시 true 리턴, 실패시 false 리턴
*/
void
SendBuffer (struct protocol data) { // 원래 인자는 string fileName 이었음.
	/*	소켓 프로그래밍 셋팅 */
	struct sockaddr_in server;
	int sock;
	sock = tcp_connect(AF_INET, IP, PORT);
	if (sock == -1) {
		printf("tcp_connect fail");
		exit(1);
	}

	char buf[MAXBUF];

	/*	서버에 dataSize 전송 */
	size_t dataSize = sizeof(struct protocol);
	send (sock, &dataSize, sizeof(dataSize), 0); // 구조체를 전송하기 전에 dataSize를 먼저 전송
	printf ("dataSize: %d\n", dataSize);
	
	/*	서버에 struct protocol data 전송 */
	int sent = sendfile (sock, (struct protocol*) &data, sizeof(data));
	ASSERT (sent == dataSize);

	return true;
}