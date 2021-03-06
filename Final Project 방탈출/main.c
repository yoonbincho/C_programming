#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include "stray.h"

PLAYER player;
char strPlayer[] = "≒";

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
	puts("  蝶饜葬蒂 霞чж溥賊 Enter蒂 援腦衛螃 . . .\n");
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
				strPrint("旎堅朝 蘋萄酈蒂 渣 菴縑 綠塵廓�ㄧ� 殮溘п撿 и棻.							\n");
				if (player.item.card_key) {
					if (player.item.rose_hint) {
						strPrint("\'鞅緊-\'														\n");
						strPrint("釭朝 離碟�� 蘋萄酈蒂 旎堅縑 渣 菴 懍�ㄧ� 殮溘ц棻.					\n");
						if (flower_language())
							gameOver();
						txtPrint("right_room-2.txt");
						player.item.teddy_bear = true;
						player.visited[RIGHT_ROOM] = true;
					}
					else
						strPrint("憾, 綠塵廓�ˋ� 渠и �爩扇� 橈戲棲 寞縑憮 �爩捂� 渦 瓊嬴爾紫煙 ж濠.	\n");
				}
				else
					strPrint("憾, 蘋萄酈陛 橈戲棲 棻艇 寞縑憮 蘋萄酈蒂 瓊嬴爾紫煙 ж濠.				\n");
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
					strPrint("憾, 繹っ擊 翮 濰纂陛 橈戲棲 濰纂蒂 瓊嬴爾紫煙 ж濠.					\n");
				player.object = false;
				break;
			}
		}
		else {
			switch (player.room) {
			case LEFT_ROOM:
				if (player.visited[LEFT_ROOM]) {
					stdLobby();
					strPrint("檜嘐 諮湍 寞檜棻. 棻艇 寞戲煎 檜翕п爾濠.								\n");
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
					strPrint("檜嘐 諮湍 寞檜棻. 棻艇 寞戲煎 檜翕п爾濠.								\n");
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
					strPrint("檜嘐 諮湍 寞檜棻. 棻艇 寞戲煎 檜翕п爾濠.								\n");
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
					strPrint("雖旎擎 懍�ˋ� 婦и �爩扇� 橈戲棲 寞擊 渦 萃楝爾紫煙 ж濠.				\n");
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
	printf("    _,--._.-,\n   /Ｊ_r-,Ｊ_ )\n Ｈ-.) _:=:_/ (Ｊ\nＪ Ｊ'     Ｊ/  )\n L.:-. _.:|-:  /\n <_:-:Ｊ: :  /\n   Ｊ-._( Ｊ\n    ___   ＪＪ,       ______\n    Ｊ .:-. ＪＪ  .  /.-:_./\n       Ｊ._   .ＪＪ/.- _./\n          Ｊ--..Ｊ(.--/\n");
	printf("    ﹥﹥﹥﹥﹥       ﹥           ﹥      ﹥﹥﹥﹥﹥﹥﹥ ﹥  \n");
	printf("            ﹥       ﹥           ﹥            ﹥       ﹥  \n");
	printf("            ﹥       ﹥           ﹥﹥﹥      ﹥  ﹥     ﹥  \n");
	printf("            ﹥       ﹥﹥﹥﹥     ﹥        ﹥      ﹥   ﹥﹥﹥  \n");
	printf("                                  ﹥       ﹥        ﹥  ﹥  \n");
	printf("   ﹥﹥﹥﹥﹥﹥﹥     ﹥﹥﹥﹥﹥﹥﹥                     ﹥  \n");
	printf("                      ﹥          ﹥                     ﹥  \n");
	printf("                      ﹥          ﹥                     ﹥  \n");
	printf("                      ﹥﹥﹥﹥﹥﹥﹥                        \n");
	printf("                            ﹤﹤﹤﹤﹤         ﹤﹤         ﹤     ﹤﹤﹤﹤﹤﹤﹤ ﹤ \n");
	printf("                                    ﹤       ﹤    ﹤   ﹤﹤﹤           ﹤       ﹤  \n");
	printf("                                    ﹤       ﹤    ﹤       ﹤         ﹤  ﹤     ﹤ \n");
	printf("                                    ﹤         ﹤﹤     ﹤﹤﹤       ﹤      ﹤   ﹤﹤﹤  \n");
	printf("                                                            ﹤      ﹤        ﹤  ﹤  \n");
	printf("                           ﹤﹤﹤﹤﹤﹤﹤                   ﹤                    ﹤  \n");
	printf("                                                            ﹤                    ﹤  \n\n");
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
	printf("   ﹥﹥﹥﹥﹥   ﹥    ﹥    ﹥﹥﹥﹥  \n");
	printf("       ﹥       ﹥    ﹥    ﹥        \n");
	printf("       ﹥       ﹥﹥﹥﹥    ﹥﹥﹥﹥  \n");
	printf("       ﹥       ﹥    ﹥    ﹥        \n");
	printf("       ﹥       ﹥    ﹥    ﹥﹥﹥﹥  \n");
	printf("                                      \n");
	printf("    ﹤﹤﹤﹤    ﹤      ﹤   ﹤﹤﹤   \n");
	printf("    ﹤          ﹤ ﹤   ﹤   ﹤    ﹤   \n");
	printf("    ﹤﹤﹤﹤    ﹤  ﹤  ﹤   ﹤     ﹤  \n");
	printf("    ﹤          ﹤    ﹤﹤   ﹤    ﹤  \n");
	printf("    ﹤﹤﹤﹤    ﹤      ﹤   ﹤﹤﹤    \n");
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
	// �飛� 幗ぷ 2偃 儅撩

	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//醴憮 獗晦晦
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
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("旭                                                                      曲\n");
	printf("                                                                        \n");
	printf("旬                                                                      旨\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");
}

void Lobby(void)
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                                                      早");
	ScreenPrint(0, 2, "早                                                                      早");
	ScreenPrint(0, 3, "早                                                                      早");
	ScreenPrint(0, 4, "早                                                                      早");
	ScreenPrint(0, 5, "早                                                                      早");
	ScreenPrint(0, 6, "早                                                                      早");
	ScreenPrint(0, 7, "早                                                                      早");
	ScreenPrint(0, 8, "早                                                                      早");
	ScreenPrint(0, 9, "早                                                                      早");
	ScreenPrint(0, 10, "早                                                                      早");
	ScreenPrint(0, 11, "旭                                                                      曲");
	ScreenPrint(0, 12, "                                                                        ");
	ScreenPrint(0, 13, "旬                                                                      旨");
	ScreenPrint(0, 14, "早                                                                      早");
	ScreenPrint(0, 15, "早                                                                      早");
	ScreenPrint(0, 16, "早                                                                      早");
	ScreenPrint(0, 17, "早                                                                      早");
	ScreenPrint(0, 18, "早                                                                      早");
	ScreenPrint(0, 19, "早                                                                      早");
	ScreenPrint(0, 20, "早                                                                      早");
	ScreenPrint(0, 21, "早                                                                      早");
	ScreenPrint(0, 22, "早                                                                      早");
	ScreenPrint(0, 23, "早                                                                      早");
	ScreenPrint(0, 24, "早                                                                      早");
	ScreenPrint(0, 25, "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void stdRightRoom(void)
{
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("旭                                                                      早\n");
	printf("                                             ___________               早\n");
	printf("旬                                           |     _     |              早\n");
	printf("早                                           |    |_|    |              早\n");
	printf("早                                           |___________|              早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                     _________        早\n");
	printf("早                                                    |_ Table _|       早\n");
	printf("早                                                      ||   ||         早\n");
	printf("早                                                      ||   ||         早\n");
	printf("早                                                                      早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");
}


void RightRoom(void)
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                                                      早");
	ScreenPrint(0, 2, "早                                                                      早");
	ScreenPrint(0, 3, "早                                                                      早");
	ScreenPrint(0, 4, "早                                                                      早");
	ScreenPrint(0, 5, "早                                                                      早");
	ScreenPrint(0, 6, "早                                                                      早");
	ScreenPrint(0, 7, "早                                                                      早");
	ScreenPrint(0, 8, "早                                                                      早");
	ScreenPrint(0, 9, "早                                                                      早");
	ScreenPrint(0, 10, "早                                                                      早");
	ScreenPrint(0, 11, "旭                                                                      早");
	ScreenPrint(0, 12, "                                             ___________               早 ");
	ScreenPrint(0, 13, "旬                                           |     _     |              早");
	ScreenPrint(0, 14, "早                                           |    |_|    |              早");
	ScreenPrint(0, 15, "早                                           |___________|              早 ");
	ScreenPrint(0, 16, "早                                                                      早");
	ScreenPrint(0, 17, "早                                                                      早");
	ScreenPrint(0, 18, "早                                                                      早");
	ScreenPrint(0, 19, "早                                                                      早");
	ScreenPrint(0, 20, "早                                                     _________        早");
	ScreenPrint(0, 21, "早                                                    |_ Table _|       早");
	ScreenPrint(0, 22, "早                                                      ||   ||         早");
	ScreenPrint(0, 23, "早                                                      ||   ||         早");
	ScreenPrint(0, 24, "早                                                                      早");
	ScreenPrint(0, 25, "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void stdLeftRoom(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早     _______                                                          早\n");
	printf("早    |_o_|_o_|                                                         曲\n");
	printf("早    |___o___|                                                          \n");
	printf("早    |___o___|                                                         旨\n");
	printf("早    |___o___|                                                         早\n");
	printf("早     ||   ||                                                          早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");
}

void LeftRoom(void) {
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                                                                      早");
	ScreenPrint(0, 2, "早                                                                      早");
	ScreenPrint(0, 3, "早                                                                      早");
	ScreenPrint(0, 4, "早                                                                      早");
	ScreenPrint(0, 5, "早                                                                      早");
	ScreenPrint(0, 6, "早                                                                      早");
	ScreenPrint(0, 7, "早                                                                      早");
	ScreenPrint(0, 8, "早                                                                      早");
	ScreenPrint(0, 9, "早                                                                      早");
	ScreenPrint(0, 10, "早                                                                      早");
	ScreenPrint(0, 11, "早     _______                                                          曲");
	ScreenPrint(0, 12, "早    |_o_|_o_|                                                          ");
	ScreenPrint(0, 13, "早    |___o___|                                                         旨");
	ScreenPrint(0, 14, "早    |___o___|                                                         早");
	ScreenPrint(0, 15, "早    |___o___|                                                         早");
	ScreenPrint(0, 16, "早     ||   ||                                                          早");
	ScreenPrint(0, 17, "早                                                                      早");
	ScreenPrint(0, 18, "早                                                                      早");
	ScreenPrint(0, 19, "早                                                                      早");
	ScreenPrint(0, 20, "早                                                                      早");
	ScreenPrint(0, 21, "早                                                                      早");
	ScreenPrint(0, 22, "早                                                                      早");
	ScreenPrint(0, 23, "早                                                                      早");
	ScreenPrint(0, 24, "早                                                                      早");
	ScreenPrint(0, 25, "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void stdInnerRoom(void)
{
	printf("旨收收收收收收收收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早                      早                       早                       早\n");
	printf("早                      早       IRON PLATE      早                       早\n");
	printf("早                      曲收收收收收收收收收收收收收收收收收收收收收收收旭                       早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("早                                                                      早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");
}

void InnerRoom(void)
{
	ScreenPrint(0, 0, "旨收收收收收收收收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收收收收收收收收收收旬");
	ScreenPrint(0, 1, "早                      早                       早                       早");
	ScreenPrint(0, 2, "早                      早       IRON PLATE      早                       早");
	ScreenPrint(0, 3, "早                      曲收收收收收收收收收收收收收收收收收收收收收收收旭                       早");
	ScreenPrint(0, 4, "早                                                                      早");
	ScreenPrint(0, 5, "早                                                                      早");
	ScreenPrint(0, 6, "早                                                                      早");
	ScreenPrint(0, 7, "早                                                                      早");
	ScreenPrint(0, 8, "早                                                                      早");
	ScreenPrint(0, 9, "早                                                                      早");
	ScreenPrint(0, 10, "早                                                                      早");
	ScreenPrint(0, 11, "早                                                                      早");
	ScreenPrint(0, 12, "早                                                                      早");
	ScreenPrint(0, 13, "早                                                                      早");
	ScreenPrint(0, 14, "早                                                                      早");
	ScreenPrint(0, 15, "早                                                                      早");
	ScreenPrint(0, 16, "早                                                                      早");
	ScreenPrint(0, 17, "早                                                                      早");
	ScreenPrint(0, 18, "早                                                                      早");
	ScreenPrint(0, 19, "早                                                                      早");
	ScreenPrint(0, 20, "早                                                                      早");
	ScreenPrint(0, 21, "早                                                                      早");
	ScreenPrint(0, 22, "早                                                                      早");
	ScreenPrint(0, 23, "早                                                                      早");
	ScreenPrint(0, 24, "早                                                                      早");
	ScreenPrint(0, 25, "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}