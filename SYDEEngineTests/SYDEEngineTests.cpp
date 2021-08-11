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
#include "SYDEClickableButtonTest.h"

#pragma endregion


int main()
{
    int successfulTests = 0;
    int failedTests = 0;
    std::vector<SYDEEngineBaseTest*> listOfTests = std::vector<SYDEEngineBaseTest*>{
        new Vector2Test(),
        new TextItemTest(),
        new ConsoleWindowTest(),
        new SYDESliderTest(),
        new SYDEClickableButtonTest(),
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
