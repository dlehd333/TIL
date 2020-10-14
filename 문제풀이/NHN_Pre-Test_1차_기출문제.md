# 문제
모든 원소가 0 또는 1 인 행렬이 있습니다. 1 로 표시된 원소는 영역을 나타냅니다. 여기에서 상하좌우에 인접한 1은 같은 영역이라고 가정합니다. 각 영역의 크기는 1 의 개수로 정의합니다. 주어진 N x N 크기의 행렬에서 영역의개수와 각 영역의 크기를 오름차순으로 출력하세요.
# 입력
• 첫 번째 행은 행렬의 크기인 N입니다. N 은 1 이상 10 이하의 자연수입니다.
• 입력 두 번째 행부터는 공백으로 구분된 0 과 1 로 행렬이 주어집니다. 각 행은 개행 문자(newline, \n)로
구분됩니다.
# 출력
• 첫 번째 행은 영역의 개수를 출력합니다.
• 두 번째 행은 각 영역의 크기를 공백으로 구분하여 오름차순으로 출력합니다.
• 한 행의 끝은 불필요한 공백 없이 개행 문자(newline, \n)로 끝나야 합니다.
• 영역이 존재하지 않을 경우 영역 수 0으로 1 행으로만 출력합니다.
# 행렬 및 영역 예시
![이미지]()
영역은 3개이며, 각 영역의 크기는 4, 5, 7입니다.
아래 테스트 케이스에서 예제로 2 개를 오픈하므로 별도로 예를 들 필요가 없습니다.

# 예시 입/출력
입력 1

6

0 1 1 0 0 0

0 1 1 0 1 1

0 0 0 0 1 1

0 0 0 0 1 1

1 1 0 0 1 0

1 1 1 0 0 0

출력 1

3

4 5 7

---
입력 2

4

0 0 0 0

0 0 0 0

0 0 0 0

0 0 0 0

출력 2

0

---
입력 3

4

1 0 0 0

1 0 0 0

0 0 0 0

0 0 1 1

출력 3

2

2 2

# 나의 풀이
- 추가로 정리할 수 있지만, 그대로의 모습을 위해 완성한 직후의 모습을 남긴다
```c
#include <stdio.h>
#include <stdlib.h>

struct pos {	// 영역정보를 저장할 구조체
	int x;
	int y;
	int team;
};

struct pos area[36];	// 영역정보를 저장하는 배열
int nextCount = 0;		// 원소가 1인 영역의 전체 개수
int nextTeam = 0;		// 전체 영역의 개수

int compare(const void* a, const void* b)    // 오름차순 비교 함수 구현
{
	int num1 = *(int*)a;    // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴
	int num2 = *(int*)b;    // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴

	if (num1 < num2)    // a가 b보다 작을 때는
		return -1;      // -1 반환

	if (num1 > num2)    // a가 b보다 클 때는
		return 1;       // 1 반환

	return 0;    // a와 b가 같을 때는 0 반환
}


int searchTeam(x, y)	// 해당 위치의 영역을 찾는 함수
{
	for (int i = 0; i < nextCount; i++)
	{
		if (area[i].x == x && area[i].y == y)
			return area[i].team;
	}
	return 0;
}

int main()
{
	int hexlen = 8;
	int hex[8][8] = {
		{0,1,1,0,0,1,0,0},
		{0,1,1,0,0,1,0,0},
		{0,0,0,0,0,0,1,1},
		{1,0,0,1,0,0,1,1},
		{1,1,0,0,1,0,1,0},
		{1,0,0,0,1,0,1,1},
		{1,0,0,0,1,0,0,1},
		{0,0,0,0,0,0,0,0}
	};

	for (int i = 0; i < hexlen; i++)	// 탐색하면서 영역을 판별한다
	{
		for (int j = 0; j < hexlen; j++)
		{
			if (hex[i][j] == 0)	// 0인 원소는 패스한다
				continue;

			if (i > 0)	// 가로 맨 윗줄은 검사하지 않는다
			{
				if (hex[i - 1][j] == 1)	// 자기자신 윗칸의 영역을 검사한다
				{
					area[nextCount].x = i;
					area[nextCount].y = j;
					area[nextCount].team = searchTeam(i - 1, j);
					nextCount++;
					continue;
				}
			}
			if (j > 0)	// 세로 맨 윗줄은 검사하지 않는다
			{
				if (hex[i][j - 1] == 1)	// 자기자신 왼쪽의 영역을 검사한다
				{
					area[nextCount].x = i;
					area[nextCount].y = j;
					area[nextCount].team = searchTeam(i, j - 1);
					nextCount++;
					continue;
				}
			}
			// 왼쪽과 위쪽의 인접한 지역의 원소가 0이라면 스스로가 새로운 영역이 된다
			area[nextCount].x = i;
			area[nextCount].y = j;
			area[nextCount].team = nextTeam;
			nextTeam++;
			nextCount++;
		}
	}

	// 수집한 1인 원소들의 데이터를 영역의 크기별로 재수집
	int* line = malloc(sizeof(int) * (nextTeam));
	memset(line, 0, sizeof(int));

	for (int i = 0; i < nextTeam; i++)
	{
		// 수집한 원소들이 어느 영역인지 카운트하여 그 값을 저장
		int num = 0;
		for (int j = 0; j < nextCount; j++)
		{
			if (area[j].team == i)
				num++;
		}
		*(line+i) = num;
	}

	// 저장한 영역의 크기들을 오름차순으로 정렬
	qsort(line, nextTeam, sizeof(int), compare);

	// 출력
	printf("%d\n", hexlen);
	for (int i = 0; i < hexlen; i++)
	{
		for (int j = 0; j < hexlen; j++)
			printf("%d ", hex[i][j]);
		printf("\n");
	}
	printf("\n%d\n", nextTeam);
	for (int i = 0; i < nextTeam; i++)
		printf("%d ", *(line + i));
	printf("\n");

	free(line);

	return 0;
}
```