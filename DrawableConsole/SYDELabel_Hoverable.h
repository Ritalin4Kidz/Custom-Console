#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDELabel.h"
#include "SYDEKeyCode.h"

class SYDELabel_Hoverable : public SYDELabel
{
public:
	SYDELabel_Hoverable() { m_Label = ""; }
	SYDELabel_Hoverable(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG);
	SYDELabel_Hoverable(string a_text, Vector2 a_Pos, Vector2 a_Size, ColourClass txtColour, bool _TRANSPARENTBG, void(*f)());
	virtual ~SYDELabel_Hoverable() { if (m_Function != NULL) delete& m_Function; }
	/// <summary>
	/// Draw the label onto the window and return it
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	/// <summary>
	/// Execute the main button function
	/// </summary>
	void DoFunc() { m_Function(); }
	/// <summary>
	/// Set the main function for the button
	/// </summary>
	/// <param name="f"></param>
	void SetFunc(void(*f)()) { m_Function = f; }
protected:
	bool pointIsInButtonRange(Vector2 Point);
	bool hovering = false;
	void(*m_Function)();
};