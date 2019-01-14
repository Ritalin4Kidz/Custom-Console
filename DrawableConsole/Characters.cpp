#include "pch.h"
#include "Characters.h"
#include "Vector2.h"

ConsoleWindow Characters::draw_truck_syde_001(ConsoleWindow window, Vector2 point)
{
	//OUTLINE 1
	for (int i = -2; i < 29; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 1), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 12), " ", BLACK);
	}
	for (int i = 27; i < 29; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = -2; i < 0; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = -2; i < 0; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	//FILL 1
	for (int i = 0; i < 27; i++)
	{
		for (int ii = 2; ii < 12; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
	}
	//FILL 2
	for (int i = 1; i < 7; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 8), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", BLACK);
	}
	for (int i = 1; i < 3; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 9), " ", BLACK);
	}
	for (int i = 5; i < 7; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 7), " ", BLACK);
	}
	for (int i = 7; i < 9; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 11; i < 13; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 7; i < 13; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 9), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 6; i < 9; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + 9, point.getY() - i), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + 10, point.getY() - i), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 13; i < 17; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", BLACK);
	}
	for (int i = 7; i < 10; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + 13, point.getY() - i), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + 14, point.getY() - i), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + 17, point.getY() - i), " ", BLACK);
		window.setTextAtPoint(Vector2(point.getX() + 18, point.getY() - i), " ", BLACK);
	}
	for (int i = 19; i < 25; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 10), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 8), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	for (int i = 19; i < 21; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 9), " ", LIGHTGREY_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 7), " ", LIGHTGREY_LIGHTGREY_BG);
	}
	//WHEELS 1
	for (int i = 0; i < 6; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(point.getX() + 0, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 1, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	for (int i = 19; i < 25; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(point.getX() + 19, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 20, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 23, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 24, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	//OUTLINE 2
	for (int i = 29; i < 31; i++)
	{
		for (int ii = 1; ii < 13; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 31; i < 33; i++)
	{
		for (int ii = 1; ii < 12; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 33; i < 35; i++)
	{
		for (int ii = 1; ii < 11; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 35; i < 37; i++)
	{
		for (int ii = 1; ii < 10; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 37; i < 41; i++)
	{
		for (int ii = 1; ii < 7; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	for (int i = 41; i < 43; i++)
	{
		for (int ii = 2; ii < 6; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 4), "K", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 4), "i", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 4), "d", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 6, point.getY() - 4), "n", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 7, point.getY() - 4), "a", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 8, point.getY() - 4), "p", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 9, point.getY() - 4), "p", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 10, point.getY() - 4), "i", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 11, point.getY() - 4), "n", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 12, point.getY() - 4), "g", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 13, point.getY() - 4), " ", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 14, point.getY() - 4), "S", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 15, point.getY() - 4), "i", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 16, point.getY() - 4), "n", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 17, point.getY() - 4), "c", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 18, point.getY() - 4), "e", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 19, point.getY() - 4), " ", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 20, point.getY() - 4), "1", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 21, point.getY() - 4), "9", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 22, point.getY() - 4), "8", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 23, point.getY() - 4), "3", BLACK_BRIGHTWHITE_BG);
	//FILL 1
	for (int i = 31; i < 35; i++)
	{
		for (int ii = 6; ii < 10; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", AQUA_LIGHTBLUE_BG);
		}
	}
	window.setTextAtPoint(Vector2(point.getX() + 31, point.getY() - 10), " ", AQUA_LIGHTBLUE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 32, point.getY() - 10), " ", AQUA_LIGHTBLUE_BG);

	window.setTextAtPoint(Vector2(point.getX() + 41, point.getY() - 2), " ", AQUA_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(point.getX() + 42, point.getY() - 2), " ", AQUA_BRIGHTYELLOW_BG);
	//WHEELS
	for (int i = 33; i < 39; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(point.getX() + 33, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 34, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 37, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	window.setTextAtPoint(Vector2(point.getX() + 38, point.getY() - 1), " ", LIGHTBLUE_WHITE_BG);
	return window;
}

ConsoleWindow Characters::draw_girl_diptio_park(ConsoleWindow window, Vector2 point)
{
	window.setTextAtPoint(Vector2(point.getX() + 0, point.getY() + 0), " ", LIGHTBLUE_WHITE_BG);
	for (int i = 0; i < 4; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 0), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 1), " ", BLACK);
		for (int ii = 2; ii < 5; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", LIGHTBLUE_GREEN_BG);
		}
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 5), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTBLUE_WHITE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 7), " ", LIGHTBLUE_DARKBLUE_BG);
	}
	for (int i = -2; i < 0; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
		for (int ii = 3; ii < 5; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", LIGHTBLUE_GREEN_BG);
		}
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 5), " ", LIGHTBLUE_DARKBLUE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTBLUE_DARKBLUE_BG);
	}
	for (int i = 4; i < 6; i++)
	{
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 2), " ", LIGHTBLUE_WHITE_BG);
		for (int ii = 3; ii < 5; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - ii), " ", LIGHTBLUE_GREEN_BG);
		}
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 5), " ", LIGHTBLUE_DARKBLUE_BG);
		window.setTextAtPoint(Vector2(point.getX() + i, point.getY() - 6), " ", LIGHTBLUE_DARKBLUE_BG);
	}
	return window;
}

