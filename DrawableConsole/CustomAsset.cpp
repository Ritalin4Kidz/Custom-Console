#include "pch.h"
#include "CustomAsset.h"

ConsoleWindow CustomAsset::draw_asset(ConsoleWindow window, Vector2 point)
{
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			window.setTextAtPoint(Vector2(ii + point.getX(), i + point.getY()), " ", window._intToColour(AssetVector[i][ii].getColour()));
		}
	}
	return window;
}

void CustomAsset::setAsset(int width, int height, vector<ColourClass> colourClassArray)
{
	int j = 0;
	vector<vector<TextItem>> temp_temp;
	for (int i = 0; i < height; i++)
	{
		vector<TextItem> temp;
		for (int ii = 0; ii < width; ii++)
		{
			temp.push_back(TextItem(' ', colourClassArray[j]));
			j++;
		}
		temp_temp.push_back(temp);
	}
	AssetVector = temp_temp;
}
