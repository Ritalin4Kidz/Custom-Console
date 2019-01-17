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



