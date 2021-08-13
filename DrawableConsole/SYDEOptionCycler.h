#pragma once
/*
< [~~~] >

Cycle through a list of options

UI ELEMENT

*/
#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include <vector>
#include "SYDEKeyCode.h"

struct SYDEOptionCyclerItem
{
	SYDEOptionCyclerItem() { }
	SYDEOptionCyclerItem(int v, string s) { m_Text = s; m_Value = v; }
	SYDEOptionCyclerItem(int v, string s, string t) { m_Text = s; m_Value = v; m_Tag = t; }
	int m_Value;
	string m_Text;
	string m_Tag = "";
};

class SYDEOptionCycler : public SYDEUI {
public:
	SYDEOptionCycler() { m_Label = ""; }
	SYDEOptionCycler(Vector2 a_Pos, int a_Size, ColourClass txtColour, bool _TRANSPARENTBG, vector<SYDEOptionCyclerItem> items)
	{
		m_Pos = a_Pos;
		_TRANSPARENT = _TRANSPARENTBG;
		m_Colour = txtColour;
		m_Items = items;
		size = a_Size;
	}
	virtual ~SYDEOptionCycler() {}
	/// <summary>
	/// Draw the label onto the window and return it
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	int getSelectedValue() { return m_Items[m_SelectedItem].m_Value; }
	string getSelectedText() { return m_Items[m_SelectedItem].m_Text; }
	string getSelectedTag() { return m_Items[m_SelectedItem].m_Tag; }


private:
	ColourClass m_Colour;
	int size;
	bool _TRANSPARENT;
	vector<SYDEOptionCyclerItem> m_Items;
	int m_SelectedItem;
	bool canClick = true;
	bool pointIsInButtonRangePrev(Vector2 Point);
	bool pointIsInButtonRangeNext(Vector2 Point);
};