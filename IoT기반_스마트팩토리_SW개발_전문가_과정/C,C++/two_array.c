#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 4�������� ������ ������ �ִ� 5���� �ִٴ� ����
// ���κ� ����, ���� ����� ���Ѵ�

int main()
{
	srand(time(NULL));	// ���� �õ尪

	int point[5][5];	// �л����� �迭
	double aver[sizeof(point[0]) / sizeof(int)] = { 0, };		// ��� �迭

	// -----------------------------------------------------------------------------------
	// �迭�� ������ �� ������ �̿��� �� ����.
	// 		int averSize = sizeof(point[0]) / sizeof(int);
	// 		double aver[averSize] = { 0, }; // error
	// ������ Ȱ���ؾ� �� ���� �����Ҵ��� �̿�����\
	// 		double *aver = malloc(sizeof(double) * averSize);
	// -----------------------------------------------------------------------------------

	// �迭 ũ��
	int pointCol = sizeof(point[0]) / sizeof(int);		// ����� + ����
	int pointRow = sizeof(point) / sizeof(point[0]);	// �л���
	
	// �л����� �迭 �ʱ�ȭ
	for (int i = 0; i < pointRow; i++)
	{
		for (int j = 0; j < pointCol; j++)
		{
			if (j < 3)
				point[i][j] = rand() % 16 + 15;	// ���� 15~30
			else if (j == 3)
				point[i][j] = rand() % 6 + 5;	// ���� 5~10
			else
				point[i][j] = 0;				// 0����
		}
	}

	// �л����� ����, ��� ���ϱ�
	// ----------------------------------------------------------------------
	// ���� ���� ��� ����� ���� for���� �ι� ���������
	// ����, ��� ����� ���� ��Ʈ��ȸ�� ������ �ٸ����� ������ �����Ƿ�
	// �ݺ����� ������ ���� �� �ִ�.
	// ----------------------------------------------------------------------
	
	for (int i = 0; i < pointCol - 1; i++)
	{
		for (int j = 0; j < pointRow; j++)
		{
			point[j][pointCol - 1] += point[j][i];	// �迭�� ������ ��(����)�� ����
			aver[i] += point[j][i];					// ��� ����� ���� ����
		}

		aver[i] = aver[i] / pointRow;
	}

	// ���(��� �迭�� ���� ����ϱ� ���� ���� ���̺��� 1 ���ؼ� �ݺ����� ������)
	for (int i = 0; i < pointRow + 1; i++)
	{
		if (i < pointRow)
			printf("�� ��  %2d��: ", i+1);
		else
			printf("�׸� ���: ");

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