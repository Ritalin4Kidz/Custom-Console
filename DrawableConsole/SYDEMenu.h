#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEButton.h"
#include <vector>
#include "CustomAsset.h"

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

class SYDEAdaptiveMenu_Item{
public:
	SYDEAdaptiveMenu_Item(SYDEButton Button) { m_display = false; m_Button = Button; }
	SYDEAdaptiveMenu_Item(SYDEButton Button, CustomAsset Display, Vector2 Loc) { m_display = true; m_Button = Button; m_DisplayItem = Display; m_DisplayLoc = Loc;}
	virtual ~SYDEAdaptiveMenu_Item() {}

	void setButtonHighlight(bool a) { m_Button._HIGHLIGHT(a); }
	void setButtonHighlightColour(ColourClass c) { m_Button.setHighLight(c); }
	void DoButtonFunc() { m_Button.DoFunc(); }

	bool getDisplay() { return m_display; }
	Vector2 getDiplayLoc() { return m_DisplayLoc; }

	SYDEButton& getButton() { return m_Button; }

	void draw_ui(ConsoleWindow& window) { window = m_Button.draw_ui(window); }
	void drawDisplay(ConsoleWindow& window) { window = m_DisplayItem.draw_asset(window, m_DisplayLoc); }

	string getLabel() { return m_Button.m_Label; }
	bool compareLabel(std::string text) { return m_Button.m_Label == text; }
	void setLabel(std::string labelTxt) { m_Button.m_Label = labelTxt; }

protected:
	bool m_display;
	SYDEButton m_Button = SYDEButton();
	CustomAsset m_DisplayItem = CustomAsset();
	Vector2 m_DisplayLoc = Vector2(0, 0);
};

class SYDEAdaptiveMenu {
public:
	SYDEAdaptiveMenu() { m_Items = vector<SYDEAdaptiveMenu_Item>(); selectionNumber = 0; }
	/// <summary>
	/// Create a menu with an array of buttons
	/// </summary>
	/// <param name="_ITEMS"></param>
	SYDEAdaptiveMenu(vector<SYDEAdaptiveMenu_Item> _ITEMS) { m_Items = _ITEMS; m_Items[0].setButtonHighlight(true); selectionNumber = 0;}
	virtual ~SYDEAdaptiveMenu() {}
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
	void AddOption(SYDEAdaptiveMenu_Item option) { m_Items.push_back(option); m_Items[0].setButtonHighlight(true);}

	/// <summary>
	/// Remove an option from the menu
	/// </summary>
	/// <param name="i"></param>
	void RemoveOptionAtIndex(int i);

	SYDEAdaptiveMenu_Item& operator[](int i) { return m_Items[i]; }

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
	SYDEAdaptiveMenu_Item& getSelected() { return m_Items[selectionNumber]; }
	/// <summary>
	/// Do the DoFunc call for the selected item
	/// </summary>
	void DoSelectedFunc() { m_Items[selectionNumber].DoButtonFunc(); }
	void setPos(Vector2 newPos) { m_Pos = newPos; }
private:
	vector<SYDEAdaptiveMenu_Item> m_Items;
	Vector2 m_Pos = Vector2(0, 0);

	bool m_Active = true;

	int selectionNumber = 0;
};