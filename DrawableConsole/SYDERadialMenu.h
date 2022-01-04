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

enum SYDERadialMenuType
{
	Radial_Basic,
	Radial_
};

class SYDERadialOption : public SYDECheckbox
{
public:
	SYDERadialOption() {}
	SYDERadialOption(string a_text, ColourClass txtColour, ColourClass checkBoxClr);
	virtual ~SYDERadialOption() {}
	ConsoleWindow draw_ui_at_vector(ConsoleWindow window, Vector2 point);

	bool getOptionClicked() { return optionClicked; }

	void setIsChecked(bool check) { m_Checked = check; }

private:
	bool optionClicked = false;
	bool pointIsInCheckRange(Vector2 Point, Vector2 m_Pos);
};


class SYDERadialMenu : public SYDEUI {
public:
	SYDERadialMenu() { }
	SYDERadialMenu(Vector2 a_Pos);
	virtual ~SYDERadialMenu() {}
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;


	void setSpacing(int space) { m_Spacing = space; }

private:
	vector<SYDERadialOption> m_Options;
	int m_Spacing = 0;
};