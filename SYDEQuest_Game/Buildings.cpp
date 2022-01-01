#include "Buildings.h"
bool Test_Building::hasLoaded = false;
CustomAsset Test_Building::m_Map = CustomAsset();
CustomAsset Test_Building::m_bg = CustomAsset();
Test_Building::Test_Building()
{
	if (!hasLoaded)
	{
		m_bg = CustomAsset(60, 30, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg2.bmp", 30, 30));
		m_Map = CustomAsset(60, 30, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\TestHouse.bmp", 30, 30));
		hasLoaded = true;
	}
}

Test_Building::~Test_Building()
{
}

ConsoleWindow Test_Building::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = m_Map.draw_asset(window, Vector2(SYDEMapGame::camera_Pos.getX() - 20, SYDEMapGame::camera_Pos.getY() - 10), windowWidth, windowHeight);
	window = Building_Defaults::Base_Input(window, m_Map);
	return window;
}

ConsoleWindow Building_Defaults::Base_Input(ConsoleWindow window, CustomAsset m_Map)
{
	Vector2 MovementBuffer(0);
	window.setTextAtPoint(Vector2(20, 10), "><", window.determineColourAtPoint(Vector2(20, 10), BLACK, true));
	char tempChar = m_Map.getCharAtPoint(SYDEMapGame::camera_Pos);
	//if (SYDEKeyCode::get_key('I')._CompareState(KEYDOWN))
	//{
	//	GameScene::SetScene(MoveSelection);
	//	return window;
	//}
	if (SYDEKeyCode::get_key('S')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20 + MovementBuffer.getX(), 11 + MovementBuffer.getY())));
		if (temp.compare("0") != 0)
		{
			SYDEMapGame::camera_Pos.addY(1);
			MovementBuffer.addY(1);
		}
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20 + MovementBuffer.getX(), 9 + MovementBuffer.getY())));
		if (temp.compare("0") != 0)
		{
			SYDEMapGame::camera_Pos.addY(-1);
			MovementBuffer.addY(-1);
		}
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(22 + MovementBuffer.getX(), 10 + MovementBuffer.getY())));
		if (temp.compare("0") != 0)
		{
			SYDEMapGame::camera_Pos.addX(2);
			MovementBuffer.addX(2);
		}
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(18 + MovementBuffer.getX(), 10 + MovementBuffer.getY())));
		if (temp.compare("0") != 0)
		{
			SYDEMapGame::camera_Pos.addX(-2);
			MovementBuffer.addX(-2);
		}
	}
	return window;
}
