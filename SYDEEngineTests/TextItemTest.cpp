
#include "TextItemTest.h"

#include "pch.h"

TestResult TextItemTest::runTests()
{
	TestResult mainResult;
	TestResult result;
	result = initializeTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	return mainResult;
}

TestResult TextItemTest::initializeTest()
{
	TextItem t1;
	if (t1.getChar() != ' ' || t1.getColour() != 0)
	{
		return TestResult("TextItem t1 did not initialize properly \n", false);
	}
	TextItem t2('@',67);
	if (t2.getChar() != '@' || t2.getColour() != 67)
	{
		return TestResult("TextItem t2 did not initialize properly \n", false);
	}
	TextItem t3(t2);
	if (t3.getChar() != '@' || t3.getColour() != 67)
	{
		return TestResult("TextItem t3 did not initialize properly \n", false);
	}
	return TestResult("TextItem Initialize Test Was Successful \n", true);
}
