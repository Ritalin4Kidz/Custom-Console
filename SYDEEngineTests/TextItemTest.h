#pragma once
#include "SYDEEngineBaseTest.h"


class TextItemTest : public SYDEEngineBaseTest
{
public:
	TextItemTest() { TestName = "Text Item Tests"; }

	TestResult runTests() override;

	/// <summary>
	/// Test that the TextItem initializes properly
	/// </summary>
	/// <returns></returns>
	TestResult initializeTest();

private:
};
