#pragma once
#include "SYDEEngineBaseTest.h"


class ConsoleWindowTest : public SYDEEngineBaseTest
{
public:
	ConsoleWindowTest() { TestName = "Console Window Tests"; }

	TestResult runTests() override;

	TestResult ConsoleWindowPointColourTest();

private:
};
