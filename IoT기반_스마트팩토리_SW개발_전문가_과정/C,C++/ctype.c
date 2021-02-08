#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

// 텍스트 파일의 이름을 입력받아서(임의의파일은 대소문자 혼합파일)
// 파일내의 문자들에 대하여 영문자의 개수를 문자별로 세서 출력
// 단, 문자의 개수를 셀 때는 대소문자를 구별하지 않는다.

int main()
{
	FILE* fp = fopen("c:\\_temp\\file3.txt", "r");	// 파일 불러오기
	char str;										// 검사할 문자를 입력받을 버퍼
	int countAlphabet[26] = { 0, };					// 알파멧의 숫자를 입력할 배열

	while (1)
	{
		str = fgetc(fp);					// 문자 하나 읽기
		if (str == EOF) break;				// 파일의 끝의 도달할 경우 검색 종료

		// -----------------------------------------------------------------------------------
		// C언어 문자 조작 관련 함수
		// isalpha(int c); - 알파벳이 아니면 0리턴, 대문자는 1리턴, 소문자는 2리턴
		// isupper(int c); islower(int c); isdigit(int c); - 아니라면 0리턴, 맞다면 정수 리턴
		// toupper(int c); tolower(int c); - 대문자라면 소문자를, 소문자라면 대문자를 리턴한다
		// 바꿔줄 대문자나 소문자가 아니라면 입력받은 문자를 그대로 리턴한다
		// 참고로 인자로 들어간 int c는 모두 아스키코드값임을 명심하자
		// 이 외에도 여러 종류의 문자 조작 관련 함수가 ctype.h에 있다
		// -----------------------------------------------------------------------------------

		printf("%c", str);

		if (isalpha(str))					// 알파벳이라면
		{
			str = tolower(str);				// 카운트가 편하게 소문자로 통일하고
			countAlphabet[str - 'a']++;		// 해당 아스키 코드에 맞게 배열에 카운트해준다
		}
	}

	printf("\n");

	for (int i = 0; i < 26;i++)
	{
		printf("%c:%d ", i + 65, countAlphabet[i]);
		if (i == 12)	printf("\n");
	}

	fclose(fp);
}