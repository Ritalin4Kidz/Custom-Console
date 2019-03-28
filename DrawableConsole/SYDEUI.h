#pragma once
#include <string>
#include <vector>

using namespace std;
enum TextState {
	TEXTNONE,
	TEXTCHANGED,
	TEXTENTER
};

class SYDEUI
{
public:
	bool _CompareTextState(TextState m_State) { return m_State == m_TxtState; }
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
protected:
	TextState m_TxtState = TEXTNONE;
	string m_LastText = "";
};