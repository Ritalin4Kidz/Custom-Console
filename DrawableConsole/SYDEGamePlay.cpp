#include "pch.h"
#include "SYDEGamePlay.h"

using namespace std;
ConsoleWindow SYDEGamePlay::play_game(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight)
{
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
	SetConsoleCursorPosition(hOut, start);
	return SYDE_GAME->window_draw_game(window, windowWidth, windowHeight);
}