ConsoleWindow Characters::draw_player(ConsoleWindow window, Vector2 point, ColourClass Clothes1, ColourClass Clothes2, ColourClass Accessory, ColourClass Skin, string lookAngle, string charName)
{
	//PANTS
	for (int i = 0; i < 4; i++)
	{
		for (int ii = 0; ii < 4; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Clothes2);
		}
	}
	//SHIRT
	for (int i = 3; i < 7; i++)
	{
		for (int ii = -2; ii < 6; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Clothes1);
		}
	}
	//HEAD
	for (int i = 6; i < 8; i++)
	{
		for (int ii = 0; ii < 4; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Skin);
		}
	}
	//BADGE
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() - 5), " ", Accessory);
	window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 5), " ", Accessory);
	//HANDS
	window.setTextAtPoint(Vector2(point.getX() - 2, point.getY() - 3), " ", Skin);
	window.setTextAtPoint(Vector2(point.getX() - 1, point.getY() - 3), " ", Skin);

	window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 3), " ", Skin);
	window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 3), " ", Skin);
	if (charName == "Nude_Lunatic")
	{
		for (int x = -2; x < 6; x++)
		{
			for (int y = 2; y < 3; y++)
			{
				window.setTextAtPoint(Vector2(point.getX() + x, point.getY() - y), " ", BLACK);
			}
		}
	}
	//HAT
	if (charName != "Nude_Lunatic")
	{
		for (int i = 8; i < 10; i++)
		{
			for (int ii = 0; ii < 4; ii++)
			{
				window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), " ", Clothes1);
			}
		}
		if (lookAngle == "Right")
		{
			window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 8), " ", Clothes1);
			window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 8), " ", Clothes1);
		}
		else if (lookAngle == "Left")
		{
			window.setTextAtPoint(Vector2(point.getX() - 1, point.getY() - 8), " ", Clothes1);
			window.setTextAtPoint(Vector2(point.getX() - 2, point.getY() - 8), " ", Clothes1);
		}
	}
	if (charName == "Nude_Lunatic")
	{
		window.setTextAtPoint(Vector2(point.getX() + 0, point.getY() - 8), " ", Clothes1);
		window.setTextAtPoint(Vector2(point.getX() + 1, point.getY() - 8), " ", Clothes1);
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() - 8), " ", Clothes1);
		window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 8), " ", Clothes1);
	}
	return window;
}

