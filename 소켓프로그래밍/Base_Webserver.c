// TCP 소켓 통신으로 웹페이지 출력
// 소켓 프로그래밍, 파일 입출력, 쓰레드 사용

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

#define TRUE 1
#define MAX_BUF 2047

void* client_handle(void*);	// 함수 선언부
void error_handling(char*);
const char webpage[] = "HTTP/1.1 200 OK\r\n"	// 수정되지 않도록 CONST로 저장
						"Server:Linux Web Server\r\n"
						"COntent-Type: text/html; charset=UTF-8\r\n\r\n"
						"<!DOCTYPE html>\r\n"
						"<html><head><title>My Web Page</title>\r\n"
						"<style>body {background-color:#FFFF00}</style></head>\r\n"
						"<body><center><h1>Hello world!!</h1><br>\r\n"
						"<img src=\"smartfactory.jpg\"></center></body></html>\r\n";
pthread_mutex_t mutex;			// 뮤텍스 락 동기화 사용

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	int option = TRUE;
	pthread_t t_id;

	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	pthread_mutex_init(&mutex, NULL);	// 뮤텍스 초기화

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);	// 소켓 생성
	if(serv_sock == -1)
		error_handling("socket() error!");
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)); // 소켓 재사용 옵션 활성화

	memset(&serv_adr, 0, sizeof(serv_adr));	// 서버 주소 구조체 초기화
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)& serv_adr, sizeof(serv_adr)) == -1)	// 소켓에 주소 연결
		error_handling("bind() error!");

	if(listen(serv_sock, 5) == -1)	// 소켓에 연결 가능하도록 활성화
		error_handling("listen() error!");

	clnt_adr_sz = sizeof(clnt_adr);

	while(1)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);	// 연결 대기 및 수락
		if(clnt_sock == -1)
			error_handling("accept() error!");

		pthread_create(&t_id, NULL, client_handle, (void*)&clnt_sock);	// 연결받으면 클라이언트 정보를 스레드로 분리
		pthread_detach(t_id);	// 쓰레드는 함수 수행 후 자동 종료되도록 설정

		printf("connected client id : %s\n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);	// 사용한 소켓은 종료
	pthread_mutex_destroy(&mutex);
}

void* client_handle(void* arg)	// 쓰레드의 메인, 클라이언트가 사용할 쓰레드 핸들러
{
	int clnt_sock = *((int*)arg);
	int str_len = 0;
	char msg[MAX_BUF];
	char imgbuf[700000];
	FILE* fdimg;

	while((str_len = read(clnt_sock, msg, MAX_BUF)) != 0)	// 클라이언트로 부터 입력
	{
		printf("sock %d : %s\n",clnt_sock, msg);

		pthread_mutex_lock(&mutex);		// 파일 포인터 사용 구간에 뮤텍스 동기화
		if(strncmp(msg, "GET /smartfactory.jpg", 21) == 0)	// 이미지를 요철할 경우
		{
			fdimg = fopen("./smartfactory.jpg", "rt");	// 파일포인터로 이미지 불러옴
			memset(&imgbuf, 0, 700000);					// 입력할 버퍼 초기화
			fread(imgbuf, 1, 700000, fdimg);			// 버퍼에 이미지 파일 내용 입력
			write(clnt_sock, imgbuf, sizeof(imgbuf));	// 파일 내용을 클라이언트에게 보냄
			fclose(fdimg);								// 파일포인터 종료
		}
		else	// 이미지를 요청한 경우를 제외한 경우
		{
			write(clnt_sock, webpage, sizeof(webpage));	// webpage를 보내줌
		}
		pthread_mutex_unlock(&mutex);	// 뮤텍스 동기화 종료
		memset(&msg, 0, MAX_BUF);		// 입력 버퍼 초기화
	}
	close(clnt_sock);
	return NULL;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}