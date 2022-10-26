#pragma once
#include <string>
#include <vector>

#include "Vector2.h"

using namespace std;
enum TextState {
	TEXTNONE,
	TEXTCHANGED,
	TEXTENTER
};

enum ButtonState {
	BUTTONNONE,
	BUTTONCLICKED
};


class SYDEUI
{
public:
	bool _CompareTextState(TextState m_State) { return m_State == m_TxtState; }
	bool _CompareButtonState(ButtonState m_State) { return m_State == m_BtnState; }
	virtual ~SYDEUI() { if (m_Function != NULL) delete& m_Function; }
	void _CheckState() {
		if (m_Text == m_LastText)
		{
			m_TxtState = TEXTNONE;
		}
		else {
			m_TxtState = TEXTCHANGED;
		}
		m_LastText = m_Text;
	}
	void _Enter()
	{
		m_TxtState = TEXTENTER;
	}
	string m_Text = "";
	string m_Label = "";

	string returnLabel() { return m_Label; }

	/// <summary>
	/// Execute the main button function
	/// </summary>
	void DoFunc() {
		if (m_FunctionSet)
		{
			m_Function();
		}
	}
	void setEnabled(bool isEnabled) { enabled = isEnabled; }
	virtual ConsoleWindow draw_ui(ConsoleWindow window) { return window; }

	/// <summary>
	/// Set the main function for the button
	/// </summary>
	/// <param name="f"></param>
	void SetFunc(void(*f)()) { m_FunctionSet = true;  m_Function = f; }

	Vector2 getPos() { return m_Pos; }
	void setPos(Vector2 p) { m_Pos = p; }

protected:
	TextState m_TxtState = TEXTNONE;
	ButtonState m_BtnState = BUTTONNONE;
	string m_LastText = "";
	bool enabled = true;
	Vector2 m_Pos = Vector2(0, 0);
private:
	bool m_FunctionSet = false;
	void(*m_Function)();
};