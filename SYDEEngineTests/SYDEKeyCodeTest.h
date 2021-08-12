#pragma once
#include "SYDEEngineBaseTest.h"


class SYDEKeyCodeTest : public SYDEEngineBaseTest
{
public:
	SYDEKeyCodeTest() { TestName = "SYDE KeyCode Tests"; }

	TestResult runTests() override;

	/// <summary>
	/// Test that the TextItem initializes properly
	/// </summary>
	/// <returns></returns>
	TestResult initializeTest();

private:
};