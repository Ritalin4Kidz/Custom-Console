#include "SYDEOptionCyclerTest.h"

TestResult SYDEOptionCyclerTest::runTests()
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

TestResult SYDEOptionCyclerTest::BasicClickTest()
{
	return TestResult("", false);
}

ConsoleWindow SYDEOptionCyclerTestWindow::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	return window;
}
