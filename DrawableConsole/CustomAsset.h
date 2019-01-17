#pragma once
#include <vector>
#include "ConsoleWindow.h"

using namespace std;

class CustomAsset {
public:
	CustomAsset() {}
	virtual ~CustomAsset() {}

	ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point);
	void setAsset(int width, int height, vector<ColourClass> colourClassArray);

private:

	vector<vector<TextItem>> AssetVector;
};