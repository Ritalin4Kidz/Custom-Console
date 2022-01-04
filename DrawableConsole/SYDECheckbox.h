#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEButton.h"
#include "SYDEKeyCode.h"
class SYDECheckbox : public SYDEUI {
public:
	SYDECheckbox() { }
	SYDECheckbox(string a_text, Vector2 a_Pos, ColourClass txtColour, ColourClass checkBoxClr, bool checked);
	virtual ~SYDECheckbox() {}
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	bool isChecked() { return m_Checked; }

protected:
	bool m_Checked = false;
	bool canClick = true;
	ColourClass TextColour = NULLCOLOUR;
	ColourClass CheckBoxColour = NULLCOLOUR;
	bool pointIsInButtonRange(Vector2 Point);
};