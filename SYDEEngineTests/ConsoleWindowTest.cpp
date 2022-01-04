
#include "ConsoleWindowTest.h"

#include "pch.h"

TestResult ConsoleWindowTest::runTests()
{
	TestResult mainResult;
	TestResult result;
	result = ConsoleWindowPointColourTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	return mainResult;
}

TestResult ConsoleWindowTest::ConsoleWindowPointColourTest()
{
	ConsoleWindow window(20, false);
	window.initialize(40, 20);
	for (int i = 0; i < 20; i++)
	{
		for (int ii = 0; ii < 20; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}
	if (window.getTextColourAtPoint(Vector2(25, 13)) != WHITE)
	{
		return TestResult("ConsoleWindowPointTest: Unexpected Colour In Window\n", false);
	}
	if (window.getTextColourAtPoint(Vector2(14, 13)) != BLACK)
	{
		return TestResult("ConsoleWindowPointTest: Unexpected Colour In Window\n", false);
	}
	return TestResult("ConsoleWindowPointTest Ran Successfully \n", true);
}
