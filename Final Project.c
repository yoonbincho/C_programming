/* ���α׷��ֱ��� 2018-1 �⸻��� ���� ����
* main �Լ� �� �Լ������� ���� �������� ����, main �Լ� �ϴ��� �� �Լ����� �ϼ��� ��!
* �� �Լ����� ��������� �ݵ�� �ؼ��� ��!
* ���� ���� ��, 0���̸� �κ� ���� ����.
* ��� �ۼ� ��, "�й�-�̸�.c" ������ U-ķ�� �����ϰ� ������ Ȯ�� �� ���.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void printSum1To1000(void);
void PrintProfile(void);
int Factorial(int);
void covert2Low(char*);
void AvgOfArray(double*);
void my_strcpy(char *, char *);

int main(void)
{
	int num;
	double arr[] = { 1.2, 3.5, 7.4, 0.5, 10.0 };
	char str[16]; char des[60] = { '\0' };

	printf("����1 �Լ� ȣ�� ����\n");

	//1����: �ݺ����� �̿��ؼ� 1���� 1000������ ������ ����ؼ� ����ϴ� �Ʒ��� �Լ� �ϼ� 
	printSum1To1000();//6��

	printf("����2 �Լ� ȣ�� ����\n");
	//2����: �ڽ��� �й�, �̸�, �а��� ����ϴ� �Ʒ��� �Լ� �ϼ�.
	PrintProfile(); //5��

	printf("����3 �Լ� ȣ�� ����\n");
	//3 ����: ������ ���� ������ �Է� �� ���ڷ� ���޹޾Ƽ� ���丮���� ����ϵ��� 
	//����Լ��� ������ Factorial �Լ��ϼ�.
	scanf("%d", &num);
	printf("%d! = %d \n", num, Factorial(num)); //6��

	printf("����4 �Լ� ȣ�� ����\n");
	//4 ����: ���� ���ڿ��� �Է� �޾Ƽ�, ���� �迭 str�� �����ϰ�, �빮�ڸ� ã�� �ҹ��ڷ� �ٲٴ� �Ʒ��� �Լ� �ϼ�.
	covert2Low(str);//6��
	printf("%s\n\n\n", str);

	printf("����5 �Լ� ȣ�� ����\n");
	//5 ����: ���� �ʱ�ȭ�� �迭 ������ ����� ���ؼ� �Ҽ������� ����ϴ� �Ʒ��� �Լ� �ϼ�.
	AvgOfArray(arr);//6��

	printf("����6 �Լ� ȣ�� ����\n");
	//6 ����: ���� ����� �迭 des�� "Hello World"�� �����ϴ� �Ʒ��� �Լ� �ϼ�
	my_strcpy(des, "Hello World");//6��
	printf("%s \n", des);

	printf("\n Acknowledgement\n");
	printf("��� ���б� ���� ���� ������...\n");

	return 0;
}

//���� 1
void printSum1To1000(void)
{
	int i;
	int a = 1000;
	int sum = 0;
	for (i = 1; i <= 1000; i++)
		sum += i;
	printf("%d\n", sum);
}

//����2:  
void PrintProfile(void)
{//�й��� ���� ����, �̸��� ���� �迭, �а��� �����ͺ����� �����ϰ� ���� �����ؼ� ȭ�� ���!!!.
	char *a = "2018204037";
	char *b = "������";
	char *c = "���������к�";
	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);

}

//����3
int Factorial(int n)
{//�ݵ�� ���ȣ��� �ۼ� ������ ���� ������ �Է� �� ���ڷ� ���޹޾Ƽ� ���丮���� ����ϵ��� 
	int i;
	int sum = 1;
	if (n > 0)
	{
		for (i = 1; i < n; i++)
		{
			sum = n*Factorial(n - 1);
		}
		return sum;
	}
}

//����4: Hint-> A~Z�� �ƽ�Ű�ڵ尪�� 65~90, a~z�� �ƽ�Ű�ڵ尪�� 97~122 ���� ���ڿ��� �Է� �޾Ƽ�, ���� �迭 str�� �����ϰ�, �빮�ڸ� ã�� �ҹ��ڷ� �ٲٴ� �Ʒ��� �Լ� �ϼ�.
void covert2Low(char *pStr)
{
	
	
}

//����5
void AvgOfArray(double *ptr)
{

	int i;
	double sum=0;

	for (i = 0; i < 5; i++)
	{
		sum += ptr[i];

	}
	printf("%f\n", sum / 5.0);

}

// ����6
void my_strcpy(char *p1, char *p2)
{//���̺귯�� �Լ� ������� �� ��!!!

	
	



}
