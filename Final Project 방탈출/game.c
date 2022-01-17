#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "stray.h"

void intro_b(void)
{
	char str[1024];
	FILE *fp;

	stdoutClear();
	fp = fopen("bulls_and_cows.txt", "r");
	while (fgets(str, sizeof(str), fp))
		puts(str);
	fclose(fp);
	puts("\n\n계속하려면 Enter를 누르시오 . . .\n");
	while (getchar() != '\n');
	stdoutClear();
}

void intro_f(void)
{
	char str[1024];
	FILE *fp;

	stdoutClear();
	fp = fopen("flower_language.txt", "r");
	while (fgets(str, sizeof(str), fp))
		puts(str);
	fclose(fp);
	puts("\n\n계속하려면 Enter를 누르시오 . . .\n");
	while (getchar() != '\n');
	stdoutClear();
}

void intro_p(void)
{
	char str[1024];
	FILE *fp;

	stdoutClear();
	fp = fopen("place.txt", "r");
	while (fgets(str, sizeof(str), fp))
		puts(str);
	fclose(fp);
	puts("\n\n계속하려면 Enter를 누르시오 . . .\n");
	while (getchar() != '\n');
	stdoutClear();
}

void intro_h(void)
{
	char str[1024];
	FILE *fp;

	stdoutClear();
	fp = fopen("hangman.txt", "r");
	while (fgets(str, sizeof(str), fp))
		puts(str);
	fclose(fp);
	puts("\n\n계속하려면 Enter를 누르시오 . . .\n");
	while (getchar() != '\n');
	stdoutClear();
}

int bulls_and_cows(void)
{
	char original[] = "1230";
	char guessed[DIGITS + 1];
	int i, j, k;

	intro_b();

	for (i = 0; i < TRIES; i++) {
		gotoxy(0, 0);
		for (j = 0; j < TRIES - i; j++)
			printf("♥");
		for (j = 0; j < i; j++)
			printf("♡");
		gotoxy(0, i * 3);

		printf("\n\n숫자 입력: ");
		for (j = 0; j < DIGITS; j++) {
			while (true) {
				guessed[j] = _getch();
				bool state = true;
				if (!isdigit(guessed[j]))
					state = false;
				for (k = 0; k < j; k++) {
					if (guessed[j] == guessed[k]) {
						state = false;
						break;
					}
				}
				if (state) {
					putchar(guessed[j]);
					break;
				}
			}
		}
		guessed[j] = '\0';
		printf("\n");

		int strike = 0, ball = 0;

		for (j = 0; j < DIGITS; j++)
			if (guessed[j] == original[j])
				strike++;
			else
				for (k = 0; k < DIGITS; k++)
					if (guessed[j] == original[k])
						ball++;

		if (strike + ball == 0)
			printf("OUT\n\n");
		else
			printf("%dS %dB\n\n", strike, ball);

		if (strike == 4) {
			stdoutClear();
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

int flower_language(void)
{
	char password[] = "2143";
	char guessed[DIGITS + 1];
	int i, j;

	intro_f();

	printf("\n꽃의 순서는 빨강, 파랑, 하양, 노랑이었고,\n\n");
	printf("꽃말의 순서는 1. 기적, 2. 정열적인 사랑, 3. 질투, 4. 순결이었다.\n\n\n");

	printf("숫자 입력: ");
	for (i = 0; i < DIGITS; i++) {
		while (true) {
			guessed[i] = _getch();
			bool state = true;
			if (!(guessed[i] >= '1' && guessed[i] <= '4'))
				state = false;
			for (j = 0; j < i; j++) {
				if (guessed[i] == guessed[j]) {
					state = false;
					break;
				}
			}
			if (state) {
				putchar(guessed[i]);
				break;
			}
		}
	}
	guessed[i] = '\0';
	printf("\n");

	if (strcmp(password, guessed))
		return EXIT_FAILURE;
	else {
		stdoutClear();
		return EXIT_SUCCESS;
	}
}

int hangman(void)
{
	char ch;
	int count = 0;

	intro_h();

	char str1[LETTERS] = "JANE ROSE";
	char str2[LETTERS] = "____ ____";

	while (true) {
		stdoutClear();

		for (int i = 0; i < TRIES - count; i++)
			printf("♥");
		for (int i = 0; i < count; i++)
			printf("♡");
		printf("\n\n%s\n\n", str2);

		if (count == 10)
			break;

		while (true) {
			ch = toupper(_getch());
			bool state = true;
			if (!isalpha(ch))
				state = false;
			for (int i = 0; i < LETTERS; i++) {
				if (ch == str2[i]) {
					state = false;
				}
			}
			if (state)
				break;
		}
		bool state = true;
		for (int i = 0; i < LETTERS; i++) {
			if (str1[i] == ch && str2[i] == '_') {
				str2[i] = ch;
				state = false;
			}
		}
		if (state)
			count++;

		if (!(strcmp(str1, str2))) {
			stdoutClear();

			for (int i = 0; i < TRIES - count; i++)
				printf("♥");
			for (int i = 0; i < count; i++)
				printf("♡");
			printf("\n\n%s\n\n", str1);

			printf("계속하려면 Enter키를 누르시오 . . .\n");
			while (getchar() != '\n');
			stdoutClear();

			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

int place(void)
{
	char password[] = "movietheater";
	char guessed[100];
	int i, j;

	intro_p();

	printf("\n『Pull me forward』 \"NpwjfUifbufs\"\n\n");
	printf("for (int i = 0; i < strlen(str); i++) putchar(str[i] - 1);\n\n\n");
	printf("비밀번호 입력: ");
	gets(guessed);

	for (i = 0; i < strlen(guessed); i++)
		guessed[i] = tolower(guessed[i]);

	for (i = 0; i < strlen(guessed); i++) {
		if (guessed[i] == ' ') {
			for (j = i; j < strlen(guessed); j++)
				guessed[j] = guessed[j + 1];
			guessed[j] = '\0';
			i--;
		}
	}

	if (strcmp(password, guessed))
		return EXIT_FAILURE;
	else {
		stdoutClear();
		return EXIT_SUCCESS;
	}
}