#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct Phone {
	char name[20];
	char home[15];
	char hand[15];
};

int main()
{
	struct Phone phone[5];					// ��ȭ��ȣ ������ ����ִ� ����ü
	char serch[20];							// �˻��� �Է¿� ����
	int result = -1;						// �˻���� �ش� ������ ��ġ�� ������ ����

	for (int i = 0; i < 5; i++)				// 5���� ��ȭ��ȣ ������ �Է¹޴´�
	{
		printf("�̸��� �Է��Ͻÿ� : ");
		scanf("%s", phone[i].name);
		printf("����ȭ��ȣ�� �Է��Ͻÿ� : ");
		scanf("%s", phone[i].home);
		printf("�޴�����ȣ�� �Է��Ͻÿ� : ");
		scanf("%s", phone[i].hand);
	}
	
	printf("\n");
	
	while (1)								// �̸��� ���� ��ȭ��ȣ�� �˻��Ѵ�
	{
		result = -1;
		sprintf(serch, "");					// �Է¹��� �ʱ�ȭ

		printf("�˻��� �̸��� �Է��ϼ��� : ");
		scanf("%s", serch);					// �˻��� �Է�

		for (int i = 0; i < 5; i++)
		{
			if (strcmp(serch, phone[i].name) == 0)	// ���ڿ� ��
			{
				result = i;		// �ش� ���� ��ġ�� ����
				break;
			}
		}

		if (result != -1)	// ����� ������ ��ġ�� �ִٸ� ���
		{
			printf("����ȭ��ȣ : %s\n", phone[result].home);
			printf("�޴�����ȣ : %s\n\n", phone[result].hand);
		}
		else
			printf("�߸��� �Է��Դϴ�.\n\n");
	}
}