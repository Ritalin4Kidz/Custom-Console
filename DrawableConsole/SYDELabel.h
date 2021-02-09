#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"

enum SYDELabelAnchor {
	SLA_Normal,
	SLA_Center,
	SLA_Right
};

class SYDELabel : public SYDEUI, public SYDEUIInterface {
public:
	SYDELabel() { m_Label = ""; }
	SYDELabel(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG);
	virtual ~SYDELabel() {}
	/// <summary>
	/// Draw the label onto the window and return it
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;
	/// <summary>
	/// Add text to the label
	/// </summary>
	/// <param name="a_text"></param>
	void addText(string a_text) { m_Text += a_text; }
	/// <summary>
	/// replace the text in the label
	/// </summary>
	/// <param name="a_text"></param>
	void setText(string a_text) { m_Text = a_text; }
	/// <summary>
	/// remove a certain amount of text
	/// </summary>
	/// <param name="amt"> - Amount Of Text To Remove</param>
	void removeText(int amt) {m_Text = m_Text.substr(0, m_Text.size() - amt);}

	void setPos(Vector2 v) { m_Pos = v; }
	void setSize(Vector2 v) { m_Size = v; }
	void setColour(ColourClass c) { TextColour = c; }

	/// <summary>
	/// Set text wrapping enabled in draw function
	/// </summary>
	/// <param name="_WRAP"></param>
	void _WrapText(bool _WRAP) { _WRAPTEXT = _WRAP; }

	/// <summary>
	/// set the label anchor
	/// </summary>
	/// <param name="a"> - Text Anchor</param>
	void setLabelAnchor(SYDELabelAnchor a) { _Anchor = a; }

protected:
	bool _WRAPTEXT = false;
	bool _TRANSPARENT = false;
	Vector2 m_Size = Vector2(0, 0);
	Vector2 m_Pos = Vector2(0, 0);
	ColourClass TextColour = NULLCOLOUR;

	ConsoleWindow draw_normal(ConsoleWindow window);
	ConsoleWindow draw_center_anchored(ConsoleWindow window);
	ConsoleWindow draw_right_anchored(ConsoleWindow window);

	SYDELabelAnchor _Anchor = SLA_Normal;

};
