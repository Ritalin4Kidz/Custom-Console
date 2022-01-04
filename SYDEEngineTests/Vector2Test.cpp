#include "Vector2Test.h"

TestResult Vector2Test::runTests()
{
	TestResult mainResult;
	TestResult result;
	result = initializeTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	result = differenceTest();
	if (!result.isSuccessful)
	{
		mainResult.isSuccessful = false;
		mainResult.ResultMessage += result.ResultMessage;
	}
	return mainResult;
}

TestResult Vector2Test::initializeTest()
{
	Vector2 v1;
	if (v1.getX() != 0 || v1.getY() != 0)
	{
		return TestResult("Vector v1 did not initialize properly \n", false);
	}
	Vector2 v2 = Vector2(5);
	if (v2.getX() != 5 || v2.getY() != 5)
	{
		return TestResult("Vector v2 did not initialize properly \n", false);
	}
	Vector2 v3 = Vector2(10,8);
	if (v3.getX() != 10 || v3.getY() != 8)
	{
		return TestResult("Vector v3 did not initialize properly \n", false);
	}
	return TestResult("Vector Initialize Test Was Successful \n", true);
}

TestResult Vector2Test::differenceTest()
{
	Vector2 a = Vector2(5, 0);
	Vector2 b = Vector2(0, 0);
	if (a.distance(b) != 5)
	{
		return TestResult("Expected 5, but instead got " + to_string(a.distance(b)) + "\n", false);
	}
	Vector2 c = Vector2(13, 4);
	Vector2 d = Vector2(101, -6);
	//JUST MAKING THIS THE INT FOR SIMPLICITY SINCE FLOATS CAN GET COMPLICATED
	if ((int)c.distance(d) != 88)
	{
		return TestResult("Expected 88, but instead got " + to_string((int)c.distance(d)) + "\n", false);
	}
	return TestResult("Vector Distance Test Was Successful \n", true);
}
