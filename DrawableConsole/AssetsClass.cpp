#include "pch.h"
#include <vector>
#include "Vector2.h"
#include "AssetsClass.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace std;
using namespace Gdiplus;
using namespace std;
//LOOK AT BITMAP
LPCWSTR AssetsClass::explosion_file_path = L"EngineFiles\\Sounds\\explosion.wav";
vector<string> AssetsClass::BLACK_RGB = { "12","12","12" };
vector<string> AssetsClass::BLUE_RGB = { "0","55","218" };
vector<string> AssetsClass::GREEN_RGB = { "19","161","14" };
vector<string> AssetsClass::AQUA_RGB = { "58","150","221" };
vector<string> AssetsClass::RED_RGB = { "197","15","31" };
vector<string> AssetsClass::PURPLE_RGB = { "136","23","152" };
vector<string> AssetsClass::YELLOW_RGB = { "193","156","0" };
vector<string> AssetsClass::WHITE_RGB = { "204","204","204" };
vector<string> AssetsClass::LIGHTGREY_RGB = { "118","118","118" };
vector<string> AssetsClass::DARKBLUE_RGB = { "59","120","255" };
vector<string> AssetsClass::BRIGHTGREEN_RGB = { "22","198","12" };
vector<string> AssetsClass::LIGHTBLUE_RGB = { "97","214","214" };
vector<string> AssetsClass::BRIGHTRED_RGB = { "231","72","86" };
vector<string> AssetsClass::LIGHTPURPLE_RGB = { "180","0","158" };
vector<string> AssetsClass::BRIGHTYELLOW_RGB = { "249","241","165" };
vector<string> AssetsClass::BRIGHTWHITE_RGB = { "242","242","242" };
const int AssetsClass::get_file_size(char * filename)
{
	FILE* f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	fclose(f);
	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	const int size = 4 * width * height;
	return size;
}

vector<unsigned char> AssetsClass::get_data_from_bmp(char * filename)
{
	int i;
	//PROPERLY CHECK FILE
	FILE* f = fopen(filename, "rb");
	unsigned char data[1600]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), 1600, f); // read the rest of the data at once
	vector<unsigned char> newdata;
	fclose(f);
	for (i = 0; i < 1600; i += 4)
	{
		unsigned char tmp = data[i + 1];
		data[i + 1] = data[i + 3];
		data[i + 3] = tmp;
	}
	for (int ii = 0; ii < 1600; ii++)
	{
		newdata.push_back(data[ii]);
	}
	return newdata;
}

vector<vector<unsigned char>> AssetsClass::convert_to_rgb_vector(vector<unsigned char> data)
{
	vector<vector<unsigned char>> newData;
	for (int i = 0; i < 1600; i += 4)
	{
		newData.push_back(vector<unsigned char>{data[i + 1], data[i + 2], data[i + 3]});
	}
	return newData;
}

bool AssetsClass::rgb_match(vector<string> rgb, string r, string g, string b)
{
	return r == rgb[0] && g == rgb[1] && b == rgb[2] ;
}

bool AssetsClass::rgb_compare(vector<string> rgb, string r, string g, string b)
{
	return r == rgb[0] && g == rgb[1] && b == rgb[2];
}

ColourClass AssetsClass::return_colour_from_RGB(string r, string g, string b)
{
	if (rgb_match(get_BLACK_RGB(), r, g, b))
	{
		return BLACK;
	}
	if (rgb_match(get_BLUE_RGB(), r, g, b))
	{
		return BLUE_BLUE_BG;
	}
	if (rgb_match(get_GREEN_RGB(), r, g, b))
	{
		return GREEN_GREEN_BG;
	}
	if (rgb_match(get_AQUA_RGB(), r, g, b))
	{
		return AQUA_AQUA_BG;
	}
	if (rgb_match(get_RED_RGB(), r, g, b))
	{
		return RED_RED_BG;
	}
	if (rgb_match(get_PURPLE_RGB(), r, g, b))
	{
		return PURPLE_PURPLE_BG;
	}
	if (rgb_match(get_YELLOW_RGB(), r, g, b))
	{
		return YELLOW_YELLOW_BG;
	}
	if (rgb_match(get_WHITE_RGB(), r, g, b))
	{
		return WHITE_WHITE_BG;
	}
	if (rgb_match(get_LIGHTGREY_RGB(), r, g, b))
	{
		return LIGHTGREY_LIGHTGREY_BG;
	}
	if (rgb_match(get_DARKBLUE_RGB(), r, g, b))
	{
		return DARKBLUE_DARKBLUE_BG;
	}
	if (rgb_match(get_BRIGHTGREEN_RGB(), r, g, b))
	{
		return BRIGHTGREEN_BRIGHTGREEN_BG;
	}
	if (rgb_match(get_LIGHTBLUE_RGB(), r, g, b))
	{
		return LIGHTBLUE_LIGHTBLUE_BG;
	}
	if (rgb_match(get_BRIGHTRED_RGB(), r, g, b))
	{
		return BRIGHTRED_BRIGHTRED_BG;
	}
	if (rgb_match(get_LIGHTPURPLE_RGB(), r, g, b))
	{
		return LIGHTPURPLE_LIGHTPURPLE_BG;
	}
	if (rgb_match(get_BRIGHTYELLOW_RGB(), r, g, b))
	{
		return BRIGHTYELLOW_BRIGHTYELLOW_BG;
	}
	if (rgb_match(get_BRIGHTWHITE_RGB(), r, g, b))
	{
		return BRIGHTWHITE_BRIGHTWHITE_BG;
	}
	return NULLCOLOUR;
}

