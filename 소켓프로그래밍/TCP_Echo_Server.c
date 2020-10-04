#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// echo 서버
// 클라이언트가 전송하는 문자열 데이터를 그대로 재 전송하는 서버

#define BUF_SIZE 1024					// 전송 버퍼 사이즈
void error_handling(char *message);		// 에러 핸들링 함수

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;			// 서버, 클라이언트 소켓 파일 디스크립터
	char message[BUF_SIZE];				// 전송받는 메시지 버퍼
	int str_len, i;						// 작업에 사용되는 변수(문자열길이, 반복문변수)

	struct sockaddr_in serv_addr;		// 서버 소켓 정보
	struct sockaddr_in clnt_addr;		// 클라이언트 소켓 정보
	socklen_t clnt_adr_sz;				// 클라이언트 소켓 정보 길이

	if(argc != 2)						// 시작 시 입력값이 충분치 않을 경우
	{
		printf("Usage : %s <port>\n", argv[0]);	// port번호가 입력되지 않았다고 알리고 종료
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);	// 서버 소켓 생성
	if(serv_sock == -1)								// 실패 시 에러 핸들링
		error_handling("socket() error!");

	memset(&serv_addr, 0, sizeof(serv_addr));		// 서버 소켓 정보 구조체 초기화
	serv_addr.sin_family = AF_INET;					// 소켓 타입(IPv4)
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 주소 정보(IP)
	serv_addr.sin_port = htons(atoi(argv[1]));		// 포트 정보(port)

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)	// 소켓에 주소 할당
		error_handling("bind() error!");										// 실패 시 에러 핸들링

	if(listen(serv_sock, 5) == -1)												// 연결 가능 상태로 변경
		error_handling("listen() error!");										// 실패 시 에러 핸들링

	clnt_adr_sz = sizeof(clnt_addr);	// accept 사용을 위해 변수 값 채우기

	// 반복문을 사용하지 않을 시 단 한번의 접속만 받고 접속이 끝나면 종료
	// 반복문으로 accept부터 close까지 반복하여 여러 클라이언트를 받는다
	// 단, 한번에 한명만 받을 수 있다.

	for(i = 0;i < 5;i++)	// 총 5번 받을 수 있다
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_adr_sz);	// 연결 승인
		if(clnt_sock == -1)															// 실패 시 에러 핸들링
			error_handling("accept() error!");
		else
			printf("Connected client %d\n", i+1);									// 성공 시 알림

		// 클라이언트에서 연결을 끊을때까지 계속해서 받은 메시지를 재전송한다
		while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)	// 문장의 끝을 만날 때 까지 진행한다
		{
			printf("Message from client : %s", message);			// 클라이언트로부터 받은 메시지를 출력
			write(clnt_sock, message, str_len);						// echo는 받은 메시지를 바로 재전송
		}

		close(clnt_sock);	// 클라이언트 연결 종료
	}

	close(serv_sock);	// 서버 종료
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}