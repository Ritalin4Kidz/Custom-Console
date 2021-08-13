#include "pch.h"

#include "SYDEClickableButtonTest.h"

bool SYDEClickableButtonTestWindow::m_ButtonPressed = false;

void ButtonFunc()
{
	SYDEClickableButtonTestWindow::toggleButtonResult();
}


SYDEClickableButtonTestWindow::SYDEClickableButtonTestWindow()
{
	m_Button = SYDEClickableButton("TestButton", Vector2(4, 18), Vector2(10, 1), BLACK_RED_BG, false);
	m_Button.SetFunc(ButtonFunc);
}

ConsoleWindow SYDEClickableButtonTestWindow::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	window = m_Button.draw_ui(window);
	return window;
}

void SYDEClickableButtonTestWindow::toggleButtonResult()
{
	m_ButtonPressed = !m_ButtonPressed;
}

bool SYDEClickableButtonTestWindow::getButtonResult()
{
	return m_ButtonPressed;
}

TestResult SYDEClickableButtonTest::BasicClickTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDEClickableButtonTestWindow m_Test;
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	//CALL A FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (SYDEClickableButtonTestWindow::getButtonResult())
	{
		return TestResult("BasicClickTest: Result Was True When Expected False", false);
	}
	SYDEKeyCode::SetLastClickPosition(Vector2(9, 18));
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyDown();
	//CALL THE NEXT FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (!SYDEClickableButtonTestWindow::getButtonResult())
	{
		return TestResult("BasicClickTest: Result Was False When Expected True", false);
	}

	//REFRESH FRAME
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);

	SYDEKeyCode::SetLastClickPosition(Vector2(15, 16));
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyDown();
	//CALL THE NEXT FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (!SYDEClickableButtonTestWindow::getButtonResult())
	{
		return TestResult("BasicClickTest: Result Was False When Expected True", false);
	}

	return TestResult("Basic Click Test Ran Successfully", true);
}
