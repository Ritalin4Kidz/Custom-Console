#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEButton.h"
#include "SYDEKeyCode.h"
class SYDEClickableButton : public SYDEButton {
public:
	SYDEClickableButton() { m_Label = ""; }
	SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG);
	SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG);
	SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, void(*f)());
	virtual ~SYDEClickableButton() {}
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;
	void setTag(string newTag) { tag = newTag; }
	string getTag() { return tag; }

	static string getLastButtonTag();
private:
	static string lastTag;
	string tag = "";
	bool pointIsInButtonRange(Vector2 Point);
};