ConsoleWindow Characters::draw_player_wireframe(ConsoleWindow window, Vector2 point, ColourClass Clothes1, ColourClass Clothes2, ColourClass Accessory, ColourClass Skin, string lookAngle, string charName)
{
	//PANTS
	for (int i = 0; i < 4; i++)
	{
		for (int ii = 0; ii < 4; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), "#", window.determineColourAtPoint(Vector2(point.getX() + ii, point.getY() - i),Clothes2, true));
		}
	}
	//SHIRT
	for (int i = 3; i < 7; i++)
	{
		for (int ii = -2; ii < 6; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), "#", window.determineColourAtPoint(Vector2(point.getX() + ii, point.getY() - i), Clothes1, true));
		}
	}
	//HEAD
	for (int i = 6; i < 8; i++)
	{
		for (int ii = 0; ii < 4; ii++)
		{
			window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), "#", window.determineColourAtPoint(Vector2(point.getX() + ii, point.getY() - i), Skin, true));
		}
	}
	//BADGE
	window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() - 5), "#", window.determineColourAtPoint(Vector2(point.getX() + 2, point.getY() - 5), Accessory, true));
	window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 5), "#", window.determineColourAtPoint(Vector2(point.getX() + 3, point.getY() - 5), Accessory, true));
	//HANDS
	window.setTextAtPoint(Vector2(point.getX() - 2, point.getY() - 3), "#", window.determineColourAtPoint(Vector2(point.getX() - 2, point.getY() - 3), Skin, true));
	window.setTextAtPoint(Vector2(point.getX() - 1, point.getY() - 3), "#", window.determineColourAtPoint(Vector2(point.getX() - 1, point.getY() - 3), Skin, true));
																																					   
	window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 3), "#", window.determineColourAtPoint(Vector2(point.getX() + 4, point.getY() - 3), Skin, true));
	window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 3), "#", window.determineColourAtPoint(Vector2(point.getX() + 5, point.getY() - 3), Skin, true));
	if (charName == "Nude_Lunatic")
	{
		for (int x = -2; x < 6; x++)
		{
			for (int y = 2; y < 3; y++)
			{
				window.setTextAtPoint(Vector2(point.getX() + x, point.getY() - y), "#", window.determineColourAtPoint(Vector2(point.getX() + x, point.getY() - y), BLACK, true));
			}
		}
	}
	//HAT
	if (charName != "Nude_Lunatic")
	{
		for (int i = 8; i < 10; i++)
		{
			for (int ii = 0; ii < 4; ii++)
			{
				window.setTextAtPoint(Vector2(point.getX() + ii, point.getY() - i), "#", window.determineColourAtPoint(Vector2(point.getX() + ii, point.getY() - i), Clothes1, true));
			}
		}
		if (lookAngle == "Right")
		{
			window.setTextAtPoint(Vector2(point.getX() + 4, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() + 4, point.getY() - 8), Clothes1, true));
			window.setTextAtPoint(Vector2(point.getX() + 5, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() + 5, point.getY() - 8), Clothes1, true));
		}
		else if (lookAngle == "Left")
		{
			window.setTextAtPoint(Vector2(point.getX() - 1, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() - 1, point.getY() - 8), Clothes1, true));
			window.setTextAtPoint(Vector2(point.getX() - 2, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() - 2, point.getY() - 8), Clothes1, true));
		}
	}
	if (charName == "Nude_Lunatic")
	{
		window.setTextAtPoint(Vector2(point.getX() + 0, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() + 0, point.getY() - 8), Clothes1, true));
		window.setTextAtPoint(Vector2(point.getX() + 1, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() + 1, point.getY() - 8), Clothes1, true));
		window.setTextAtPoint(Vector2(point.getX() + 2, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() + 2, point.getY() - 8), Clothes1, true));
		window.setTextAtPoint(Vector2(point.getX() + 3, point.getY() - 8), "#", window.determineColourAtPoint(Vector2(point.getX() + 3, point.getY() - 8), Clothes1, true));
	}
	return window;
}
