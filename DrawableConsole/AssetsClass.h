#pragma once
#include <string>
#include <vector>
#include "Vector2.h"
#include <windows.h>
#include <objidl.h>
#include "ConsoleWindow.h"
#include <gdiplus.h>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
struct ColorRGB_SYDE {
	ColorRGB_SYDE(int R, int B, int G, int A) { r = R; b = B; g = G; a = A; }
	int r;
	int g;
	int b;
	int a;
};

class AssetsClass {
public:
	AssetsClass() {}
	virtual ~AssetsClass() {}

	const int get_file_size(char* filename);
	//THIS NEEDS BETTER WORKING, WORKS TO 20x20
	vector<unsigned char> get_data_from_bmp(char* filename);
	vector<vector<unsigned char>> convert_to_rgb_vector(vector<unsigned char> data);

	bool rgb_match(vector<string> rgb, string r, string g, string b);
	ColourClass return_colour_from_RGB(string r, string g, string b);
	ConsoleWindow draw_bmp_on_window(ConsoleWindow window, const WCHAR* bmpFile, Vector2 bmpfilepoint, Vector2 point, int windowWidth, int windowHeight, int bmpWidth, int bmpHeight);

	char* get_test_bmp_path() { return test_bmp_path; }
	vector<ColourClass> get_bmp_as_direct_colour_class_array(const WCHAR* bmpFile, int bmpWidth, int bmpHeight);
	LPCWSTR get_electronic_chime_file_path() { return electronic_chime_file_path; }
	LPCWSTR get_squish_file_path() { return squish_file_path; }
	static LPCWSTR get_explosion_file_path() { return explosion_file_path; }

	static vector<string> get_BLACK_RGB() { return BLACK_RGB; }
	static vector<string> get_BLUE_RGB() { return BLUE_RGB; }
	static vector<string> get_GREEN_RGB() { return GREEN_RGB; }
	static vector<string> get_AQUA_RGB() { return AQUA_RGB; }
	static vector<string> get_RED_RGB() { return RED_RGB; }
	static vector<string> get_PURPLE_RGB() { return PURPLE_RGB; }
	static vector<string> get_YELLOW_RGB() { return YELLOW_RGB; }
	static vector<string> get_WHITE_RGB() { return WHITE_RGB; }
	static vector<string> get_LIGHTGREY_RGB() { return LIGHTGREY_RGB; }
	static vector<string> get_DARKBLUE_RGB() { return DARKBLUE_RGB; }
	static vector<string> get_BRIGHTGREEN_RGB() { return BRIGHTGREEN_RGB; }
	static vector<string> get_LIGHTBLUE_RGB() { return LIGHTBLUE_RGB; }
	static vector<string> get_BRIGHTRED_RGB() { return BRIGHTRED_RGB; }
	static vector<string> get_LIGHTPURPLE_RGB() { return LIGHTPURPLE_RGB; }
	static vector<string> get_BRIGHTYELLOW_RGB() { return BRIGHTYELLOW_RGB; }
	static vector<string> get_BRIGHTWHITE_RGB() { return BRIGHTWHITE_RGB; }

	static vector<string> ColourToRGBStrArray(ColourClass c);

private:
	LPCWSTR electronic_chime_file_path = L"EngineFiles\\Sounds\\electronicchime.wav";
	LPCWSTR squish_file_path = L"EngineFiles\\Sounds\\squish.wav";
	static LPCWSTR explosion_file_path;
	char* test_bmp_path = (char*)"EngineFiles\\TestBitmaps\\testfile2.bmp";


	//BITMAP SETTINGS
	static vector<string> BLACK_RGB;
	static vector<string> BLUE_RGB;
	static vector<string> GREEN_RGB;
	static vector<string> AQUA_RGB;
	static vector<string> RED_RGB;
	static vector<string> PURPLE_RGB;
	static vector<string> YELLOW_RGB;
	static vector<string> WHITE_RGB;
	static vector<string> LIGHTGREY_RGB;
	static vector<string> DARKBLUE_RGB;
	static vector<string> BRIGHTGREEN_RGB;
	static vector<string> LIGHTBLUE_RGB;
	static vector<string> BRIGHTRED_RGB;
	static vector<string> LIGHTPURPLE_RGB;
	static vector<string> BRIGHTYELLOW_RGB;
	static vector<string> BRIGHTWHITE_RGB;
};