
#include "SYDEVerticalSliderTest.h"

#include "pch.h"

TestResult SYDEVerticalSliderTest::BasicClickTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDEVerticalSliderTestWindow m_Test;
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	//CALL A FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (m_Test.getSliderValue() != 0)
	{
		return TestResult("BasicClickTest: Expected 0 But Got " + to_string(m_Test.getSliderValue()), false);
	}
	SYDEKeyCode::SetLastClickPosition(Vector2(4, 16));
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyDown();
	//CALL THE NEXT FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (m_Test.getSliderValue() != 15)
	{
		return TestResult("BasicClickTest: Expected 15 But Got " + to_string(m_Test.getSliderValue()), false);
	}
	return TestResult("Basic Click Test Ran Successfully", true);
}

TestResult SYDEVerticalSliderTest::BasicDrawTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDEVerticalSliderTestWindow m_Test;
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	window = m_Test.initialize_window(window, windowWidth, windowHeight);
	//CALL A FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	//CHECK SLIDER IN EVERY LINE
	for (int i = 2; i < 19; i++)
	{
		if (window.getCharAtPoint(Vector2(4, i)) != '|')
		{
			return TestResult("BasicDrawTest: Slider Not Found In Line-" + std::to_string(i), false);
		}
	}
	return TestResult("Basic Draw Test Ran Successfully", true);
}

ConsoleWindow SYDEVerticalSliderTestWindow::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	window = m_Slider.draw_ui(window);
	return window;
}