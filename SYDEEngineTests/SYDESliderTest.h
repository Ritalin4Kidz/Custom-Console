#pragma once
#pragma once
#include "SYDEEngineBaseTest.h"

/*
* Here's the logic to getting a GUI test to run without actually having GUI on the screen
* ```
* 	SYDESurvival m_SRL;
	while (true)
	{
		window = SYDEGamePlay::play(&m_SRL, start, hOut, window, windowWidth, windowHeight, deltaTime);
		window.writeConsoleOptimized();
	}
* ```
* This is the code that we have to actually run a game, we do not need to write the console out
* 
* Just call up SYDEGamePlay::play everytime you want to view a specific frame, EZPZ
* 
* 
* static ConsoleWindow play_test_func(SYDEWindowGame* SYDE_GAME, ConsoleWindow window, int windowWidth, int windowHeight, SYDETIME& deltaTime);
* 
* This function removes all the console editing as well
* 
* For Inputs, we can force them by calling the SYDEKeyCode directly (e.g.)
* 
* 			SYDEKeyCode::SetLastClickPosition(LastPointClicked);
*			SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyDown();
*			SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE.ForceKeyUp();
* However we might need to actually add them to our KeyCodes in the test initialization
* 
* 
* In this example, we should be able to declare a slider with size of 10, and pos of 0,10
* 
* If we then force an input of 5,11 mouse click, we should be able to determine that the slider has moved 5 positions to the right
* 
* Last Thing Of Note, we only adjust the console window in initialize by touching the offset
* window.setOffset(config.getOffset());
* 
* You can probs just edit that and we'll all be golden
* 
*/
class SYDESliderTest : public SYDEEngineBaseTest
{
public:
	SYDESliderTest() { TestName = "SYDE UI Slider Tests"; }

	TestResult runTests() override;


private:
};