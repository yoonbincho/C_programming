// 2018204037 조윤빈 프로그래밍 기초 2차괴제 제출
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define SIZE 10 //크기를 정해줍니다

int main(void)
{   //배열을 이용하여 극장 예약 시스템 프로그램
	int i, num;
	int sit[SIZE] = { 0, 0 };  // 하나만 정해주면 나머지는 0으로 저장됩니다
	char ans, c;
	printf("7장 7번 문제 시작......\n");//7번 문제 시작
	do
	{
		printf("좌석을 예약하시겠습니까?(y 또는 n) "); scanf(" %c", &ans);
		if (ans == 'y')
		{
			printf("-----------------------\n");
			for (i = 0; i < SIZE; i++)
				printf(" %d", i + 1); //0번 좌석은 존재하지 않으므로 +1을 해줍니다
			printf("\n-----------------------\n");
			for (i = 0; i < SIZE; i++)
				printf(" %d", sit[i]);
			printf("\n몇번째 좌석을 예약하시겠습니까?");  scanf("%d", &num);//좌석번호를 받습니다
			if (sit[num - 1] == 1)
				printf("이미 예약된 좌석입니다.");
			else
			{
				sit[num - 1] = 1;
				printf("예약되었습니다.\n");
			}
		}
		else if (ans == 'n')
			break; //n이 입력된경우 break를 입력하여 실행을 멈춰 반복에서 꺼내줍니다
		else
			printf("잘못입력하셨습니다 다시 입력해주세요\n");
	} while (ans != 'n'); // n 이 아닌 다른 것을 입력하면 반복됨
						  //평균과 표준 편차를 계산하는 프로그램을 시작합니다
	double x[5], m, v, sum1 = 0, sum2 = 0, pjpc; // m=평균, v=분산 pjpc=표준편차
	printf("\n\n\n7장 8번 문제 시작......\n");
	for (i = 0; i < 5; i++)
	{
		printf("실수를 입력하세요: "); scanf("%lf", &x[i]);//실수를 입력받습니다
		sum1 += x[i];
	}
	m = sum1 / 5;
	printf("평균:%lf\n", m);//
	for (i = 0; i < 5; i++)
		sum2 += (x[i] - m) * (x[i] - m);
	v = sum2 / 5;
	pjpc = sqrt(v);
	printf("표준편차:%lf\n", pjpc);

	return 0;
}