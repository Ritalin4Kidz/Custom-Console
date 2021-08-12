// SYDEEngineTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "SYDEEngineBaseTest.h"

#pragma region Test Includes

#include "Vector2Test.h"
#include "TextItemTest.h"
#include "ConsoleWindowTest.h"
#include "SYDESliderTest.h"
#include "SYDEVerticalSliderTest.h"
#include "SYDEClickableButtonTest.h"
#include "SYDEKeyCodeTest.h"
#include "SYDEOptionCyclerTest.h"

#pragma endregion

/*
These tests are all based off functionality and as such, no GUI is displayed during any of these tests
It will probs be best to make a separate GUI Test Project later down the line
*/
int main()
{
    int successfulTests = 0;
    int failedTests = 0;
    std::vector<SYDEEngineBaseTest*> listOfTests = std::vector<SYDEEngineBaseTest*>{
        new Vector2Test(),
        new TextItemTest(),
        new SYDEKeyCodeTest(),
        new ConsoleWindowTest(),
        new SYDESliderTest(),
        new SYDEVerticalSliderTest(),
        new SYDEClickableButtonTest(),
        new SYDEOptionCyclerTest(),
    };

    for (int i = 0; i < listOfTests.size(); i++)
    {
        try
        {
            TestResult result = listOfTests[i]->runTests();
            if (!result.isSuccessful)
            {
                std::cout << listOfTests[i]->getName() + " Had Errors:\n" + result.ResultMessage << endl;
                failedTests++;
            }
            else
            {
                std::cout << listOfTests[i]->getName() + " Ran Successfully" << endl;
                successfulTests++;
            }
        }
        catch (exception ex)
        {
            std::cout << listOfTests[i]->getName() + " Had Errors:\n" << endl;
            std::cout << ex.what() << endl;
            failedTests++;
        }
    }
    listOfTests.clear();
    std::cout << "Successful: " + to_string(successfulTests) + " | Failed: " + to_string(failedTests) << endl;
    system("pause");
}