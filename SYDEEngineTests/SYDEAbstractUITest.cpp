#include "pch.h"
#include "SYDEAbstractUITest.h"
TestResult SYDEAbstractUITest::runTests()
{
	TestResult mainResult;
	TestResult result;
	result = BasicClickTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	result = BasicDrawTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	return mainResult;
}

TestResult SYDEAbstractUITest::BasicClickTest()
{
	return TestResult("BasicClickTest: Not Implemented Error\n", false);
}

TestResult SYDEAbstractUITest::BasicDrawTest()
{
	return TestResult("BasicDrawTest: Not Implemented Error\n", false);
}
