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

	/// <summary>
	/// get the size of the file
	/// </summary>
	/// <param name="filename"></param>
	/// <returns>fileSize</returns>
	const int get_file_size(char* filename);
	//THIS NEEDS BETTER WORKING, WORKS TO 20x20
	/// <summary>
	/// get the data from the bmp file
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	vector<unsigned char> get_data_from_bmp(char* filename);
	vector<vector<unsigned char>> convert_to_rgb_vector(vector<unsigned char> data);

	/// <summary>
	/// Compare RGB
	/// </summary>
	/// <param name="rgb"></param>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <returns>true/false</returns>
	static bool rgb_match(vector<string> rgb, string r, string g, string b);
	/// <summary>
	/// Compare RGB
	/// </summary>
	/// <param name="rgb"></param>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <returns>true/false</returns>
	static bool rgb_compare(vector<string> rgb, string r, string g, string b);
	/// <summary>
	/// get colour from RGB
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	static ColourClass return_colour_from_RGB(string r, string g, string b);
	/// <summary>
	/// get colour from RGB
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	static ColourClass colour_from_RGB(string r, string g, string b);
	ConsoleWindow draw_bmp_on_window(ConsoleWindow window, const WCHAR* bmpFile, Vector2 bmpfilepoint, Vector2 point, int windowWidth, int windowHeight, int bmpWidth, int bmpHeight);

	/// <summary>
	/// default test bmp path
	/// </summary>
	/// <returns>"EngineFiles\\TestBitmaps\\testfile2.bmp"</returns>
	char* get_test_bmp_path() { return test_bmp_path; }


	/// <summary>
	/// Get bmp as a colour class array (LEGACY: user get_bmp_as_array instead)
	/// </summary>
	/// <param name="bmpFile"></param>
	/// <param name="bmpWidth"></param>
	/// <param name="bmpHeight"></param>
	/// <returns></returns>
	static vector<ColourClass> get_bmp_as_direct_colour_class_array(const WCHAR* bmpFile, int bmpWidth, int bmpHeight);
	/// <summary>
	/// Get bmp as a colour class array
	/// </summary>
	/// <param name="bmpFile"></param>
	/// <param name="bmpWidth"></param>
	/// <param name="bmpHeight"></param>
	/// <returns></returns>
	static vector<ColourClass> get_bmp_as_array(const WCHAR* bmpFile, int bmpWidth, int bmpHeight);
	/// <summary>
	/// Default chime file path
	/// </summary>
	/// <returns>L"EngineFiles\\Sounds\\electronicchime.wav"</returns>
	LPCWSTR get_electronic_chime_file_path() { return electronic_chime_file_path; }
	/// <summary>
	/// Default Squish file path
	/// </summary>
	/// <returns>L"EngineFiles\\Sounds\\squish.wav"</returns>
	LPCWSTR get_squish_file_path() { return squish_file_path; }

	/// <summary>
	/// Default explosion file path
	/// </summary>
	/// <returns>L"EngineFiles\\Sounds\\explosion.wav"</returns>
	static LPCWSTR get_explosion_file_path() { return explosion_file_path; }

	/// <summary>
	/// Default BLACK RGB
	/// </summary>
	/// <returns>"12","12","12"</returns>
	static vector<string> get_BLACK_RGB() { return BLACK_RGB; }
	/// <summary>
	/// Default BLUE RGB
	/// </summary>
	/// <returns>"0","55","218"</returns>
	static vector<string> get_BLUE_RGB() { return BLUE_RGB; }
	/// <summary>
	/// Default GREEN RGB
	/// </summary>
	/// <returns>"19","161","14"</returns>
	static vector<string> get_GREEN_RGB() { return GREEN_RGB; }
	/// <summary>
	/// Default AQUA RGB
	/// </summary>
	/// <returns>"58","150","221"</returns>
	static vector<string> get_AQUA_RGB() { return AQUA_RGB; }
	/// <summary>
	/// Default RED RGB
	/// </summary>
	/// <returns>"197","15","31"</returns>
	static vector<string> get_RED_RGB() { return RED_RGB; }
	/// <summary>
	/// Default PURPLE RGB
	/// </summary>
	/// <returns>"136","23","152"</returns>
	static vector<string> get_PURPLE_RGB() { return PURPLE_RGB; }
	/// <summary>
	/// Default YELLOW RGB
	/// </summary>
	/// <returns>"193","156","0"</returns>
	static vector<string> get_YELLOW_RGB() { return YELLOW_RGB; }
	/// <summary>
	/// Default WHITE RGB
	/// </summary>
	/// <returns>"204","204","204"</returns>
	static vector<string> get_WHITE_RGB() { return WHITE_RGB; }
	/// <summary>
	/// Default LIGHTGREY RGB
	/// </summary>
	/// <returns>"118","118","118"</returns>
	static vector<string> get_LIGHTGREY_RGB() { return LIGHTGREY_RGB; }
	/// <summary>
	/// Default DARKBLUE RGB
	/// </summary>
	/// <returns>"59","120","255"</returns>
	static vector<string> get_DARKBLUE_RGB() { return DARKBLUE_RGB; }
	/// <summary>
	/// Default BRIGHTGREEN RGB
	/// </summary>
	/// <returns>"22","198","12"</returns>
	static vector<string> get_BRIGHTGREEN_RGB() { return BRIGHTGREEN_RGB; }
	/// <summary>
	/// Default LIGHTBLUE RGB
	/// </summary>
	/// <returns>"97","214","214"</returns>
	static vector<string> get_LIGHTBLUE_RGB() { return LIGHTBLUE_RGB; }
	/// <summary>
	/// Default BRIGHTRED RGB
	/// </summary>
	/// <returns>"231","72","86"</returns>
	static vector<string> get_BRIGHTRED_RGB() { return BRIGHTRED_RGB; }
	/// <summary>
	/// Default LIGHTPURPLE RGB
	/// </summary>
	/// <returns>"180","0","158"</returns>
	static vector<string> get_LIGHTPURPLE_RGB() { return LIGHTPURPLE_RGB; }
	/// <summary>
	/// Default BRIGHTYELLOW RGB
	/// </summary>
	/// <returns>"249","241","165"</returns>
	static vector<string> get_BRIGHTYELLOW_RGB() { return BRIGHTYELLOW_RGB; }
	/// <summary>
	/// Default BRIGHTWHITE RGB
	/// </summary>
	/// <returns>"242","242","242"</returns>
	static vector<string> get_BRIGHTWHITE_RGB() { return BRIGHTWHITE_RGB; }

	/// <summary>
	/// Return the string RGB array for the colour
	/// </summary>
	/// <param name="c"> - Colour To Get Back As String</param>
	/// <returns></returns>
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