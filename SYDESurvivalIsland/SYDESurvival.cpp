#include "SYDESurvival.h"
AssetsClass SYDESurvival::astVars = AssetsClass();
void SYDESurvival::init()
{
	test();
	m_ButtonMenu.setSpacing(1);
	m_Radial.setSpacing(-1);
}

void SYDESurvival::test()
{
	srand(time(NULL));
	SYDENoiseMap noiseMap = SYDENoiseMap(
		vector<SYDENoiseMapRule>(
			{
				SYDENoiseMapRule(0,0.5, BLUE_BLUE_BG, ' '),
				SYDENoiseMapRule(0.5,0.525, BRIGHTYELLOW_BRIGHTYELLOW_BG, ' '),
				SYDENoiseMapRule(0.555,0.557, LIGHTGREY_GREEN_BG, '(', ')'),
				SYDENoiseMapRule(0.755,0.757, LIGHTGREY_GREEN_BG, '(', ')'),
				SYDENoiseMapRule(0.575,0.675, BRIGHTGREEN_GREEN_BG, 'v'),
				SYDENoiseMapRule(0.675,0.695, BLACK_GREEN_BG, '*'),
			}),
			GREEN_GREEN_BG,
			rand(),
			_width,
			_height,
			gradientLength,
			gradientStrength
	);
	m_Island = noiseMap.getAsset();
	//m_Island.ExportAssetToFile();
}

ConsoleWindow SYDESurvival::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLUE_BLUE_BG);
		}
	}
	window = m_Island.draw_asset(window, m_CameraPos, windowWidth, windowHeight);
	if (SYDEKeyCode::get_key('W')._CompareState(KEY))
	{
		if (m_CameraPos.getY() > 0)
		{
			m_CameraPos.addY(-1);
		}
	}
	if (SYDEKeyCode::get_key('S')._CompareState(KEY))
	{
		if (m_CameraPos.getY() < _height)
		{
			m_CameraPos.addY(1);
		}
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY))
	{
		if (m_CameraPos.getX() < _width * 2)
		{
			m_CameraPos.addX(1);
		}
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY))
	{
		if (m_CameraPos.getX() > 0)
		{
			m_CameraPos.addX(-1);
		}
	}
	window.setTextAtPoint(Vector2(0, 19), std::to_string(m_CameraPos.getX()) + "," + std::to_string(m_CameraPos.getY()), BLACK_BRIGHTWHITE_BG);
	//window = m_ButtonMenu.draw_ui(window);
	window = m_Radial.draw_ui(window);
	return window;
}
