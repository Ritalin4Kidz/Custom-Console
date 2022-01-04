#pragma once
#include "SYDEAbstractUITest.h"
class SYDERadioOptionTestWindow : public SYDEWindowGame {
public:
	SYDERadioOptionTestWindow() { }
	virtual ~SYDERadioOptionTestWindow() {}

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

	SYDERadioButtonMenu m_ButtonMenu = SYDERadioButtonMenu(Vector2(0, 1), vector<SYDERadioOption>({
	SYDERadioOption(string("This Is 1 Test"), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG),
	SYDERadioOption(string("This Is 2 Test"), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG),
	SYDERadioOption(string("This Is 3 Test"), BRIGHTWHITE, BLACK_BRIGHTWHITE_BG)
		}));
};


class SYDERadioOptionTest : public SYDEAbstractUITest
{
public:
	SYDERadioOptionTest() { TestName = "SYDE Radio Option Tests"; }

	TestResult BasicClickTest() override;
	TestResult BasicDrawTest() override;

private:
};