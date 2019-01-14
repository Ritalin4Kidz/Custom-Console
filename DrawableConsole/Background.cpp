#include "pch.h"
#include "Background.h"

ConsoleWindow BackgroundClass::draw_diptio_park_cutscene_bg(ConsoleWindow window,int windowWidth, int windowHeight)
{
	//CLOUDS
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", LIGHTBLUE_LIGHTBLUE_BG);
		}
	}
	window.setTextAtPoint(Vector2(0, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(1, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(2, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(3, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(0, 3), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(1, 3), " ", LIGHTBLUE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(19, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(20, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(21, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(22, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);

	window.setTextAtPoint(Vector2(35, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(36, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(37, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(38, 1), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(37, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(38, 2), " ", LIGHTBLUE_BRIGHTWHITE_BG);
	//GRASS
	for (int i = 0; i < 40; i++)
	{
		for (int ii = 16; ii < 18; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		}
	}
	//SIDEWALK
	for (int i = 0; i < 40; i++)
	{
		for (int ii = 18; ii < 21; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTBLUE_LIGHTGREY_BG);
		}
	}
	//TREE
	for (int i = 0; i < 22; i++)
	{
		window.setTextAtPoint(Vector2(i, 15), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 2; i < 20; i++)
	{
		window.setTextAtPoint(Vector2(i, 14), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 2; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 13), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 12), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 4; i < 16; i++)
	{
		window.setTextAtPoint(Vector2(i, 11), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 10), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 6; i < 16; i++)
	{
		window.setTextAtPoint(Vector2(i, 9), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 8), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 8; i < 20; i++)
	{
		window.setTextAtPoint(Vector2(i, 7), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 8; i < 14; i++)
	{
		window.setTextAtPoint(Vector2(i, 6), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 5), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 2), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 1), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 18; i < 24; i++)
	{
		window.setTextAtPoint(Vector2(i, 6), " ", LIGHTBLUE_YELLOW_BG);
	}
	//LEAVES
	for (int i = 4; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 1), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 4; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(i, 2), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 2; i < 4; i++)
	{
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 6; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(i, 5), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 12; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 2), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 14; i < 16; i++)
	{
		window.setTextAtPoint(Vector2(i, 3), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 16; i < 18; i++)
	{
		window.setTextAtPoint(Vector2(i, 4), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 22; i < 24; i++)
	{
		window.setTextAtPoint(Vector2(i, 5), " ", LIGHTBLUE_BRIGHTGREEN_BG);
		window.setTextAtPoint(Vector2(i, 7), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	for (int i = 24; i < 26; i++)
	{
		window.setTextAtPoint(Vector2(i, 6), " ", LIGHTBLUE_BRIGHTGREEN_BG);
	}
	//FENCE
	for (int i = 0; i < 40; i += 4)
	{
		for (int ii = 12; ii < 17; ii++)
		{
			window.setTextAtPoint(Vector2(i + 0, ii), " ", LIGHTBLUE_LIGHTGREY_BG);
			window.setTextAtPoint(Vector2(i + 1, ii), " ", LIGHTBLUE_LIGHTGREY_BG);
		}
	}
	for (int i = 0; i < 40; i++)
	{
		window.setTextAtPoint(Vector2(i, 13), " ", LIGHTBLUE_LIGHTGREY_BG);
		window.setTextAtPoint(Vector2(i, 15), " ", LIGHTBLUE_LIGHTGREY_BG);
	}
	//BENCH
	for (int i = 25; i < 38; i++)
	{
		window.setTextAtPoint(Vector2(i, 14), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 15), " ", LIGHTBLUE_YELLOW_BG);
		window.setTextAtPoint(Vector2(i, 16), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 27; i < 36; i++)
	{
		window.setTextAtPoint(Vector2(i, 14), " ", BLACK);
		window.setTextAtPoint(Vector2(i, 15), " ", BLACK);
	}
	for (int i = 25; i < 27; i++)
	{
		window.setTextAtPoint(Vector2(i, 17), " ", LIGHTBLUE_YELLOW_BG);
	}
	for (int i = 36; i < 38; i++)
	{
		window.setTextAtPoint(Vector2(i, 17), " ", LIGHTBLUE_YELLOW_BG);
	}
	return window;
}

vector<BackgroundObj> BackgroundClass::draw_break_room_001(vector<BackgroundObj> bgArr, int windowWidth, int windowHeight)
{
	//BACKGROUND
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_LIGHTGREY_BG, Vector2(l, m), " "));
		}
	}
	//BENCH LOWER
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 16; m < windowHeight - 1; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_YELLOW_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 15; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int m = 16; m < windowHeight - 1; m++)
	{
		bgArr.push_back(BackgroundObj(BLACK, Vector2(0, m), " "));
	}
	bgArr.push_back(BackgroundObj(BLACK, Vector2(8, 17), " "));
	bgArr.push_back(BackgroundObj(BLACK, Vector2(7, 17), " "));
	for (int m = 16; m < windowHeight - 1; m++)
	{
		bgArr.push_back(BackgroundObj(BLACK, Vector2(10, m), " "));
	}
	bgArr.push_back(BackgroundObj(BLACK, Vector2(18, 17), " "));
	bgArr.push_back(BackgroundObj(BLACK, Vector2(17, 17), " "));
	for (int m = 16; m < windowHeight - 1; m++)
	{
		bgArr.push_back(BackgroundObj(BLACK, Vector2(20, m), " "));
	}
	bgArr.push_back(BackgroundObj(BLACK, Vector2(28, 17), " "));
	bgArr.push_back(BackgroundObj(BLACK, Vector2(27, 17), " "));
	for (int m = 16; m < windowHeight - 1; m++)
	{
		bgArr.push_back(BackgroundObj(BLACK, Vector2(30, m), " "));
	}
	bgArr.push_back(BackgroundObj(BLACK, Vector2(36, 17), " "));
	bgArr.push_back(BackgroundObj(BLACK, Vector2(37, 17), " "));
	for (int m = 16; m < windowHeight - 1; m++)
	{
		bgArr.push_back(BackgroundObj(BLACK, Vector2(39, m), " "));
	}

	//WINDOW
	for (int l = 10; l < 30; l++)
	{
		for (int m = 6; m < 13; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_LIGHTBLUE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 5; m < 6; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 9; m < 10; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 13; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 8; l < 10; l++)
	{
		for (int m = 5; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 30; l < 32; l++)
	{
		for (int m = 5; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	return bgArr;
}

vector<BackgroundObj> BackgroundClass::draw_break_room_002(vector<BackgroundObj> bgArr, int windowWidth, int windowHeight)
{
	//BACKGROUND
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_LIGHTGREY_BG, Vector2(l, m), " "));
		}
	}
	//WINDOW
	for (int l = 10; l < 30; l++)
	{
		for (int m = 6; m < 13; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_LIGHTBLUE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 5; m < 6; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 9; m < 10; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 13; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 8; l < 10; l++)
	{
		for (int m = 5; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 30; l < 32; l++)
	{
		for (int m = 5; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTWHITE_BG, Vector2(l, m), " "));
		}
	}
	//COUCH
	for (int l = 6; l < 34; l++)
	{
		for (int m = 14; m < 19; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_BRIGHTRED_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 9; l < 10; l++)
	{
		for (int m = 14; m < 19; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), "|"));
		}
	}
	for (int l = 30; l < 31; l++)
	{
		for (int m = 14; m < 19; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), "|"));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 17; m < 19; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_RED_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 10; l < 30; l++)
	{
		for (int m = 16; m < 17; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK_BRIGHTRED_BG, Vector2(l, m), "_"));
		}
	}
	//PILLOWS
	for (int l = 13; l < 18; l++)
	{
		for (int m = 15; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_AQUA_BG, Vector2(l, m), " "));
		}
		for (int m = 16; m < 17; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK_AQUA_BG, Vector2(l, m), "_"));
		}
	}

	for (int l = 21; l < 26; l++)
	{
		for (int m = 15; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_PURPLE_BG, Vector2(l, m), " "));
		}
		for (int m = 16; m < 17; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK_PURPLE_BG, Vector2(l, m), "_"));
		}
	}
	return bgArr;

}

vector<BackgroundObj> BackgroundClass::draw_holding_cell(vector<BackgroundObj> bgArr, int windowWidth, int windowHeight)
{
	//BACKGROUND
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_LIGHTGREY_BG, Vector2(l, m), " "));
		}
	}
	//CELL
	for (int l = 0; l < 10; l++)
	{
		for (int m = 13; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_YELLOW_BG, Vector2(l, m), " "));
		}
	}
	for (int l = 28; l < 38; l++)
	{
		for (int m = 13; m < 14; m++)
		{
			bgArr.push_back(BackgroundObj(YELLOW_YELLOW_BG, Vector2(l, m), " "));
		}
	}
	//TODO, ADD PERSON ON THE BENCH
	//BARS
	for (int l = 0; l < 2; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 4; l < 6; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 8; l < 10; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 12; l < 14; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 16; l < 18; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 20; l < 22; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 24; l < 26; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 28; l < 30; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 32; l < 34; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	for (int l = 36; l < 38; l++)
	{
		for (int m = 0; m < 16; m++)
		{
			bgArr.push_back(BackgroundObj(BLACK, Vector2(l, m), " "));
		}
	}
	return bgArr;
}


