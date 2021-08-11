#pragma once
#include "SYDEEngineAssets.h"
#include "SYDEEngineDemos.h"
#include "SYDEEngineMath.h"
#include "SYDEEngineUI.h"
#include "SYDESounds.h"
#include "SYDESpecial.h"
#include "SYDEstdafx.h"
#include <string>

struct TestResult
{
	TestResult() {}
	TestResult(string m, bool s) { ResultMessage = m; isSuccessful = s; }
	std::string ResultMessage ="";
	bool isSuccessful = true;
};

class SYDEEngineBaseTest
{
public:
	SYDEEngineBaseTest() {}


	virtual TestResult runTests() { return TestResult("", true); }

	std::string getName() { return TestName; }

protected:

	std::string TestName = "";
};