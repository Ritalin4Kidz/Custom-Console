
#include "SYDESliderTest.h"

#include "pch.h"

TestResult SYDESliderTest::runTests()
{
	TestResult mainResult;
	TestResult result;
	result = BasicClickTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	return mainResult;
}

TestResult SYDESliderTest::BasicClickTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDESliderTestWindow m_Test;
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	//CALL A FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (m_Test.getSliderValue() != 0)
	{
		return TestResult("BasicClickTest: Expected 0 But Got " + to_string(m_Test.getSliderValue()), false);
	}
	SYDEKeyCode::SetLastClickPosition(Vector2(9,18));
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyDown();
	//CALL THE NEXT FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (m_Test.getSliderValue() != 5)
	{
		return TestResult("BasicClickTest: Expected 5 But Got " + to_string(m_Test.getSliderValue()), false);
	}
	return TestResult("Basic Click Test Ran Successfully", true);
}

ConsoleWindow SYDESliderTestWindow::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
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