ColourClass AssetsClass::colour_from_RGB(string r, string g, string b)
{
	if (rgb_compare(get_BLACK_RGB(), r, g, b))
	{
		return BLACK;
	}
	if (rgb_compare(get_BLUE_RGB(), r, g, b))
	{
		return BLUE_BLUE_BG;
	}
	if (rgb_compare(get_GREEN_RGB(), r, g, b))
	{
		return GREEN_GREEN_BG;
	}
	if (rgb_compare(get_AQUA_RGB(), r, g, b))
	{
		return AQUA_AQUA_BG;
	}
	if (rgb_compare(get_RED_RGB(), r, g, b))
	{
		return RED_RED_BG;
	}
	if (rgb_compare(get_PURPLE_RGB(), r, g, b))
	{
		return PURPLE_PURPLE_BG;
	}
	if (rgb_compare(get_YELLOW_RGB(), r, g, b))
	{
		return YELLOW_YELLOW_BG;
	}
	if (rgb_compare(get_WHITE_RGB(), r, g, b))
	{
		return WHITE_WHITE_BG;
	}
	if (rgb_compare(get_LIGHTGREY_RGB(), r, g, b))
	{
		return LIGHTGREY_LIGHTGREY_BG;
	}
	if (rgb_compare(get_DARKBLUE_RGB(), r, g, b))
	{
		return DARKBLUE_DARKBLUE_BG;
	}
	if (rgb_compare(get_BRIGHTGREEN_RGB(), r, g, b))
	{
		return BRIGHTGREEN_BRIGHTGREEN_BG;
	}
	if (rgb_compare(get_LIGHTBLUE_RGB(), r, g, b))
	{
		return LIGHTBLUE_LIGHTBLUE_BG;
	}
	if (rgb_compare(get_BRIGHTRED_RGB(), r, g, b))
	{
		return BRIGHTRED_BRIGHTRED_BG;
	}
	if (rgb_compare(get_LIGHTPURPLE_RGB(), r, g, b))
	{
		return LIGHTPURPLE_LIGHTPURPLE_BG;
	}
	if (rgb_compare(get_BRIGHTYELLOW_RGB(), r, g, b))
	{
		return BRIGHTYELLOW_BRIGHTYELLOW_BG;
	}
	if (rgb_compare(get_BRIGHTWHITE_RGB(), r, g, b))
	{
		return BRIGHTWHITE_BRIGHTWHITE_BG;
	}
	return NULLCOLOUR;
}

ConsoleWindow AssetsClass::draw_bmp_on_window(ConsoleWindow window, const WCHAR* bmpFile, Vector2 bmpfilepoint, Vector2 point, int windowWidth, int windowHeight, int bmpWidth, int bmpHeight)
{
	//EDIT NEEDED, ADJUST SO THAT POINT ACTUALLY WORKS, WE CAN SPAWN FROM DIFFERENT POSITIONS
	Bitmap temp(bmpFile, FALSE);
	int vectorgetPixelx = bmpfilepoint.getX();
	int vectorgetPixely = bmpfilepoint.getY();
	for (int ii = bmpfilepoint.getY(); ii < bmpHeight; ii++)
	{
		vector<Color> linecolorArray;
		for (int i = bmpfilepoint.getX(); i < bmpWidth; i++)
		{
			Gdiplus::Color pixelColor;
			temp.GetPixel(i, ii, &pixelColor);
			linecolorArray.push_back(pixelColor);
			linecolorArray.push_back(pixelColor);
		}
		for (int i = 0; i < linecolorArray.size(); i++)
		{
			window.setTextAtPoint(Vector2(i + point.getX(), ii), " ", return_colour_from_RGB(to_string(linecolorArray[i].GetR()), to_string(linecolorArray[i].GetG()), to_string(linecolorArray[i].GetB())));
		}
	}
	return window;
}

