#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define ROOMS 4
#define LOBBY 0
#define LEFT_ROOM 1
#define INNER_ROOM 2
#define RIGHT_ROOM 3
#define EXIT 4

#define CHEST 11
#define PLATE 21
#define SAFEBOX 31
#define TABLE 32

#define DIGITS 4
#define LETTERS 10
#define TRIES 10

#ifndef _STRUCT_DEFINED
typedef struct _item {
	bool card_key;
	bool teddy_bear;
	bool key;
	bool rose_hint;
} ITEM;

typedef struct _player {
	int nX, nY;
	int room;
	int object;
	bool visited[ROOMS];
	ITEM item;
} PLAYER;
#define _STRUCT_DEFINED
#endif

void intro_b(void);
void intro_f(void);
void intro_p(void);
void intro_h(void);

int bulls_and_cows(void);
int flower_language(void);
int place(void);
int hangman(void);

void strPrint(char *str);
void txtPrint(char *file_name);

void intro(void);
void gameOver(void);
void outro(void);

void stdLobby(void);
void stdLeftRoom(void);
void stdRightRoom(void);
void stdInnerRoom(void);

void Lobby(void);
void LeftRoom(void);
void RightRoom(void);
void InnerRoom(void);

void gotoxy(int x, int y);
void stdoutClear(void);

void Move(void);
bool Crush(int num);
void Render(int num);

void ScreenInit(void);
void ScreenFlipping(void);
void ScreenClear(void);
void ScreenRelease(void);
void ScreenPrint(int x, int y, char *string);
void SetColor(unsigned short color);