#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEButton.h"
#include "SYDEKeyCode.h"
class SYDESlider : public SYDEUI {
public:
	SYDESlider() { }
	SYDESlider(Vector2 a_Pos, int size, ColourClass BackClr, ColourClass SliderClr);
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;
	bool getIsInDraggedState() { return isInDraggedState; }

	void setIsHoldClickRequired(bool state) { isHoldClickRequired = state; }
	bool getIsHoldClickRequired() { return isHoldClickRequired; }

	int getValue() { return sliderValue; }

	void setSize(int s) { m_Size = s; }

protected:
	bool isInDraggedState = false;
	void setIsInDraggedState(bool state) { isInDraggedState = state; }
	bool isHoldClickRequired = true;
	bool canClick = true;

	int sliderValue = 0;

	int m_Size = 0;
	ColourClass BackColour = NULLCOLOUR;
	ColourClass SliderColour = NULLCOLOUR;
	bool pointIsInButtonRange(Vector2 Point);
};

class SYDEVerticalSlider : public SYDESlider {
public:
	SYDEVerticalSlider() { }
	SYDEVerticalSlider(Vector2 a_Pos, int size, ColourClass BackClr, ColourClass SliderClr);
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;
	bool pointIsInButtonRange(Vector2 Point);
};