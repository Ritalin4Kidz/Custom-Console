#include "pch.h"
#include "Concerto.h"
#include <string>

ColourClass Concerto::_bg = BLACK;

void Concerto::Initialize()
{
	m_Label._WrapText(true);
	//m_Button = SYDEButton("Test Text", Vector2(0, 0), Vector2(10, 1), BLACK, true);
	//m_Button.setHighLight(RED);
	for (int i = 0; i < _MENU.getSize(); i++)
	{
		_MENU[i].setHighLight(RED);
	}
	_t.SetFunc(TickFunc);
	_t.SetPos(Vector2(0, 2));
	_t.SetColour(BRIGHTGREEN);
	//_t.setState(Percentage);
	_t.setValueLength(3);

	_e.setColour(AQUA);
	_e.setCharacter("*");
	_e.RainbowOn(true);

	_b.setColour(YELLOW);
	_b.setCharacter("*");
	_b.RainbowOn(true);
	_b.setMaxParticles(35);
	_b.setFinishingColour(WHITE);
}
void Concerto::m_Button_Press()
{
	m_Label.setText("Potassium");
}
void TickFunc()
{
	int r = rand() % 255;
	Concerto::setBG(static_cast<ColourClass>(r));
}
ConsoleWindow Concerto::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//return test_A(window,windowWidth,windowHeight);
	return test_Particles(window,windowWidth,windowHeight);
}

ConsoleWindow Concerto::test_A(ConsoleWindow window, int windowWidth, int windowHeight)
{
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
	window = m_Button.draw_ui(window);
	window.setTextAtPoint(Vector2(0, 18), to_string(SYDEDefaults::getDeltaTime()), BLACK_WHITE_BG);
	window = _t.draw_ui(window);
	return window;
}

ConsoleWindow Concerto::test_Particles(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", _bg);
		}
	}
	if (SYDEKeyCode::get_key('Q')._CompareState(KEYDOWN))
	{
		_e.Start();
	}
	if (SYDEKeyCode::get_key('E')._CompareState(KEYDOWN))
	{
		_e.Stop();
	}
	if (SYDEKeyCode::get_key('B')._CompareState(KEYDOWN))
	{
		if (_b.isDead())
		{
			float _x = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40 - 0)));
			float _y = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (19 - 0)));
			_b.setPos(Vector2(_x, _y));
			_b.burst();
		}
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEYDOWN))
	{
		_e.increaseLifeSpan(0.1f);
		_e.increaseMaxParticles(1);
		_e.decreaseSpawnTime(0.05f);
	}
	if (SYDEKeyCode::get_key('S')._CompareState(KEYDOWN))
	{
		_e.decreaseLifeSpan(0.1f);
		_e.decreaseMaxParticles(1);
		_e.increaseSpawnTime(0.05f);
	}
	_e.draw(window);
	_b.draw(window);
	window = m_Label.draw_ui(window);
	return window;
}

