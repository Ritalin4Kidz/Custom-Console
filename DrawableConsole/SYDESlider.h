#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEButton.h"
#include "SYDEKeyCode.h"
class SYDESlider : public SYDEUI, public SYDEUIInterface {
public:
	SYDESlider() { }
	SYDESlider(Vector2 a_Pos, int size, ColourClass BackClr, ColourClass SliderClr);
	virtual ~SYDESlider() {}
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

protected:
	bool isInDraggedState = false;
	void setIsInDraggedState(bool state) { isInDraggedState = state; }
	bool isHoldClickRequired = true;
private:
	bool canClick = true;
	Vector2 m_Pos = Vector2(0, 0);

	int sliderValue = 0;

	int m_Size = 0;
	ColourClass BackColour = NULLCOLOUR;
	ColourClass SliderColour = NULLCOLOUR;
	bool pointIsInButtonRange(Vector2 Point);
};