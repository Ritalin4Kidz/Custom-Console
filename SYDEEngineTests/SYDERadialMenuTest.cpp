#include "SYDERadialMenuTest.h"

ConsoleWindow SYDERadialMenuTestWindow::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	window = m_Radial.draw_ui(window);
	return window;
}

TestResult SYDERadialMenuTest::BasicClickTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDERadialMenuTestWindow m_Test;
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	//CALL A FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	SYDEKeyCode::ForceLastMousePosition(Vector2(0, 0));
	if (m_Test.m_Radial.getHighlightedIndex() != -1)
	{
		return TestResult("BasicClickTest: Expected -1 But Got " + to_string(m_Test.m_Radial.getHighlightedIndex()), false);
	}
	SYDEKeyCode::ForceLastMousePosition(Vector2(22, 10));
	//CALL THE NEXT FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	if (m_Test.m_Radial.getHighlightedIndex() != 1)
	{
		return TestResult("BasicClickTest: Expected 1 But Got " + to_string(m_Test.m_Radial.getHighlightedIndex()), false);
	}

	return TestResult("Basic Click Test Ran Successfully", true);
}

TestResult SYDERadialMenuTest::BasicDrawTest()
{
	//INIT TEST
	SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
	int windowWidth = 40;
	const int windowHeight = 20;
	ConsoleWindow window(windowHeight, false);
	SYDERadialMenuTestWindow m_Test;
	window = m_Test.initialize_window(window, windowWidth, windowHeight);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	//CALL A FRAME
	SYDEKeyCode::ForceLastMousePosition(Vector2(0, 0));
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	string sliderTextLine = window.getLine(1).getCurrentText();
	if (sliderTextLine.find("Mana") != std::string::npos)
	{
		return TestResult("BasicDrawTest: Found String When Null Expected", false);
	}
	SYDEKeyCode::ForceLastMousePosition(Vector2(22, 10));
	//CALL THE NEXT FRAME
	window = SYDEGamePlay::play_test_func(&m_Test, window, windowWidth, windowHeight, deltaTime);
	sliderTextLine = window.getLine(1).getCurrentText();
	if (sliderTextLine.find("Mana") == std::string::npos)
	{
		return TestResult("BasicDrawTest: Could not find string MANA in: " + sliderTextLine, false);
	}

	return TestResult("Basic Draw Test Ran Successfully", true);
}
