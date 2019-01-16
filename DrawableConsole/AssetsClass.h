#pragma once
#include <string>
#include <vector>
using namespace std;
class AssetsClass {
public:
	AssetsClass() {}
	virtual ~AssetsClass() {}

	const int get_file_size(char* filename);
	//THIS NEEDS BETTER WORKING, WORKS TO 20x20
	vector<unsigned char> get_data_from_bmp(char* filename);
	vector<vector<unsigned char>> convert_to_rgb_vector(vector<unsigned char> data);

	bool rgb_match(vector<int> rgb, int r, int g, int b);

	char* get_test_bmp_path() { return test_bmp_path; }
	char* get_electronic_chime_file_path() { return electronic_chime_file_path; }

	vector<int> get_BLACK_RGB() { return BLACK_RGB; }
	vector<int> get_BLUE_RGB() { return BLUE_RGB; }
	vector<int> get_GREEN_RGB() { return GREEN_RGB; }
	vector<int> get_AQUA_RGB() { return AQUA_RGB; }
	vector<int> get_RED_RGB() { return RED_RGB; }
	vector<int> get_PURPLE_RGB() { return PURPLE_RGB; }
	vector<int> get_YELLOW_RGB() { return YELLOW_RGB; }
	vector<int> get_WHITE_RGB() { return WHITE_RGB; }
	vector<int> get_LIGHTGREY_RGB() { return LIGHTGREY_RGB; }
	vector<int> get_DARKBLUE_RGB() { return DARKBLUE_RGB; }
	vector<int> get_BRIGHTGREEN_RGB() { return BRIGHTGREEN_RGB; }
	vector<int> get_LIGHTBLUE_RGB() { return LIGHTBLUE_RGB; }
	vector<int> get_BRIGHTRED_RGB() { return BRIGHTRED_RGB; }
	vector<int> get_LIGHTPURPLE_RGB() { return LIGHTPURPLE_RGB; }
	vector<int> get_BRIGHTYELLOW_RGB() { return BRIGHTYELLOW_RGB; }
	vector<int> get_BRIGHTWHITE_RGB() { return BRIGHTWHITE_RGB; }

private:
	char* electronic_chime_file_path = (char*)"EngineFiles\\electronicchime.wav";
	char* test_bmp_path = (char*)"EngineFiles\\testfile.bmp";


	//BITMAP SETTINGS
	vector<int> BLACK_RGB = { 12,12,12 };
	vector<int> BLUE_RGB = { 0,55,2018 };
	vector<int> GREEN_RGB = { 19,161,14 };
	vector<int> AQUA_RGB = { 58,150,221 };
	vector<int> RED_RGB = { 197,15,31 };
	vector<int> PURPLE_RGB = { 136,23,152 };
	vector<int> YELLOW_RGB = { 193,156,0 };
	vector<int> WHITE_RGB = { 204,204,204 };
	vector<int> LIGHTGREY_RGB = { 118,118,118 };
	vector<int> DARKBLUE_RGB = { 59,120,255 };
	vector<int> BRIGHTGREEN_RGB = { 22,198,12 };
	vector<int> LIGHTBLUE_RGB = { 97,214,214 };
	vector<int> BRIGHTRED_RGB = { 231,72,86 };
	vector<int> LIGHTPURPLE_RGB = { 180,0,158 };
	vector<int> BRIGHTYELLOW_RGB = { 249,241,165 };
	vector<int> BRIGHTWHITE_RGB = { 242,242,242 };
};