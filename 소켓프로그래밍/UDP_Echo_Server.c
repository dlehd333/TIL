#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char* argv[])
{
	// UDP는 연결의 개념이 없어, 데이터를 주고받을 떄 마다 목적지의 정보를 받거나 전달한다
	// 그래서 소켓을 하나만 생성한다

	int serv_sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	if(argc != 2)	// port 정보의 유무를 검사
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_DGRAM, 0);			// 소켓의 생성, UDP를 사용하므로 SOCK_DGRAM을 사용
	if(serv_sock == -1)
		error_handling("UDP socket ceration error");

	memset(&serv_adr, 0, sizeof(serv_adr));				// 서버의 주소 정보 초기화
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)	// 주소를 할당한다
		error_handling("bind() error");

	// UDP는 연결의 개념이 없어, TCP처럼 listen, accept의 과정이 없다
	printf("UDP Server Start!\n");

	while(1)
	{
		// UDP는 데이터 수신 시 전송지 정보가 함께 전달된다
		// UDP는 연결의 개념이 없어, 데이터의 전송지가 둘 이상이 될 수 있다
		// 데이터 수신 후 전송지가 어디인지 확인할 필요가 있다
		clnt_adr_sz = sizeof(clnt_adr);
		str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		printf("Receive From Message");

		// UDP는 연결의 개념이 없어, 데이터를 전송할 때 마다 목적지의 정보를 전달해야 한다
		sendto(serv_sock, message, str_len, 0, (struct sockaddr*)&clnt_adr, clnt_adr_sz);	// 전달받은 문자열을 바로 echo

		printf("Sent To Message : %s", message);
	}
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
