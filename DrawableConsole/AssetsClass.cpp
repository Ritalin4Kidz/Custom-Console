#include "pch.h"
#include <vector>
#include "AssetsClass.h"

using namespace std;

const int AssetsClass::get_file_size(char * filename)
{
	FILE* f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	fclose(f);
	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	const int size = 3 * width * height;
	return size;
}

vector<unsigned char> AssetsClass::get_data_from_bmp(char * filename)
{
	int i;
	FILE* f = fopen(filename, "rb");
	unsigned char data[1200]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), 1200, f); // read the rest of the data at once
	vector<unsigned char> newdata;
	fclose(f);
	for (i = 0; i < 1200; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}
	for (int ii = 0; ii < 1200; ii++)
	{
		newdata.push_back(data[ii]);
	}
	return newdata;
}

vector<vector<unsigned char>> AssetsClass::convert_to_rgb_vector(vector<unsigned char> data)
{
	vector<vector<unsigned char>> newData;
	for (int i = 0; i < 1200; i += 3)
	{
		newData.push_back(vector<unsigned char>{data[i], data[i + 1], data[i + 2]});
	}
	return newData;
}

bool AssetsClass::rgb_match(vector<int> rgb, int r, int g, int b)
{
	return r == rgb[0] && g == rgb[1] && b == rgb[2] ;
}
