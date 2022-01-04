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


class SYDERadioOption : public SYDECheckbox
{
public:
	SYDERadioOption() {}
	SYDERadioOption(string a_text, ColourClass txtColour, ColourClass checkBoxClr);
	virtual ~SYDERadioOption() {}
	ConsoleWindow draw_ui_at_vector(ConsoleWindow window, Vector2 point);

	bool getOptionClicked() { return optionClicked; }

	void setIsChecked(bool check) { m_Checked = check; }

private:
	bool optionClicked = false;
	bool pointIsInCheckRange(Vector2 Point, Vector2 m_Pos);
};


class SYDERadioButtonMenu : public SYDEUI {
public:
	SYDERadioButtonMenu() { }
	SYDERadioButtonMenu(Vector2 a_Pos, vector<SYDERadioOption> options);
	virtual ~SYDERadioButtonMenu() {}
	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	/// <summary>
	/// Returns the index of the menu checked, returns -1 if none checked
	/// </summary>
	/// <returns></returns>
	int getChecked();

	void setSpacing(int space) { m_Spacing = space; }

private:
	vector<SYDERadioOption> m_Options;
	int m_Spacing = 0;
};