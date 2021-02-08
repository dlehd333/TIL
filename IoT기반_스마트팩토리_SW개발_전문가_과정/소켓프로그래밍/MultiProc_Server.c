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
void read_childproc(int);

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;

	pid_t pid;	// 자식 프로세스 ID를 저장하는 변수
	struct sigaction act;	// 시그널 등록시 호출 될 함수의 정보를 담은 구조체
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE];
	if(argc != 2)
	{
		printf("usage : %s <port> \n", argv[0]);
		exit(1);
	}

	act.sa_handler = read_childproc;	// 핸들러로 지정할 함수 등록
	sigemptyset(&act.sa_mask);	// 나머지 구조체 변수는 0으로 초기화
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0);

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen error");

	while(1)
	{
		adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);

		if(clnt_sock == -1)
			continue;
		else
			puts("new client connected...");

		pid = fork();	// 클라이언트 연결시 자식프로세스 생성, 서버소켓과 클라이언트소켓도 복사

		if(pid == -1)
		{
			close(clnt_sock);
			continue;
		}

		if(pid == 0)	// 자식 프로세스 실행영역
		{
			close(serv_sock);	// 자식프로세스 - 서비스 제공에 clnt_sock만 사용
			while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
				write(clnt_sock, buf, str_len);

			close(clnt_sock);
			puts("client disconnected...");
			return 0;
		}
		else
			close(clnt_sock);	// 부모프로세스 - serv_sock만 사용
	}
	close(serv_sock);
	return 0;
}

void read_childproc(int sig)	// 기본적인 좀비 프로세서를 소멸하는 핸들러
{
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);
	if(WIFEXITED(status))
	{
		printf("removed proc id : %d\n", id);
		printf("child send : %d\n", WEXITSTATUS(status));
	}
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
