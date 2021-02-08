#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// echo 서버의 클라이언트

#define BUF_SIZE 1024	// 버퍼 크기
void error_handling(char *message);		// 에러 핸들링 함수

int main(int argc, char* argv[])
{
	int sock;	// 클라이언트의 소켓 파일 디스크립터
	char message[BUF_SIZE];		// 전송할 메시지의 버퍼
	int str_len, recv_len, recv_cnt;	// 작업에 사용되는 변수(문자열 길이, 전송받은 문자열 길이 등)
	struct sockaddr_in serv_adr;	// 접속한 서버의 주소 정보

	if(argc != 3)	// 시작 시 입력값이 충분치 않을 경우
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);	// ip와 port정보를 달라고 하고 종료
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);		// 클라이언트 소켓 생성
	if(sock == -1)		// 실패 시 에러 핸들링
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));		// 서버 주소 정보 구조체 초기화
	serv_adr.sin_family = AF_INET;		// 소켓 타입(IPv4)
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);	// 주소 정보(IP)
	serv_adr.sin_port = htons(atoi(argv[2]));		// 포트 정보(port)

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)	// 서버와 연결
		error_handling("connect() error");		// 실패 시 에러 핸들링
	else
		puts("Connected...............");		// 성공시 메시지 출력

	// TCP 데이터 송수신에는 경계가 존재하지 않는다
	// 서버는 데이터의 경계를 구분하지 않고 수신된 데이터를 그대로 전송할
	// 의무만 갖는다. write를 두번 쓰던 세번 쓰던 문제되지 않는다.
	// 클라이언트는 문장 단위로 데이터를 송수신하기 때문에 데이터의 경계를
	// 구분하여야 한다. 때문에 아래와 같은 송수신 방식은 문제가 된다.
	// wirte(sock, message, strlen(message));
	// str_len = read(sock, message, BUF_SIZE -1);
	// message[str_len] = 0;
	// printf("Message from server : %s", message);

	while(1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);	// 전송할 메시지를 버퍼에 입력받는다

		if(!strcmp(message,"q\n") || !strcmp(message, "Q\n"))	// q, Q를 입력할 경우 서버와의 연결을 종료한다
			break;

		// write함수 호출을 통해서 전송한 데이터의 길이만큼 읽어들이기 위한 반복문의
		// 삽입이 필요하다. 이것이 TCP를 기반으로 데이터를 구분지어 읽어들이는데
		// 부가적으로 필요한 구분이다

		str_len = write(sock, message, strlen(message));	// 버퍼에 입력된 값을 전송하고 그 길이를 저장해둔다

		recv_len = 0;		// 전체 전송 받은 데이터의 길이가 들어갈 변수

		while(recv_len < str_len)	// 전체 전송 받은 데이터의 길이가 전송한 데이터의 길이와 같아질 때까지 반복
		{
			// 서버에서 전송된 값을 전체 전송받은 데이터의 양 부터 받고, 그 길이를 저장한다
			recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
			if(recv_cnt == -1)		// 읽기가 실패할 경우 에러 핸들링
				error_handling("read() error");
			recv_len += recv_cnt;	// 전송된 값의 길이를 전송된 값의 전체 길이를 저장하는 변수에 더한다
		}

		message[recv_len] = 0;		// 문자열의 끝에 NULL 처리
		printf("Message from server : %s", message);	// 입력받은 전체 문자열 출력
	}

	close(sock);	// 연결 종료

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