vector<ColourClass> AssetsClass::get_bmp_as_direct_colour_class_array(const WCHAR * bmpFile, int bmpWidth, int bmpHeight)
{
	Bitmap temp(bmpFile, FALSE);
	vector<ColourClass> tempVec;
	for (int i = 0; i < bmpHeight; i++)
	{
		for (int ii = 0; ii < bmpWidth; ii++)
		{
			Gdiplus::Color pixelColor;
			temp.GetPixel(ii + 1, i, &pixelColor);
			ColourClass colour_use = return_colour_from_RGB(to_string(pixelColor.GetR()), to_string(pixelColor.GetG()), to_string(pixelColor.GetB()));
			tempVec.push_back(colour_use); //twice for one pixel
			tempVec.push_back(colour_use);
		}
	}
	return tempVec;
}

vector<ColourClass> AssetsClass::get_bmp_as_array(const WCHAR* bmpFile, int bmpWidth, int bmpHeight)
{
	Bitmap temp(bmpFile, FALSE);
	vector<ColourClass> tempVec;
	for (int i = 0; i < bmpHeight; i++)
	{
		for (int ii = 0; ii < bmpWidth; ii++)
		{
			Gdiplus::Color pixelColor;
			temp.GetPixel(ii, i, &pixelColor);
			ColourClass colour_use = colour_from_RGB(to_string(pixelColor.GetR()), to_string(pixelColor.GetG()), to_string(pixelColor.GetB()));
			tempVec.push_back(colour_use); //twice for one pixel
			tempVec.push_back(colour_use);
		}
	}
	return tempVec;
}

vector<string> AssetsClass::ColourToRGBStrArray(ColourClass c)
{
	if (c < BLACK_BLUE_BG)
	{
		return get_BLACK_RGB();
	}
	if (c >= BLACK_BLUE_BG && c < BLACK_GREEN_BG)
	{
		return get_BLUE_RGB();
	}

	if (c >= BLACK_GREEN_BG && c < BLACK_AQUA_BG)
	{
		return get_GREEN_RGB();
	}

	if (c >= BLACK_AQUA_BG && c < BLACK_RED_BG)
	{
		return get_AQUA_RGB();
	}

	if (c >= BLACK_RED_BG && c < BLACK_PURPLE_BG)
	{
		return get_RED_RGB();
	}

	if (c >= BLACK_PURPLE_BG && c < BLACK_YELLOW_BG)
	{
		return get_PURPLE_RGB();
	}

	if (c >= BLACK_YELLOW_BG && c < BLACK_WHITE_BG)
	{
		return get_YELLOW_RGB();
	}

	if (c >= BLACK_WHITE_BG && c < BLACK_LIGHTGREY_BG)
	{
		return get_WHITE_RGB();
	}

	if (c >= BLACK_LIGHTGREY_BG && c < BLACK_DARKBLUE_BG)
	{
		return get_LIGHTGREY_RGB();
	}

	if (c >= BLACK_DARKBLUE_BG && c < BLACK_BRIGHTGREEN_BG)
	{
		return get_DARKBLUE_RGB();
	}

	if (c >= BLACK_BRIGHTGREEN_BG && c < BLACK_LIGHTBLUE_BG)
	{
		return get_BRIGHTGREEN_RGB();
	}

	if (c >= BLACK_LIGHTBLUE_BG && c < BLACK_BRIGHTRED_BG)
	{
		return get_LIGHTBLUE_RGB();
	}

	if (c >= BLACK_BRIGHTRED_BG && c < BLACK_LIGHTPURPLE_BG)
	{
		return get_BRIGHTRED_RGB();
	}

	if (c >= BLACK_LIGHTPURPLE_BG && c < BLACK_BRIGHTYELLOW_BG)
	{
		return get_LIGHTPURPLE_RGB();
	}

	if (c >= BLACK_BRIGHTYELLOW_BG && c < BLACK_BRIGHTWHITE_BG)
	{
		return get_BRIGHTYELLOW_RGB();
	}

	if (c >= BLACK_BRIGHTWHITE_BG && c <= BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		return get_BRIGHTWHITE_RGB();
	}
	return get_BLACK_RGB();
}




