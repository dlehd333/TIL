#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 사용자에게 암호를 입력받아
// 암호의 유효성을 테스트하는 문제
// 암호에는 소문자, 대문자, 숫자가 전부 있어야함

int main()
{
	// 암호를 입력받을 동적배열 및 체크용 bool 변수
	char* pw = malloc(50);
	bool check[3] = { false, false, false };

	// 유용한 암호를 입력받을 때까지 무한루프
	while (true)
	{
		// 체크용 bool변수 초기화
		for(int i = 0; i < sizeof(check);i++)
			check[i] = false;

		// 암호 입력
		printf("암호를 생성하시오:");
		scanf("%s", pw);

		// 암호의 유용성 검사
		for (int i = 0; i < strlen(pw);i++)
		{
			if (pw[i] >= '0' && pw[i] <= '9')		// 숫자
				check[0] = true;
			else if (pw[i] >= 'A' && pw[i] <= 'Z')	// 대문자
				check[1] = true;
			else if (pw[i] >= 'a' && pw[i] <= 'z')	// 소문자
				check[2] = true;
		}

		// 검사결과를 모두 만족할 경우 성공 메시지 및 무한루프 탈출
		// 아닐경우 실패 메시지 출력 후 무한루프 지속
		if (check[0] && check[1] && check[2])
		{
			printf("적정한 암호입니다\n");
			break;
		}
		else
			printf("숫자,대문자,소문자를 섞어서 암호를 다시 만드세요!\n");
	}

	// 동적할당 해제
	free(pw);
}