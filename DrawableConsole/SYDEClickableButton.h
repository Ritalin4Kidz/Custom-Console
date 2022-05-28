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
	SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, void(*f)(), string a_Tag);
	SYDEClickableButton(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, ColourClass a_hiLightColour, bool _TRANSPARENTBG, void(*f)(), string a_Tag, string a_Label);
	virtual ~SYDEClickableButton() {}
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;
	ConsoleWindow draw_ui(ConsoleWindow window, Vector2 point);
	void setTag(string newTag) { tag = newTag; }
	string getTag() { return tag; }

	void setColour(ColourClass m_Col) { TextColour = m_Col; }
	static string getLastButtonTag();
private:
	static string lastTag;
	string tag = "";
	bool pointIsInButtonRange(Vector2 Point);
	bool pointIsInButtonRange(Vector2 Point, Vector2 mousePos);

	bool canClick = true;

	ColourClass disabledColour = BLACK_LIGHTGREY_BG;
};