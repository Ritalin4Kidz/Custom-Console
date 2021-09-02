#pragma once
#include "SYDEAbstractUITest.h"
class SYDEClickableTextboxTestWindow : public SYDEWindowGame {
public:
	SYDEClickableTextboxTestWindow();
	virtual ~SYDEClickableTextboxTestWindow() {}

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;

private:
	SYDEClickableTextBox m_Textbox;
};


class SYDEClickableTextboxTest : public SYDEAbstractUITest
{
public:
	SYDEClickableTextboxTest() { TestName = "SYDE UI Clickable Textbox Tests"; }

private:
};