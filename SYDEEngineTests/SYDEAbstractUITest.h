#pragma once
#include "SYDEEngineBaseTest.h"

class SYDEAbstractUITest : public SYDEEngineBaseTest
{
public:
	SYDEAbstractUITest() { TestName = "SYDE Abstract UI Tests"; }

	TestResult runTests() override;

	virtual TestResult BasicClickTest();

	virtual TestResult BasicDrawTest();
};