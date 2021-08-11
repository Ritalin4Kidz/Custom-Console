#pragma once
#include "SYDEEngineBaseTest.h"


class Vector2Test : public SYDEEngineBaseTest
{
public:
	Vector2Test() { TestName = "Vector 2 Tests"; }

	TestResult runTests() override;

	/// <summary>
	/// Test that the vector initializes properly
	/// </summary>
	/// <returns></returns>
	TestResult initializeTest();
	/// <summary>
	/// Test that we are properly counting distance between two points
	/// </summary>
	/// <returns></returns>
	TestResult differenceTest();

private:
};