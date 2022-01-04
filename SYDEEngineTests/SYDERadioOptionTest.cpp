#include "SYDERadioOptionTest.h"

ConsoleWindow SYDERadioOptionTestWindow::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	window = m_ButtonMenu.draw_ui(window);
	return window;
}

TestResult SYDERadioOptionTest::BasicClickTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDERadioOptionTestWindow m_Test;
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	//CALL A FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (m_Test.m_ButtonMenu.getChecked() != -1)
	{
		return TestResult("BasicClickTest: Expected -1 But Got " + to_string(m_Test.m_ButtonMenu.getChecked()), false);
	}
	SYDEKeyCode::SetLastClickPosition(Vector2(15, 1));
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyDown();
	//CALL THE NEXT FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (m_Test.m_ButtonMenu.getChecked() != 0)
	{
		return TestResult("BasicClickTest: Expected 0 But Got " + to_string(m_Test.m_ButtonMenu.getChecked()), false);
	}

	return TestResult("Basic Click Test Ran Successfully", true);
}

TestResult SYDERadioOptionTest::BasicDrawTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDERadioOptionTestWindow m_Test;
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	window = m_Test.initialize_window(window, windowWidth, windowHeight);
	//CALL A FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	string sliderTextLine = window.getLine(1).getCurrentText();
	if (sliderTextLine.find("This Is 1 Test") == std::string::npos)
	{
		return TestResult("BasicDrawTest: Failed To Find Radio Option Text", false);
	}
	return TestResult("Basic Draw Test Ran Successfully", true);
}
