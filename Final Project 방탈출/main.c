#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include "stray.h"

PLAYER player;
char strPlayer[] = "●";

int main(void)
{
	player.item.card_key = false;
	player.item.teddy_bear = false;
	player.item.key = false;
	player.item.rose_hint = false;

	player.room = LOBBY;

	for (int i = 0; i < ROOMS; i++)
		player.visited[i] = false;

	player.nX = 35;
	player.nY = 12;

	intro();
	puts("  스토리를 진행하려면 Enter를 누르시오 . . .\n");
	while (getchar() != '\n');
	stdoutClear();

	txtPrint("lobby.txt");
	stdoutClear();

	while (true) {
		Move();
		stdoutClear();
		if (player.object) {
			switch (player.object) {
			case CHEST:
				stdLeftRoom();
				txtPrint("chest.txt");
				if (bulls_and_cows())
					gameOver();
				txtPrint("left_room-2.txt");
				player.object = false;
				player.item.card_key = true;
				player.visited[LEFT_ROOM] = true;
				break;

			case TABLE:
				stdRightRoom();
				txtPrint("table.txt");
				player.object = false;
				player.item.rose_hint = true;
				break;

			case SAFEBOX:
				stdRightRoom();
				strPrint("금고는 카드키를 댄 뒤에 비밀번호를 입력해야 한다.							\n");
				if (player.item.card_key) {
					if (player.item.rose_hint) {
						strPrint("\'삐빅-\'														\n");
						strPrint("나는 차분히 카드키를 금고에 댄 뒤 암호를 입력했다.					\n");
						if (flower_language())
							gameOver();
						txtPrint("right_room-2.txt");
						player.item.teddy_bear = true;
						player.visited[RIGHT_ROOM] = true;
					}
					else
						strPrint("앗, 비밀번호에 대한 힌트가 없으니 방에서 힌트를 더 찾아보도록 하자.	\n");
				}
				else
					strPrint("앗, 카드키가 없으니 다른 방에서 카드키를 찾아보도록 하자.				\n");
				player.object = false;
				break;

			case PLATE:
				stdInnerRoom();
				txtPrint("plate.txt");
				if (player.item.teddy_bear) {
					txtPrint("inner_room-2.txt");
					if (place())
						gameOver();
					txtPrint("inner_room-3.txt");
					player.item.key = true;
					player.visited[INNER_ROOM] = true;
				}
				else
					strPrint("앗, 철판을 열 장치가 없으니 장치를 찾아보도록 하자.					\n");
				player.object = false;
				break;
			}
		}
		else {
			switch (player.room) {
			case LEFT_ROOM:
				if (player.visited[LEFT_ROOM]) {
					stdLobby();
					strPrint("이미 왔던 방이다. 다른 방으로 이동해보자.								\n");
					player.room = LOBBY;
					player.nX = 2;
				}
				else {
					stdLeftRoom();
					txtPrint("left_room-1.txt");
				}
				break;

			case RIGHT_ROOM:
				if (player.visited[RIGHT_ROOM]) {
					stdLobby();
					strPrint("이미 왔던 방이다. 다른 방으로 이동해보자.								\n");
					player.room = LOBBY;
					player.nX = 68;
				}
				else {
					stdRightRoom();
					txtPrint("right_room-1.txt");
					break;
				}
				break;

			case INNER_ROOM:
				if (player.visited[INNER_ROOM]) {
					stdLobby();
					strPrint("이미 왔던 방이다. 다른 방으로 이동해보자.								\n");
					player.room = LOBBY;
					player.nY = 2;
				}
				else {
					stdInnerRoom();
					txtPrint("inner_room-1.txt");
				}
				break;

			case EXIT:
				if (player.item.key) {
					txtPrint("exit-1.txt");
					if (hangman())
						gameOver();
					txtPrint("exit-2.txt");
					outro();
				}
				else {
					stdLobby();
					strPrint("지금은 암호에 관한 힌트가 없으니 방을 더 둘러보도록 하자.				\n");
				}
				player.room = LOBBY;
				player.nY = 23;
				break;
			}
		}
	}
	return 0;
}

