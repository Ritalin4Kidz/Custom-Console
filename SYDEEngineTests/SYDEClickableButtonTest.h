#pragma once
#include "SYDEAbstractUITest.h"

class SYDEClickableButtonTestWindow : public SYDEWindowGame {
public:
	SYDEClickableButtonTestWindow();
	virtual ~SYDEClickableButtonTestWindow() {}

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;

	static void toggleButtonResult();

	static bool getButtonResult();

	static bool m_ButtonPressed;

private:
	SYDEClickableButton m_Button;
};


class SYDEClickableButtonTest : public SYDEAbstractUITest
{
public:
	SYDEClickableButtonTest() { TestName = "SYDE UI Clickable Button Tests"; }

	TestResult BasicClickTest() override;

private:
};