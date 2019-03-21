#include "pch.h"
#include "Concerto.h"

ConsoleWindow Concerto::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	window = m_TextBox.draw_textbox(window);
	if (SYDEKeyCode::Q.GetKeyDown(false))
	{
		m_TextBox.setActive(!m_TextBox.getActive());
	}
	if (SYDEKeyCode::A.GetKeyDown(false))
	{
		m_TextBox.addText("Hi");
	}
	//DELTATIME CHECKER
	window.setTextAtPoint(Vector2(0, 18), to_string(SYDEDefaults::getDeltaTime()), BLACK_WHITE_BG);
	return window;
}
