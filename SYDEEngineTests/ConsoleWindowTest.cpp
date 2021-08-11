
#include "ConsoleWindowTest.h"

#include "pch.h"

TestResult ConsoleWindowTest::runTests()
{
	TestResult mainResult;
	TestResult result;
	result = ConsoleWindowPointTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	return mainResult;
}

TestResult ConsoleWindowTest::ConsoleWindowPointTest()
{
	ConsoleWindow window(20, false);
	window.initialize(40, 20);
	if (window.getTextAtPoint(Vector2(25, 13)) != " ")
	{
		return TestResult("ConsoleWindowPointTest: Unexpected Text In Window \n", false);
	}
	return TestResult("ConsoleWindowPointTest Ran Successfully \n", true);
}