void intro(void)
{
	printf("    _,--._.-,\n   /↖_r-,↖_ )\n ↗-.) _:=:_/ (↖\n↖ ↖'     ↖/  )\n L.:-. _.:|-:  /\n <_:-:↖: :  /\n   ↖-._( ↖\n    ___   ↖↖,       ______\n    ↖ .:-. ↖↖  .  /.-:_./\n       ↖._   .↖↖/.- _./\n          ↖--..↖(.--/\n");
	printf("    ■■■■■       ■           ■      ■■■■■■■ ■  \n");
	printf("            ■       ■           ■            ■       ■  \n");
	printf("            ■       ■           ■■■      ■  ■     ■  \n");
	printf("            ■       ■■■■     ■        ■      ■   ■■■  \n");
	printf("                                  ■       ■        ■  ■  \n");
	printf("   ■■■■■■■     ■■■■■■■                     ■  \n");
	printf("                      ■          ■                     ■  \n");
	printf("                      ■          ■                     ■  \n");
	printf("                      ■■■■■■■                        \n");
	printf("                            □□□□□         □□         □     □□□□□□□ □ \n");
	printf("                                    □       □    □   □□□           □       □  \n");
	printf("                                    □       □    □       □         □  □     □ \n");
	printf("                                    □         □□     □□□       □      □   □□□  \n");
	printf("                                                            □      □        □  □  \n");
	printf("                           □□□□□□□                   □                    □  \n");
	printf("                                                            □                    □  \n\n");
}

void gameOver(void)
{
	stdoutClear();
	gotoxy(35, 12);
	puts("G A M E  O V E R");
	gotoxy(0, 25);
	exit(1);
}

void outro(void)
{
	gotoxy(0, 0);
	printf("   ■■■■■   ■    ■    ■■■■  \n");
	printf("       ■       ■    ■    ■        \n");
	printf("       ■       ■■■■    ■■■■  \n");
	printf("       ■       ■    ■    ■        \n");
	printf("       ■       ■    ■    ■■■■  \n");
	printf("                                      \n");
	printf("    □□□□    □      □   □□□   \n");
	printf("    □          □ □   □   □    □   \n");
	printf("    □□□□    □  □  □   □     □  \n");
	printf("    □          □    □□   □    □  \n");
	printf("    □□□□    □      □   □□□    \n");
	exit(0);
}

void Render(int num)
{
	ScreenClear();
	switch (num) {
	case LOBBY:	Lobby(); break;
	case RIGHT_ROOM: RightRoom(); break;
	case INNER_ROOM: InnerRoom(); break;
	case LEFT_ROOM: LeftRoom(); break;
	}
	ScreenPrint(player.nX, player.nY, strPlayer);
	ScreenFlipping();
}

void Move(void)
{
	int nKey;

	ScreenInit();

	while (true) {
		if (Crush(player.room))
			break;
		if (_kbhit()) {
			nKey = _getch();
			switch (nKey) {
			case LEFT:
				if (player.nX - 1 >= 1)
					player.nX--;
				break;
			case UP:
				if (player.nY - 1 >= 1)
					player.nY--;
				break;
			case RIGHT:
				if (player.nX + 1 <= 69)
					player.nX++;
				break;
			case DOWN:
				if (player.nY + 1 <= 24)
					player.nY++;
				break;
			}
		}
		Render(player.room);
	}
	ScreenRelease();
}

void txtPrint(char *file_name)
{
	char str[1024];
	FILE *fp;

	fp = fopen(file_name, "r");
	while (fgets(str, sizeof(str), fp)) {
		gotoxy(2, 27);
		puts(str);
		gotoxy(70, 27);
		while (getchar() != '\n');
	}
	fclose(fp);
}

void strPrint(char *str)
{
	gotoxy(2, 27);
	puts(str);
	gotoxy(70, 27);
	while (getchar() != '\n');
}

bool Crush(int num)
{
	switch (num) {
	case LOBBY:
		if (player.nX == 1 && player.nY == 12) {
			player.room = LEFT_ROOM;
			player.nX = 68;
			return true;
		}
		else if (player.nX == 35 && player.nY == 1) {
			player.room = INNER_ROOM;
			player.nY = 23;
			return true;
		}
		else if (player.nX == 69 && player.nY == 12) {
			player.room = RIGHT_ROOM;
			player.nX = 2;
			return true;
		}
		else if (player.nX == 35 && player.nY == 24) {
			player.room = EXIT;
			return true;
		}
		else
			return false;
		break;

	case LEFT_ROOM:
		if (player.nX == 69 && player.nY == 12) {
			player.room = LOBBY;
			player.nX = 2;
			return true;
		}
		else if (((player.nX >= 5) && (player.nX <= 13)) && ((player.nY >= 11) && (player.nY <= 15))) {
			player.object = CHEST;
			player.nX = 14;
			player.nY = 12;
			return true;
		}
		else
			return false;
		break;

	case INNER_ROOM:
		if (player.nX == 35 && player.nY == 24) {
			player.room = LOBBY;
			player.nY = 2;
			return true;
		}
		else if (((player.nX >= 22) && (player.nX <= 48)) && ((player.nY >= 1) && (player.nY <= 4))) {
			player.object = PLATE;
			player.nX = 35;
			player.nY = 5;
			return true;
		}
		else
			return false;
		break;

	case RIGHT_ROOM:
		if (player.nX == 1 && player.nY == 12) {
			player.room = LOBBY;
			player.nX = 68;
			return true;
		}
		else if (((player.nX >= 42) && (player.nX <= 56)) && ((player.nY >= 12) && (player.nY <= 16))) {
			player.object = SAFEBOX;
			player.nX = 41;
			player.nY = 12;
			return true;
		}
		else if (((player.nX >= 53) && (player.nX <= 63)) && ((player.nY >= 20) && (player.nY <= 22))) {
			player.object = TABLE;
			player.nX = 52;
			player.nY = 21;
			return true;
		}
		else
			return false;
		break;
	}
}

