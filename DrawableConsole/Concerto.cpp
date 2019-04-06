#include "pch.h"
#include "Concerto.h"
#include <string>


void Concerto::Initialize()
{
	m_Label._WrapText(true);
	//m_Button = SYDEButton("Test Text", Vector2(0, 0), Vector2(10, 1), BLACK, true);
	//m_Button.setHighLight(RED);
	for (int i = 0; i < _MENU.getSize(); i++)
	{
		_MENU[i].setHighLight(RED);
	}
}
void Concerto::m_Button_Press()
{
	m_Label.setText("Potassium");
}
ConsoleWindow Concerto::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	if (SYDEKeyCode::get(VK_RETURN)._CompareState(KEYDOWN))
	{
		m_TextBox.setActive(!m_TextBox.getActive());
	}
	if (SYDEKeyCode::get(VK_BACK)._CompareState(KEYDOWN))
	{
		m_TextBox.removeText(1);
	}
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_MENU.setActive(!_MENU.getActive());
	}
	if (SYDEKeyCode::get('M')._CompareState(KEYDOWN))
	{
		_MENU.nextSelect();
	}
	if (SYDEKeyCode::get('P')._CompareState(KEYDOWN) && _MENU.getActive())
	{
		_MENU.getSelected().ButtonPress();
	}
	if (_MENU[0]._CompareButtonState(BUTTONCLICKED))
	{
		m_Button_Press();
	}
	//if (m_TextBox._CompareTextState(TEXTCHANGED))
	//{
	//	m_TextBox.setActive(false);
	//}
	//if (SYDEKeyCode::A.GetKeyDown(false))
	//{
	//	m_TextBox.addText("Hi");
	//}
	//DELTATIME CHECKER
	std::string test = SYDEKeyCode::KeysDown();
	m_TextBox.addText(test);

	if (_MENU.getActive()) { window = _MENU.draw_menu(window); }
	window = m_TextBox.draw_ui(window);
	m_Label.setText("DeltaTime:" + to_string(SYDEDefaults::getDeltaTime()));
	window = m_Label.draw_ui(window);
	//window = m_Button.draw_ui(window);
	//window.setTextAtPoint(Vector2(0, 18), to_string(SYDEDefaults::getDeltaTime()), BLACK_WHITE_BG);
	return window;
	//PICK ME UP GITHUBBY
}

