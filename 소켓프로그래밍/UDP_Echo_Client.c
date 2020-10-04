#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// udp 클라이언트

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char* argv[])
{
	// UDP는 연결의 개념이 없어, 데이터를 주고받을 떄 마다 목적지의 정보를 받거나 전달한다
	// 그래서 소켓을 하나만 생성한다
	int sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t adr_sz;
	struct sockaddr_in serv_adr, from_adr;

	if(argc != 3)	// ip, port 정보의 유무 검사
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_DGRAM, 0);	// 소켓 생성
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));			// 목적지(서버)의 주소 정보 구조체 초기화
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	while(1)
	{
		fputs("Insert message(q to quit) : ", stdout);
		fgets(message, sizeof(message), stdin);					// 전달할 데이터를 입력받음
		if(!strcmp(message, "q\n")|| !strcmp(message, "Q\n"))	// q, Q가 입력되면 연결 종료
			break;

		// UDP는 연결의 개념이 없어, 데이터를 전송할 때 마다 목적지의 정보를 전달해야 한다
		sendto(sock, message, strlen(message), 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

		// UDP는 데이터의 경계가 존재하기 때문에 한번의 recvfrom 함수호출을 통해 하나의 메시지를 완전히 읽어들인다
		// UDP는 데이터 수신 시 전송지 정보가 함께 전달된다
		adr_sz = sizeof(from_adr);
		str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&from_adr, &adr_sz);

		message[str_len] = 0;							// 문자열 끝 NULL 처리
		printf("Message from server : %s", message);	// 전달받은 문자열 출력
	}
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
