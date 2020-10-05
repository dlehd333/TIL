#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
void error_handling(char *message);
void read_childproc(int sig);

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int fds[2];

	pid_t pid;	// 자식 프로세스 ID를 저장하는 변수
	struct sigaction act;	// 시그널 등록시 호출 될 함수의 정보를 담은 구조체
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE];

	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	act.sa_handler = read_childproc;	// 핸들러로 지정할 함수 등록
	sigemptyset(&act.sa_mask);	// 나머지 구조체 변수는 0으로 초기화
	act.sa_flags = 0;

	state = sigaction(SIGCHLD, &act, 0); // SIGCHILD(자식프로세스 종료)에 대한 시그널 핸들링 등록

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen error");

	pipe(fds);	// 프로세스간 통신을 위한 파이프 생성
	pid = fork();	// 자식 프로세스 생성, 파이프 파일 디스크립터도 복사된다
	if(pid == 0)	// 자식프로세스가 전달값을 읽어 파일에 저장하는(쓰는) 구간
	{
		FILE* fp = fopen("echomsg.txt", "wt");
		char msgbuf[BUF_SIZE];
		int i, len;
		for(i = 0; i < 10; i++)
		{
			len = read(fds[0], msgbuf, BUF_SIZE);
			fwrite((void *)msgbuf, 1, len, fp);
		}
		fclose(fp);
		return 0;	// 저장 역할이 끝나면 반환값을 주고 종료된다
	}

	while(1)	// 클라이언트와 연결부분, 연결 이후 클라이언트 작업은 자식 프로세스에서 진행된다
	{
		adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		if(clnt_sock == -1)
			continue;
		else
			puts("new client connected...");
		pid = fork();	// 클라이언트 연결이 되면 자식 프로세스 생성한다, 서버소켓과 클라이언트 소켓도 복사된다
		if(pid == 0)	// 자식프로세스가 클라이언트와 데이터 연결을 진행한다
		{
			close(serv_sock);	// 클라이언트를 처리하는 자식 프로세스에는 서버소켓이 필요없다
			while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
			{
				write(clnt_sock, buf, str_len);	// 클라이언트로 echo
				write(fds[1], buf, str_len);	// 전달값을 저장하는 프로세스에 값 전달
			}
			close(clnt_sock);
			puts("client disconnected...");
			return 0;
		}
		else
			close(clnt_sock);	// 클라이언트 연결은 자식 프로세스로 넘겨서 클라이언트 소켓이 필요없다
	}
	close(serv_sock);
	return 0;
}

void read_childproc(int sig)
{
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);	// 자식프로세스의 종료여부를 검사
	if(WIFEXITED(status))	// 종료되었다면 전달값을 반환하고 프로세스를 소멸한다
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
