#pragma once
#include <string>
#include <vector>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEButton.h"
#include "SYDEKeyCode.h"
#include "SYDECheckbox.h"

class SYDERadialOption : public SYDEUI
{
public:
	SYDERadialOption() {}
	SYDERadialOption(string a_text, ColourClass txtColour, ColourClass a_hoverColour, string a_Symbol, Vector2 displayPos);
	SYDERadialOption(string a_text, ColourClass txtColour, ColourClass a_hoverColour, string a_Symbol, Vector2 displayPos, void(*f)());
	ConsoleWindow draw_ui_at_vector(ConsoleWindow window, Vector2 point);

	bool getOptionClicked() { return optionClicked; }

	bool getIsHighlighted() { return isHighlighted; }

private:
	ColourClass TextColour = NULLCOLOUR;
	ColourClass HoverColour = NULLCOLOUR;
	bool canClick = true;
	bool optionClicked = false;
	string m_Symbol;
	bool pointIsInCheckRange(Vector2 Point, Vector2 m_Pos);

	bool isHighlighted = false;

	Vector2 textDisplayPos;
};


class SYDERadialMenu_Basic : public SYDEUI {
public:
	SYDERadialMenu_Basic() { }
	SYDERadialMenu_Basic(Vector2 a_Pos, SYDERadialOption northBtn, SYDERadialOption westBtn, SYDERadialOption southBtn, SYDERadialOption eastBtn);
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;
	/// <summary>
	/// get the index of the highlighted option (N,W,S,E) -1 if none
	/// </summary>
	/// <returns></returns>
	int getHighlightedIndex();

	void setSpacing(int space) { m_Spacing = space; }

private:
	SYDERadialOption m_North;
	SYDERadialOption m_South;
	SYDERadialOption m_West;
	SYDERadialOption m_East;

	int m_Spacing = 0;
};