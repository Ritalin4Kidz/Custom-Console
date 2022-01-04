#pragma once
#include "SYDEAbstractUITest.h"


class SYDEVerticalSliderTestWindow : public SYDEWindowGame {
public:
	SYDEVerticalSliderTestWindow() {  }
	virtual ~SYDEVerticalSliderTestWindow() {}

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

	int getSliderValue() { return m_Slider.getValue(); }

private:
	SYDEVerticalSlider m_Slider = SYDEVerticalSlider(Vector2(4, 1), 18, WHITE, BRIGHTWHITE_BRIGHTWHITE_BG);
};


class SYDEVerticalSliderTest : public SYDEAbstractUITest
{
public:
	SYDEVerticalSliderTest() { TestName = "SYDE UI Vertical Slider Tests"; }

	TestResult BasicClickTest() override;
	TestResult BasicDrawTest() override;

private:
};