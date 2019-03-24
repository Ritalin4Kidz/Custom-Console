#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
using namespace std;
class SYDETextBox {
public:
	SYDETextBox() {}
	SYDETextBox(Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour);
	virtual ~SYDETextBox() {}


	ConsoleWindow draw_textbox(ConsoleWindow window);

	void addText(string a_text) { if (m_Active) { m_Text += a_text; } }
	void removeText(int amt) { if (m_Active) { m_Text = m_Text.substr(0, m_Text.size() - amt); } }
	void setActive(bool active) { m_Active = active; }

	bool getActive() { return m_Active; }
private:
	bool m_Active = false;
	string m_Text = "";

	Vector2 m_Size = Vector2(0, 0);
	Vector2 m_Pos = Vector2(0,0);
	ColourClass TextColour = NULLCOLOUR;

};