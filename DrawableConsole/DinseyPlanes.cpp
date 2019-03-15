#include "pch.h"
#include "DinseyPlanes.h"

DinseyPlanes::DinseyPlanes(AssetsClass astVars)
{
	//ADD IN PEARL HARBOUR CUTSCENE
	m_PearlHarbour.setAsset(vector<CustomAsset> {	CustomAsset(22, 11, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PlayerAnimations\\Left\\player_left_001.bmp", 11, 11)),
												CustomAsset(22, 11, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PlayerAnimations\\Left\\player_left_004.bmp", 11, 11)),
												CustomAsset(22, 11, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PlayerAnimations\\Left\\player_left_003.bmp", 11, 11)),
												CustomAsset(22, 11, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PlayerAnimations\\Left\\player_left_002.bmp", 11, 11))});

	m_PearlHarbour.setFrame(0);

	m_DinseyPlanes_MainMenu.setAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\DinseyPlanes\\MainMenu.bmp", 22, 20));
}

ConsoleWindow DinseyPlanes::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}

	if (_LEVEL == "_PearlHarbour")
	{
		return _PearlHarbour(window, windowWidth, windowHeight);
	}
	else {
		return _MainMenu(window, windowWidth, windowHeight);
	}
}

ConsoleWindow DinseyPlanes::_MainMenu(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_DinseyPlanes_MainMenu.draw_asset(window, Vector2(0, 0));
	// Template window.setTextAtPoint(Vector2(0, 0), "", window.determineColourAtPoint(Vector2(0,0),BLACK, true));
	// UI - Title
	window.setTextAtPoint(Vector2(2, 0), "D", window.determineColourAtPoint(Vector2(2, 0), BLACK, true));
	window.setTextAtPoint(Vector2(3, 0), "i", window.determineColourAtPoint(Vector2(3, 0), BLACK, true));
	window.setTextAtPoint(Vector2(4, 0), "n", window.determineColourAtPoint(Vector2(4, 0), BLACK, true));
	window.setTextAtPoint(Vector2(5, 0), "s", window.determineColourAtPoint(Vector2(5, 0), BLACK, true));
	window.setTextAtPoint(Vector2(6, 0), "e", window.determineColourAtPoint(Vector2(6, 0), BLACK, true));
	window.setTextAtPoint(Vector2(7, 0), "y", window.determineColourAtPoint(Vector2(7, 0), BLACK, true));
	window.setTextAtPoint(Vector2(9, 0), " P", window.determineColourAtPoint(Vector2(9, 0), BLACK, true));
	window.setTextAtPoint(Vector2(10, 0), "l", window.determineColourAtPoint(Vector2(10, 0), BLACK, true));
	window.setTextAtPoint(Vector2(11, 0), "a", window.determineColourAtPoint(Vector2(11, 0), BLACK, true));
	window.setTextAtPoint(Vector2(12, 0), "n", window.determineColourAtPoint(Vector2(12, 0), BLACK, true));
	window.setTextAtPoint(Vector2(13, 0), "e", window.determineColourAtPoint(Vector2(13, 0), BLACK, true));
	window.setTextAtPoint(Vector2(14, 0), "s", window.determineColourAtPoint(Vector2(14, 0), BLACK, true));
	return window;
}

ConsoleWindow DinseyPlanes::_PearlHarbour(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (_startUp)
	{
		window = m_PearlHarbour.draw_asset(window, Vector2(10, 5));
		Sleep(100);
		if (m_PearlHarbour.getFrame() >= m_PearlHarbour.getFrameSize() - 1)
		{
			_startUp = false;
		}
	}
	else
	{
		//Non Cutscene Part
	}
	return window;
}
