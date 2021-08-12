#pragma once
#include "SYDEEngineBaseTest.h"
class SYDEOptionCyclerTestWindow : public SYDEWindowGame {
public:
	SYDEOptionCyclerTestWindow() {  }
	virtual ~SYDEOptionCyclerTestWindow() {}

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;


private:
	//SYDESlider m_Slider = SYDESlider(Vector2(4, 18), 20, WHITE, BRIGHTWHITE_BRIGHTWHITE_BG);
};


class SYDEOptionCyclerTest : public SYDEEngineBaseTest
{
public:
	SYDEOptionCyclerTest() { TestName = "SYDE UI Option Cycler Tests"; }

	TestResult runTests() override;

	TestResult BasicClickTest();

private:
};