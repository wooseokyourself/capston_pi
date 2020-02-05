#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/sendfile.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

// #include "ImageProcessing.h"

#define MAXLINE  511
#define MAXBUF 1024

int
tcp_connect(int, char *, unsigned short);

void
error_handling (char *message) {
    fputs (message, stderr);
    printf("\n");
    exit(1);
}

int
main(int argc, char *argv[]) {

/* 소켓 프로그래밍 셋팅 */
	if (argc != 3) {
		printf("사용법 : %s server_ip port\n", argv[0]);
		exit(1);
	}
	struct sockaddr_in server;
	int sock;
	char buf[MAXBUF], fileName[MAXLINE], *f;
	char temp[20];
	int k, imgSize, status;
	int fileHandle;
	sock = tcp_connect(AF_INET, argv[1], atoi(argv[2]));
	if (sock == -1) {
		printf("tcp_connect fail");
		exit(1);
	}
/* 소켓 프로그래밍 셋팅 */



/*

	이 부분에서 영상을 촬영하고, 이미지프로세싱을 통해 최종적으로 사진 한 장을 얻기.

*/


/* 이하 if문이 true이면 파일을 서버로 업로드 */
	printf ("업로드할 파일 : ");
	scanf ("%s", fileName);       //파일 이름 입력
	fgets (temp, MAXLINE, stdin); //버퍼에 남은 엔터 제거
	fileHandle = open (fileName, O_RDONLY); // 파일 열기
	if (fileHandle == -1) { //파일이 없다면
		error_handling ("File doesn't exist.");
	}
		
	// buf 에 fileName 을 저장한다.
	strcpy (buf, fileName);
			
	/*	서버에 fileName 전송  */
	send (sock, buf, 100, 0);

	/*	stat 함수를 이용하여 파일의 정보를 추출하여 그 정보들을 imgInfo에 저장 */
	struct stat imgInfo;
	stat (fileName, &imgInfo);
	imgSize = imgInfo.st_size;


	/*	imgSize 전송 */
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
	int sent = sendfile (sock, fileHandle, NULL, imgSize); // 파일 송신
			

	if (sent < imgSize) {
		printf ("sent < imgSize\n");
	}
	else if (sent == imgSize) {
		printf("sent == imgSize\n");
	}
	else {
		printf("sent > imgSize\n");
	}

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
