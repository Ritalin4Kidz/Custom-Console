#include "pch.h"
#include "SYDEKeyCodeTest.h"

TestResult SYDEKeyCodeTest::runTests()
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

TestResult SYDEKeyCodeTest::initializeTest()
{
	//NOT INITIALIZED, SO WE SHOULD BE GETTING THE DEFAULT KEY INSTEAD
	if (SYDEKeyCode::get_key('W').getKeyCode() != '~')
	{
		return TestResult("initializeTest: Expected ~ But Got " + SYDEKeyCode::get_key('W').getKeyCode(), false);
	}
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('W'));
	//Now We Are Initialized
	if (SYDEKeyCode::get_key('W').getKeyCode() != 'W')
	{
		return TestResult("initializeTest: Expected W But Got " + SYDEKeyCode::get_key('W').getKeyCode(), false);
	}
	return TestResult("initializeTest Ran Successfully", true);
}
