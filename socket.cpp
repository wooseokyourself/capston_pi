#include "socket.hpp"

void
error_handling (char *message) {
    fputs (message, stderr);
    printf("\n");
    exit(1);
}

int
tcp_connect (int af, char *servip, unsigned short port) {
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
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr))
		< 0)
		return -1;
	return s;
}


/*
	.jpeg 파일을 입력받은 뒤 소켓을 생성하여 서버로 보내기.
	성공시 true 리턴, 실패시 false 리턴
*/
bool
SendImage (string fileName) {
	/*	소켓 프로그래밍 셋팅 */
	struct sockaddr_in server;
	int sock;
	char temp[20];
	int k, imgSize, status;
	int fd;
	sock = tcp_connect(AF_INET, IP, PORT);
	if (sock == -1) {
		printf("tcp_connect fail");
		exit(1);
	}

	char buf[MAXBUF], fileName[MAXLINE], *f;

	/*	파일 열기 */
	fd = open (fileName, O_RDONLY); // 파일 열기
	if (fd == -1) { //파일이 없다면
		error_handling ("File doesn't exist.");
	}

	/*	stat 함수를 이용하여 파일의 정보를 추출하여 그 정보들을 imgInfo에 저장 */
	struct stat imgInfo;
	stat (fileName, &imgInfo);
	imgSize = imgInfo.st_size;

	/*	서버에 fileName 전송  */
	strcpy (buf, fileName);
	send (sock, buf, 100, 0);

	/*	서버에 imgSize 전송 */
	send (sock, &imgSize, sizeof(int), 0); // 파일을 전송하기 전에 imgSize를 먼저 전송
	printf ("imgSize: %d\n", imgSize);

	/* 
		ssize_t sendfile (int out_fd, int in_fd, off_t *offset, size_t count);
		out_fd 는 쓰여질 파일(소켓), in_fd 는 읽을 파일이다. 즉 in_fd 파일을 out_fd 파일로 복사한다.
		offset이 NULL이 아니라면, offset은 in_fd에서 데이터를 읽기 시작할 시작점을 가리킨다. (즉 복사를 시작할 시점)
		NULL인 경우 in_fd의 처음부터 읽게 된다.
		count 는 복사할 바이트의 수이다.
		성공적으로 복사하였으면 out_fd 에 써넣은 바이트의 수를 반환한다.
	
	*/
	int sent = sendfile (sock, fd, NULL, imgSize);

	if (sent < imgSize) {
		printf ("sent < imgSize\n");
		return false;
	}
	else if (sent == imgSize) {
		printf("sent == imgSize\n");
		return true;
	}
	else {
		printf("sent > imgSize\n");
		return false;
	}
}