// 2018204037 ������ ���α׷��� ���� 2������ ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define SIZE 10 //ũ�⸦ �����ݴϴ�

int main(void)
{   //�迭�� �̿��Ͽ� ���� ���� �ý��� ���α׷�
	int i, num;
	int sit[SIZE] = { 0, 0 };  // �ϳ��� �����ָ� �������� 0���� ����˴ϴ�
	char ans, c;
	printf("7�� 7�� ���� ����......\n");//7�� ���� ����
	do
	{
		printf("�¼��� �����Ͻðڽ��ϱ�?(y �Ǵ� n) "); scanf(" %c", &ans);
		if (ans == 'y')
		{
			printf("-----------------------\n");
			for (i = 0; i < SIZE; i++)
				printf(" %d", i + 1); //0�� �¼��� �������� �����Ƿ� +1�� ���ݴϴ�
			printf("\n-----------------------\n");
			for (i = 0; i < SIZE; i++)
				printf(" %d", sit[i]);
			printf("\n���° �¼��� �����Ͻðڽ��ϱ�?");  scanf("%d", &num);//�¼���ȣ�� �޽��ϴ�
			if (sit[num - 1] == 1)
				printf("�̹� ����� �¼��Դϴ�.");
			else
			{
				sit[num - 1] = 1;
				printf("����Ǿ����ϴ�.\n");
			}
		}
		else if (ans == 'n')
			break; //n�� �ԷµȰ�� break�� �Է��Ͽ� ������ ���� �ݺ����� �����ݴϴ�
		else
			printf("�߸��Է��ϼ̽��ϴ� �ٽ� �Է����ּ���\n");
	} while (ans != 'n'); // n �� �ƴ� �ٸ� ���� �Է��ϸ� �ݺ���
						  //��հ� ǥ�� ������ ����ϴ� ���α׷��� �����մϴ�
	double x[5], m, v, sum1 = 0, sum2 = 0, pjpc; // m=���, v=�л� pjpc=ǥ������
	printf("\n\n\n7�� 8�� ���� ����......\n");
	for (i = 0; i < 5; i++)
	{
		printf("�Ǽ��� �Է��ϼ���: "); scanf("%lf", &x[i]);//�Ǽ��� �Է¹޽��ϴ�
		sum1 += x[i];
	}
	m = sum1 / 5;
	printf("���:%lf\n", m);//
	for (i = 0; i < 5; i++)
		sum2 += (x[i] - m) * (x[i] - m);
	v = sum2 / 5;
	pjpc = sqrt(v);
	printf("ǥ������:%lf\n", pjpc);

	return 0;
}