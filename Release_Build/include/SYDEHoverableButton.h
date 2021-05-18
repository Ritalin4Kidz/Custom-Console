#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEButton.h"
#include "SYDEKeyCode.h"

/// <summary>
/// Button that highlights when you hover over it
/// </summary>
class SYDEHoverableButton : public SYDEButton {
public:
	SYDEHoverableButton() { m_Label = ""; }
	SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG);
	SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG);
	SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, bool _Clickable);
	SYDEHoverableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, void(*f)());

	virtual ~SYDEHoverableButton() {}
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	void SetClickable(bool clickable) { m_Clickable = clickable; }

private:
	bool pointIsInButtonRange(Vector2 Point);
	bool m_Clickable = true;
};