#pragma once
#include "ConsoleWindow.h"
#include "ConsoleWindow3D.h"
/// <summary>
/// SYDE Window Game Interface, for building game scenes
/// </summary>
__interface SYDEWindowGame
{
	/// <summary>
	/// The main function on which SYDEGamePlay runs
	/// </summary>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <returns></returns>
	virtual ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) {}
};


__interface SYDEWindowGame3D
{
	virtual ConsoleWindow3D window_draw_game3D(ConsoleWindow3D window, int windowWidth, int windowHeight) {}
};