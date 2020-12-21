#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEButton.h"
#include <vector>

using namespace std;

class SYDEMenu {
public:
	SYDEMenu() { m_Items = vector<SYDEButton>(); }
	/// <summary>
	/// Create a menu with an array of buttons
	/// </summary>
	/// <param name="_ITEMS"></param>
	SYDEMenu(vector<SYDEButton> _ITEMS) { m_Items = _ITEMS; m_Items[0]._HIGHLIGHT(true); }
	virtual ~SYDEMenu() {}
	/// <summary>
	/// Draw the menu onto the screen
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_menu(ConsoleWindow window);
	void setActive(bool _ACTV) { m_Active = _ACTV; }
	bool getActive() { return m_Active; }

	/// <summary>
	/// Add a new item into the menu
	/// </summary>
	/// <param name="option"></param>
	void AddOption(SYDEButton option) { m_Items.push_back(option); m_Items[0]._HIGHLIGHT(true);}

	/// <summary>
	/// Remove an option from the menu
	/// </summary>
	/// <param name="i"></param>
	void RemoveOptionAtIndex(int i);

	SYDEButton& operator[](int i) { return m_Items[i]; }

	/// <summary>
	/// Select the previous option in the menu
	/// </summary>
	void prevSelect();
	/// <summary>
	/// Select the next option in the menu
	/// </summary>
	void nextSelect();
	void hiLight();

	int getSize() { return m_Items.size(); }
	int getSelectedNumber() { return selectionNumber; }
	/// <summary>
	/// return the currently selected item in the menu
	/// </summary>
	/// <returns></returns>
	SYDEButton& getSelected() { return m_Items[selectionNumber]; }
	/// <summary>
	/// Do the DoFunc call for the selected item
	/// </summary>
	void DoSelectedFunc() { m_Items[selectionNumber].DoFunc(); }
	void setPos(Vector2 newPos) { m_Pos = newPos; }
private:
	vector<SYDEButton> m_Items;
	Vector2 m_Pos = Vector2(0, 0);

	bool m_Active = false;

	int selectionNumber = 0;
};