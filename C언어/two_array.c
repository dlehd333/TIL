#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 4개과목의 성적을 가지고 있는 5명이 있다는 가정
// 개인별 총점, 과목별 평균을 구한다

int main()
{
	srand(time(NULL));	// 난수 시드값

	int point[5][5];	// 학생점수 배열
	double aver[sizeof(point[0]) / sizeof(int)] = { 0, };		// 평균 배열

	// -----------------------------------------------------------------------------------
	// 배열을 정의할 때 변수를 이용할 수 없다.
	// 		int averSize = sizeof(point[0]) / sizeof(int);
	// 		double aver[averSize] = { 0, }; // error
	// 변수를 활용해야 할 때는 동적할당을 이용하자\
	// 		double *aver = malloc(sizeof(double) * averSize);
	// -----------------------------------------------------------------------------------

	// 배열 크기
	int pointCol = sizeof(point[0]) / sizeof(int);		// 과목수 + 총점
	int pointRow = sizeof(point) / sizeof(point[0]);	// 학생수
	
	// 학생점수 배열 초기화
	for (int i = 0; i < pointRow; i++)
	{
		for (int j = 0; j < pointCol; j++)
		{
			if (j < 3)
				point[i][j] = rand() % 16 + 15;	// 난수 15~30
			else if (j == 3)
				point[i][j] = rand() % 6 + 5;	// 난수 5~10
			else
				point[i][j] = 0;				// 0으로
		}
	}

	// 학생점수 총점, 평균 구하기
	// ----------------------------------------------------------------------
	// 원래 총점 평균 계산을 위해 for문을 두번 사용하지만
	// 총점, 평균 계산을 위한 루트순회의 방향이 다를지라도 내용은 같으므로
	// 반복문의 개수를 줄일 수 있다.
	// ----------------------------------------------------------------------
	
	for (int i = 0; i < pointCol - 1; i++)
	{
		for (int j = 0; j < pointRow; j++)
		{
			point[j][pointCol - 1] += point[j][i];	// 배열의 마지막 행(총점)에 더함
			aver[i] += point[j][i];					// 평균 계산을 위해 더함
		}

		aver[i] = aver[i] / pointRow;
	}

	// 출력(평균 배열을 같이 출력하기 위해 행의 길이보다 1 더해서 반복문을 돌린다)
	for (int i = 0; i < pointRow + 1; i++)
	{
		if (i < pointRow)
			printf("학 생  %2d번: ", i+1);
		else
			printf("항목별 평균: ");

		for (int j = 0; j < pointCol;j++)
		{
			if (i < pointRow)
				printf("%2d   ", point[i][j]);
			else
				printf("%3.1lf ", aver[j]);
		}

		printf("\n");
	}
}