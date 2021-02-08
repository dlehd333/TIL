#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char*);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char* argv[])
{
	int sock;
	pid_t pid;	// 자식 프로세스 ID를 저장하는 변수
	char buf[BUF_SIZE];
	struct sockaddr_in serv_adr;

	if(argc != 3)
	{
		printf("usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect error!");

	pid = fork();	// 연결 시 자식 프로세스 생성, 수신과 발신을 개별로 수행한다

	if(pid == 0) write_routine(sock, buf);	// 데이터 발신 담당 함수(프로세스)
	else	read_routine(sock, buf);	// 데이터 수신 담당 함수(프로세스)

	close(sock);
	return 0;
}

void read_routine(int sock, char* buf)
{
	while(1)	// 데이터 수신 담당
	{
		int str_len = read(sock, buf, BUF_SIZE);
		if(str_len == 0)
			return;

		buf[str_len] = 0;
		printf("Message from server : %s", buf);
	}
}

void write_routine(int sock, char* buf)
{
	while(1)	// 데이터 발신 담당
	{
		fgets(buf, BUF_SIZE, stdin);
		if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
		{
			shutdown(sock, SHUT_WR);
			return;
		}
		write(sock, buf, strlen(buf));
	}
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
