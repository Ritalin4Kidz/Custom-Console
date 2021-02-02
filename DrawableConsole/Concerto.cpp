#include "pch.h"
#include "Concerto.h"
#include <string>

ColourClass Concerto::_bg = BLACK_LIGHTGREY_BG;

void Concerto::Initialize()
{
	m_Label._WrapText(true);
	//m_Button = SYDEButton("Test Text", Vector2(0, 0), Vector2(10, 1), BLACK, true);
	//m_Button.setHighLight(RED);
	for (int i = 0; i < _MENU.getSize(); i++)
	{
		_MENU[i].setHighLight(RED);
	}

	//for (int i = 0; i < _ADAPTIVEMENU.getSize(); i++)
	//{
	//	_ADAPTIVEMENU[i].setButtonHighlightColour(WHITE_BLUE_BG);
	//}
	_ADAPTIVEMENU.setPos(Vector2(0, 1));
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


	m_ClickableButton = SYDEClickableButton("CLICK ME", Vector2(20, 15), Vector2(10, 1), BLACK_BRIGHTWHITE_BG, false);
	m_ClickableButton.setHighLight(RED);
	m_ClickableButton.SetFunc(TickFunc);
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
	return test_Menus(window, windowWidth, windowHeight);
	//return test_Asset(window, windowWidth, windowHeight);
	//return test_A(window,windowWidth,windowHeight);
	//return test_Particles(window,windowWidth,windowHeight);
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

ConsoleWindow Concerto::test_Menus(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", _bg);
		}
	}

	if (SYDEKeyCode::get_key('M')._CompareState(KEYDOWN))
	{
		_ADAPTIVEMENU.setActive(!_ADAPTIVEMENU.getActive());
	}
	else if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_ADAPTIVEMENU.nextSelect();
	}
	if (SYDEKeyCode::LEFT_CLICK_MOUSE._CompareState(KEYDOWN))
	{
		m_LabelText = " --- State: Key Down";
	}
	else if (SYDEKeyCode::LEFT_CLICK_MOUSE._CompareState(KEY))
	{
		m_LabelText = " --- State: Key Held";
	}
	else if (SYDEKeyCode::LEFT_CLICK_MOUSE._CompareState(KEYUP))
	{
		m_LabelText = " --- State: Key Released";
	}
	window = _ADAPTIVEMENU.draw_menu(window);
	//Vector2 testMousePosition = SYDEKeyCode::getMousePosition();
	m_Label.setText(to_string((int)SYDEGamePlay::GetPointClicked().getX()) + "," + to_string((int)SYDEGamePlay::GetPointClicked().getY()) + m_LabelText);
	//m_Label.setText(to_string((int)testMousePosition.getX()) + "," + to_string((int)testMousePosition.getY()) + m_LabelText);
	window = m_Label.draw_ui(window);
	window = m_ClickableButton.draw_ui(window);
	return window;
}

ConsoleWindow Concerto::test_Asset(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_Map.draw_asset(window, Vector2(camera_Pos.getX() - 20, camera_Pos.getY() - 10), windowWidth, windowHeight);
	window = m_Structure.draw_asset(window, Vector2(20, 10));
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		m_Map.AddAssetOnto(m_Structure, Vector2(camera_Pos.getX(), camera_Pos.getY()));
	}
	window.setTextAtPoint(Vector2(0, 1), std::to_string((int)camera_Pos.getX()) + "," + std::to_string((int)camera_Pos.getY()), RED_WHITE_BG);

	if (SYDEKeyCode::get_key('S')._CompareState(KEY) && camera_Pos.getY() < 1000)
	{
		camera_Pos.addY(1);
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEY) && camera_Pos.getY() > 0)
	{
		camera_Pos.addY(-1);
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY) && camera_Pos.getX() < 1000)
	{
		camera_Pos.addX(2);
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY) && camera_Pos.getX() > 0)
	{
		camera_Pos.addX(-2);
	}

	return window;
}