void stdoutClear(void)
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 50, Coor, &dw);
	gotoxy(0, 0);
}

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

void ScreenInit(void)
{
	CONSOLE_CURSOR_INFO cci;
	// 화면 버퍼 2개 생성

	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping(void)
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear(void)
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 50, Coor, &dw);
}

void ScreenRelease(void)
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char *string)
{
	DWORD dw;
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void SetColor(unsigned short color)
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void stdLobby(void)
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┛                                                                      ┗\n");
	printf("                                                                        \n");
	printf("┓                                                                      ┏\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void Lobby(void)
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                                                      ┃");
	ScreenPrint(0, 2, "┃                                                                      ┃");
	ScreenPrint(0, 3, "┃                                                                      ┃");
	ScreenPrint(0, 4, "┃                                                                      ┃");
	ScreenPrint(0, 5, "┃                                                                      ┃");
	ScreenPrint(0, 6, "┃                                                                      ┃");
	ScreenPrint(0, 7, "┃                                                                      ┃");
	ScreenPrint(0, 8, "┃                                                                      ┃");
	ScreenPrint(0, 9, "┃                                                                      ┃");
	ScreenPrint(0, 10, "┃                                                                      ┃");
	ScreenPrint(0, 11, "┛                                                                      ┗");
	ScreenPrint(0, 12, "                                                                        ");
	ScreenPrint(0, 13, "┓                                                                      ┏");
	ScreenPrint(0, 14, "┃                                                                      ┃");
	ScreenPrint(0, 15, "┃                                                                      ┃");
	ScreenPrint(0, 16, "┃                                                                      ┃");
	ScreenPrint(0, 17, "┃                                                                      ┃");
	ScreenPrint(0, 18, "┃                                                                      ┃");
	ScreenPrint(0, 19, "┃                                                                      ┃");
	ScreenPrint(0, 20, "┃                                                                      ┃");
	ScreenPrint(0, 21, "┃                                                                      ┃");
	ScreenPrint(0, 22, "┃                                                                      ┃");
	ScreenPrint(0, 23, "┃                                                                      ┃");
	ScreenPrint(0, 24, "┃                                                                      ┃");
	ScreenPrint(0, 25, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void stdRightRoom(void)
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┛                                                                      ┃\n");
	printf("                                             ___________               ┃\n");
	printf("┓                                           |     _     |              ┃\n");
	printf("┃                                           |    |_|    |              ┃\n");
	printf("┃                                           |___________|              ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                     _________        ┃\n");
	printf("┃                                                    |_ Table _|       ┃\n");
	printf("┃                                                      ||   ||         ┃\n");
	printf("┃                                                      ||   ||         ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}


void RightRoom(void)
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                                                      ┃");
	ScreenPrint(0, 2, "┃                                                                      ┃");
	ScreenPrint(0, 3, "┃                                                                      ┃");
	ScreenPrint(0, 4, "┃                                                                      ┃");
	ScreenPrint(0, 5, "┃                                                                      ┃");
	ScreenPrint(0, 6, "┃                                                                      ┃");
	ScreenPrint(0, 7, "┃                                                                      ┃");
	ScreenPrint(0, 8, "┃                                                                      ┃");
	ScreenPrint(0, 9, "┃                                                                      ┃");
	ScreenPrint(0, 10, "┃                                                                      ┃");
	ScreenPrint(0, 11, "┛                                                                      ┃");
	ScreenPrint(0, 12, "                                             ___________               ┃ ");
	ScreenPrint(0, 13, "┓                                           |     _     |              ┃");
	ScreenPrint(0, 14, "┃                                           |    |_|    |              ┃");
	ScreenPrint(0, 15, "┃                                           |___________|              ┃ ");
	ScreenPrint(0, 16, "┃                                                                      ┃");
	ScreenPrint(0, 17, "┃                                                                      ┃");
	ScreenPrint(0, 18, "┃                                                                      ┃");
	ScreenPrint(0, 19, "┃                                                                      ┃");
	ScreenPrint(0, 20, "┃                                                     _________        ┃");
	ScreenPrint(0, 21, "┃                                                    |_ Table _|       ┃");
	ScreenPrint(0, 22, "┃                                                      ||   ||         ┃");
	ScreenPrint(0, 23, "┃                                                      ||   ||         ┃");
	ScreenPrint(0, 24, "┃                                                                      ┃");
	ScreenPrint(0, 25, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void stdLeftRoom(void) {
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃     _______                                                          ┃\n");
	printf("┃    |_o_|_o_|                                                         ┗\n");
	printf("┃    |___o___|                                                          \n");
	printf("┃    |___o___|                                                         ┏\n");
	printf("┃    |___o___|                                                         ┃\n");
	printf("┃     ||   ||                                                          ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void LeftRoom(void) {
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                                                                      ┃");
	ScreenPrint(0, 2, "┃                                                                      ┃");
	ScreenPrint(0, 3, "┃                                                                      ┃");
	ScreenPrint(0, 4, "┃                                                                      ┃");
	ScreenPrint(0, 5, "┃                                                                      ┃");
	ScreenPrint(0, 6, "┃                                                                      ┃");
	ScreenPrint(0, 7, "┃                                                                      ┃");
	ScreenPrint(0, 8, "┃                                                                      ┃");
	ScreenPrint(0, 9, "┃                                                                      ┃");
	ScreenPrint(0, 10, "┃                                                                      ┃");
	ScreenPrint(0, 11, "┃     _______                                                          ┗");
	ScreenPrint(0, 12, "┃    |_o_|_o_|                                                          ");
	ScreenPrint(0, 13, "┃    |___o___|                                                         ┏");
	ScreenPrint(0, 14, "┃    |___o___|                                                         ┃");
	ScreenPrint(0, 15, "┃    |___o___|                                                         ┃");
	ScreenPrint(0, 16, "┃     ||   ||                                                          ┃");
	ScreenPrint(0, 17, "┃                                                                      ┃");
	ScreenPrint(0, 18, "┃                                                                      ┃");
	ScreenPrint(0, 19, "┃                                                                      ┃");
	ScreenPrint(0, 20, "┃                                                                      ┃");
	ScreenPrint(0, 21, "┃                                                                      ┃");
	ScreenPrint(0, 22, "┃                                                                      ┃");
	ScreenPrint(0, 23, "┃                                                                      ┃");
	ScreenPrint(0, 24, "┃                                                                      ┃");
	ScreenPrint(0, 25, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void stdInnerRoom(void)
{
	printf("┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                      ┃                       ┃                       ┃\n");
	printf("┃                      ┃       IRON PLATE      ┃                       ┃\n");
	printf("┃                      ┗━━━━━━━━━━━━━━━━━━━━━━━┛                       ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┃                                                                      ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void InnerRoom(void)
{
	ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━┓");
	ScreenPrint(0, 1, "┃                      ┃                       ┃                       ┃");
	ScreenPrint(0, 2, "┃                      ┃       IRON PLATE      ┃                       ┃");
	ScreenPrint(0, 3, "┃                      ┗━━━━━━━━━━━━━━━━━━━━━━━┛                       ┃");
	ScreenPrint(0, 4, "┃                                                                      ┃");
	ScreenPrint(0, 5, "┃                                                                      ┃");
	ScreenPrint(0, 6, "┃                                                                      ┃");
	ScreenPrint(0, 7, "┃                                                                      ┃");
	ScreenPrint(0, 8, "┃                                                                      ┃");
	ScreenPrint(0, 9, "┃                                                                      ┃");
	ScreenPrint(0, 10, "┃                                                                      ┃");
	ScreenPrint(0, 11, "┃                                                                      ┃");
	ScreenPrint(0, 12, "┃                                                                      ┃");
	ScreenPrint(0, 13, "┃                                                                      ┃");
	ScreenPrint(0, 14, "┃                                                                      ┃");
	ScreenPrint(0, 15, "┃                                                                      ┃");
	ScreenPrint(0, 16, "┃                                                                      ┃");
	ScreenPrint(0, 17, "┃                                                                      ┃");
	ScreenPrint(0, 18, "┃                                                                      ┃");
	ScreenPrint(0, 19, "┃                                                                      ┃");
	ScreenPrint(0, 20, "┃                                                                      ┃");
	ScreenPrint(0, 21, "┃                                                                      ┃");
	ScreenPrint(0, 22, "┃                                                                      ┃");
	ScreenPrint(0, 23, "┃                                                                      ┃");
	ScreenPrint(0, 24, "┃                                                                      ┃");
	ScreenPrint(0, 25, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}