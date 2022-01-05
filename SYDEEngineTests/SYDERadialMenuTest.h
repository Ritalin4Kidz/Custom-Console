#pragma once
#include "SYDEAbstractUITest.h"
class SYDERadialMenuTestWindow : public SYDEWindowGame {
public:
	SYDERadialMenuTestWindow() { }
	virtual ~SYDERadialMenuTestWindow() {}

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow initialize_window(ConsoleWindow window, int windowWidth, int windowHeight)
	{
		for (int i = 0; i < windowHeight; i++)
		{
			for (int ii = 0; ii < windowWidth; ii++)
			{
				window.addToLine(i, " ", BLACK);
			}
		}
		return window;
	}

	SYDERadialMenu_Basic m_Radial = SYDERadialMenu_Basic(Vector2(30, 10),
		SYDERadialOption("Health", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "H", Vector2(0, 1)),
		SYDERadialOption("Mana", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "M", Vector2(0, 1)),
		SYDERadialOption("Exit", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "X", Vector2(0, 1)),
		SYDERadialOption("Options", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "O", Vector2(0, 1)));
};


class SYDERadialMenuTest : public SYDEAbstractUITest
{
public:
	SYDERadialMenuTest() { TestName = "SYDE Radial Menu Tests"; }

	TestResult BasicClickTest() override;
	TestResult BasicDrawTest() override;

private:
};
