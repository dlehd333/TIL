#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct Phone {
	char name[20];
	char home[15];
	char hand[15];
};

int main()
{
	struct Phone phone[5];					// 전화번호 정보가 들어있는 구조체
	char serch[20];							// 검색값 입력용 버퍼
	int result = -1;						// 검색결과 해당 정보의 위치를 저장할 버퍼

	for (int i = 0; i < 5; i++)				// 5명의 전화번호 정보를 입력받는다
	{
		printf("이름을 입력하시오 : ");
		scanf("%s", phone[i].name);
		printf("집전화번호를 입력하시오 : ");
		scanf("%s", phone[i].home);
		printf("휴대폰번호를 입력하시오 : ");
		scanf("%s", phone[i].hand);
	}
	
	printf("\n");
	
	while (1)								// 이름에 따른 전화번호를 검색한다
	{
		result = -1;
		sprintf(serch, "");					// 입력버퍼 초기화

		printf("검색할 이름을 입력하세요 : ");
		scanf("%s", serch);					// 검색어 입력

		for (int i = 0; i < 5; i++)
		{
			if (strcmp(serch, phone[i].name) == 0)	// 문자열 비교
			{
				result = i;		// 해당 버퍼 위치를 저장
				break;
			}
		}

		if (result != -1)	// 저장된 버퍼의 위치가 있다면 출력
		{
			printf("집전화번호 : %s\n", phone[result].home);
			printf("휴대폰번호 : %s\n\n", phone[result].hand);
		}
		else
			printf("잘못된 입력입니다.\n\n");
	}
}