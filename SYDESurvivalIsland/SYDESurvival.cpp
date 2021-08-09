#include "SYDESurvival.h"
AssetsClass SYDESurvival::astVars = AssetsClass();
void SYDESurvival::init()
{
	test();
}

void SYDESurvival::test()
{
	vector<ColourClass> colour_array = vector<ColourClass>();
	for (int i = 0; i < (_width*2) * _height; i++)
	{
		colour_array.push_back(BLACK);
	}
	m_Island = CustomAsset(_width * 2, _height, colour_array);
	srand(NULL);
	PerlinNoise pn(rand() % 100);
	for (int i = 0; i < _height; ++i) 
	{     // y
		for (int j = 0; j < _width; ++j) 
		{  // x
			double x = (double)j / ((double)_width);
			double y = (double)i / ((double)_height);
			
			double n = pn.noise(10 * x, 10 * y, 0.8);

			//FORCE NOISE
			if (i < gradientLength || i > _height - gradientLength)
			{
				int diff = i;
				if (i > _height - gradientLength)
				{
					diff = abs(i - _height);
				}

				n -= (gradientStrength / (diff + 1));
			}
			if (j < gradientLength || j > _width - gradientLength)
			{
				int diff = j;
				if (j > _width - gradientLength)
				{
					diff = abs(j - _width);
				}
				n -= (gradientStrength / (diff + 1));
			}


			// Water (or a Lakes)
			if (n < 0.5) {
				m_Island.setColourAtPoint(Vector2(j * 2, i), BLUE_BLUE_BG);
				m_Island.setColourAtPoint(Vector2((j * 2) + 1, i), BLUE_BLUE_BG);
			}
			// Sand
			else if (n >= 0.5 && n < .525) 
			{
				m_Island.setColourAtPoint(Vector2(j * 2, i), BRIGHTYELLOW_BRIGHTYELLOW_BG);
				m_Island.setColourAtPoint(Vector2((j * 2) + 1, i), BRIGHTYELLOW_BRIGHTYELLOW_BG);
			}
			// Land
			else if (n >= 0.525 && n < 0.575) 
			{
				m_Island.setColourAtPoint(Vector2(j * 2, i), GREEN_GREEN_BG);
				m_Island.setColourAtPoint(Vector2((j * 2) + 1, i), GREEN_GREEN_BG);
			}
			// Grass
			else if (n >= 0.575 && n < 0.675)
			{
				m_Island.setColourAtPoint(Vector2(j * 2, i), BRIGHTGREEN_GREEN_BG);
				m_Island.setColourAtPoint(Vector2((j * 2) + 1, i), BRIGHTGREEN_GREEN_BG);
				m_Island.setCharAtPoint(Vector2(j * 2, i), 'v');
				m_Island.setCharAtPoint(Vector2((j * 2) + 1, i), 'v');
			}
			//TREES
			else if (n >= 0.675 && n < 0.775)
			{
				m_Island.setColourAtPoint(Vector2(j * 2, i), BLACK_GREEN_BG);
				m_Island.setColourAtPoint(Vector2((j * 2) + 1, i), BLACK_GREEN_BG);
				m_Island.setCharAtPoint(Vector2(j * 2, i), '*');
				m_Island.setCharAtPoint(Vector2((j * 2) + 1, i), '*');
			}
			//STONE
			else
			{
				m_Island.setColourAtPoint(Vector2(j * 2, i), LIGHTGREY_GREEN_BG);
				m_Island.setColourAtPoint(Vector2((j * 2) + 1, i), LIGHTGREY_GREEN_BG);
				m_Island.setCharAtPoint(Vector2(j * 2, i), '(');
				m_Island.setCharAtPoint(Vector2((j * 2) + 1, i), ')');
			}
		}
	}

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
	return window;
}
