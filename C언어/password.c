#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// ����ڿ��� ��ȣ�� �Է¹޾�
// ��ȣ�� ��ȿ���� �׽�Ʈ�ϴ� ����
// ��ȣ���� �ҹ���, �빮��, ���ڰ� ���� �־����

int main()
{
	// ��ȣ�� �Է¹��� �����迭 �� üũ�� bool ����
	char* pw = malloc(50);
	bool check[3] = { false, false, false };

	// ������ ��ȣ�� �Է¹��� ������ ���ѷ���
	while (true)
	{
		// üũ�� bool���� �ʱ�ȭ
		for(int i = 0; i < sizeof(check);i++)
			check[i] = false;

		// ��ȣ �Է�
		printf("��ȣ�� �����Ͻÿ�:");
		scanf("%s", pw);

		// ��ȣ�� ���뼺 �˻�
		for (int i = 0; i < strlen(pw);i++)
		{
			if (pw[i] >= '0' && pw[i] <= '9')		// ����
				check[0] = true;
			else if (pw[i] >= 'A' && pw[i] <= 'Z')	// �빮��
				check[1] = true;
			else if (pw[i] >= 'a' && pw[i] <= 'z')	// �ҹ���
				check[2] = true;
		}

		// �˻����� ��� ������ ��� ���� �޽��� �� ���ѷ��� Ż��
		// �ƴҰ�� ���� �޽��� ��� �� ���ѷ��� ����
		if (check[0] && check[1] && check[2])
		{
			printf("������ ��ȣ�Դϴ�\n");
			break;
		}
		else
			printf("����,�빮��,�ҹ��ڸ� ��� ��ȣ�� �ٽ� ���弼��!\n");
	}

	// �����Ҵ� ����
	free(pw);
}