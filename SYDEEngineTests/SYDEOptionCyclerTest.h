#pragma once
#include "SYDEAbstractUITest.h"
class SYDEOptionCyclerTestWindow : public SYDEWindowGame {
public:
	SYDEOptionCyclerTestWindow() {  }
	virtual ~SYDEOptionCyclerTestWindow() {}

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;


private:
	//SYDESlider m_Slider = SYDESlider(Vector2(4, 18), 20, WHITE, BRIGHTWHITE_BRIGHTWHITE_BG);
};


class SYDEOptionCyclerTest : public SYDEAbstractUITest
{
public:
	SYDEOptionCyclerTest() { TestName = "SYDE UI Option Cycler Tests"; }

private:
};