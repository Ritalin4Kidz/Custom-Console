#include "pch.h"
#include "DinseyPlanes.h"

DinseyPlanes::DinseyPlanes(AssetsClass astVars)
{
	//ADD IN PEARL HARBOUR CUTSCENE
	m_PearlHarbour.setAsset(vector<CustomAsset> {	CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_001.bmp", 22, 20)),
													CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_002.bmp", 22, 20)),
													CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_003.bmp", 22, 20)),
													CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_004.bmp", 22, 20)),
													CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_005.bmp", 22, 20))});

	m_PearlHarbour.setFrame(0);

	m_Tutorial.setAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_005.bmp", 22, 20));

	m_PearlHarbourFlyDown.setAsset(vector<CustomAsset> {	CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_006.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_007.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_008.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_009.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_010.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_011.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_012.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_013.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_014.bmp", 22, 20)),
															CustomAsset(44, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Animations\\PearlHarbour\\Scene_015.bmp", 22, 20))
	});

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
	if (_LEVEL == "_Level_Select")
	{
		return _LevelSelect(window, windowWidth, windowHeight);
	}
	else {
		return _MainMenu(window, windowWidth, windowHeight);
	}
}

ConsoleWindow DinseyPlanes::_MainMenu(ConsoleWindow window, int windowWidth, int windowHeight)
{
	_MainMenuInputVoids();
	window = m_DinseyPlanes_MainMenu.draw_asset(window, Vector2(0, 0));
	// Template window.setTextAtPoint(Vector2(0, 0), "", window.determineColourAtPoint(Vector2(0,0),BLACK, true));
	// UI - Title
	window.setTextAtPoint(Vector2(2, 1), "Dinsey Planes", window.determineColourAtPoint(Vector2(2, 1), BLACK, true));

	window.setTextAtPoint(Vector2(0, 12), "A. Level Select", window.determineColourAtPoint(Vector2(2, 1), BLACK, true));
	window.setTextAtPoint(Vector2(0, 13), "Z. Quit Game", window.determineColourAtPoint(Vector2(2, 1), BLACK, true));
	return window;
}

void DinseyPlanes::_MainMenuInputVoids()
{
	if (GetKey('A'))
	{
		_LEVEL = "_Level_Select";
	}
	if (GetKey('Z'))
	{
		exit(NULL);
	}
}

ConsoleWindow DinseyPlanes::_LevelSelect(ConsoleWindow window, int windowWidth, int windowHeight)
{
	_LevelSelectInputVoids();
	window = m_DinseyPlanes_MainMenu.draw_asset(window, Vector2(0, 0));
	// Template window.setTextAtPoint(Vector2(0, 0), "", window.determineColourAtPoint(Vector2(0,0),BLACK, true));
	// UI - Level Select
	window.setTextAtPoint(Vector2(2, 1), "Dinsey Planes", window.determineColourAtPoint(Vector2(2, 1), BLACK, true));

	window.setTextAtPoint(Vector2(0, 11), "A. 1st Sep 1939", window.determineColourAtPoint(Vector2(2, 1), BLACK, true));
	window.setTextAtPoint(Vector2(0, 12), "B. 7th Dec 1941", window.determineColourAtPoint(Vector2(2, 1), BLACK, true));
	window.setTextAtPoint(Vector2(0, 13), "Z. Back", window.determineColourAtPoint(Vector2(2, 1), BLACK, true));
	return window;
}

void DinseyPlanes::_LevelSelectInputVoids()
{
	if (GetKey('A'))
	{
		//_LEVEL = "_Poland"; //NOT YET IMPLEMENTED
	}
	if (GetKey('B'))
	{
		_LEVEL = "_PearlHarbour";
		PearlHarbourScene = 0;
	}
	if (GetKey('Z'))
	{
		_LEVEL = "_MainMenu";
	}
}

ConsoleWindow DinseyPlanes::_PearlHarbour(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (PearlHarbourScene == 0)
	{
		window = m_PearlHarbour.draw_asset(window, Vector2(0, 0));
		Sleep(100);
		if (m_PearlHarbour.getFrame() >= m_PearlHarbour.getFrameSize() - 1)
		{
			m_PearlHarbour.setFrame(0);
			PearlHarbourScene++;
		}
	}
	else if (PearlHarbourScene == 1)
	{
		if (GetKey('S'))
		{
			PearlHarbourScene++;
		}
		window = m_Tutorial.draw_asset(window, Vector2(0, 0));
		for (int i = 0; i < windowWidth; i++)
		{
			window.setTextAtPoint(Vector2(i, 19), " ", BLACK);
		}
		window.setTextAtPoint(Vector2(0, 19), "Tutorial: Press 'S' To Move Down", WHITE);
		Sleep(100);
	}
	else if (PearlHarbourScene == 2)
	{
		window = m_PearlHarbourFlyDown.draw_asset(window, Vector2(0, 0));
		Sleep(100);
		if (m_PearlHarbourFlyDown.getFrame() >= m_PearlHarbourFlyDown.getFrameSize() - 1)
		{
			m_PearlHarbourFlyDown.setFrame(0);
			PearlHarbourScene++;
		}
	}
	//TO DO, ADD ANIMATION OF PLANE CRASHING INTO A HARBOUR, THEN LEVEL IS DONE
	else {
		_LEVEL = "_MainMenu";
	}
	return window;
}

bool DinseyPlanes::GetKey(char KeyCode)
{
	return GetAsyncKeyState(KeyCode) && 0x8000;
}
