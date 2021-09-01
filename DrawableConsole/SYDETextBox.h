#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEKeyCode.h"
using namespace std;

class SYDETextBox : public SYDEUI {
public:
	SYDETextBox() { m_Label = ""; }
	SYDETextBox(string a_Label) { m_Label = a_Label; }
	SYDETextBox(Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour);
	virtual ~SYDETextBox() {}

	/// <summary>
	/// Draw the textbox on the screen
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	void addText(string a_text) { if (m_Active) { m_Text += a_text; } }
	void removeText(int amt) { if (m_Active) { m_Text = m_Text.substr(0, m_Text.size() - amt); } }
	/// <summary>
	/// Set if the textbox is allowed to receive input
	/// </summary>
	/// <param name="active"></param>
	void setActive(bool active) { m_Active = active; }

	bool getActive() { return m_Active; }
private:
	bool m_Active = false;
	//string m_Text = "";

	Vector2 m_Size = Vector2(0, 0);
	ColourClass TextColour = NULLCOLOUR;

};

class SYDEClickableTextBox : public SYDEUI {
public:
	SYDEClickableTextBox() { m_Label = ""; }
	SYDEClickableTextBox(string a_Label) { m_Label = a_Label; }
	SYDEClickableTextBox(Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour);
	virtual ~SYDEClickableTextBox() {}

	/// <summary>
	/// Draw the textbox on the screen
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	void setText(string txt) { m_Text = txt; }

	void addText(string a_text) { if (m_Active) { m_Text += a_text; } }
	void removeText(int amt) { if (m_Active) { m_Text = m_Text.substr(0, m_Text.size() - amt); } }
	/// <summary>
	/// Set if the textbox is allowed to receive input
	/// </summary>
	/// <param name="active"></param>
	void setActive(bool active) { m_Active = active; }

	bool getActive() { return m_Active; }
private:
	bool pointIsInButtonRange(Vector2 Point);
	bool m_Active = false;
	//string m_Text = "";

	Vector2 m_Size = Vector2(0, 0);
	ColourClass TextColour = NULLCOLOUR;
	bool canClick = true;
	float timeSpent = 0.0f;
	const float backspaceTime = 0.25f;
};