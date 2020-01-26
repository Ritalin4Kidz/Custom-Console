#include "pch.h"
#include "CustomAsset.h"

void CustomAsset::operator=(CustomAsset other)
{
	this->AssetVector = other.AssetVector;
}

ConsoleWindow CustomAsset::draw_asset(ConsoleWindow window, Vector2 point)
{
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			window.setTextAtPoint(Vector2(ii + point.getX(), i + point.getY()), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
		}
	}
	return window;
}

ConsoleWindow CustomAsset::draw_asset(ConsoleWindow window, Vector2 point, int windowWidth, int windowHeight)
{
	int startPointY = point.getY();
	int startPointX = point.getX();
	int StartJ = 0;
	int StartJJ = 0;
	if (startPointY < 0)
	{
		StartJ = -startPointY;
		startPointY = 0;
	}
	if (startPointX < 0)
	{
		StartJJ = -startPointX;
		startPointX = 0;
	}
	for (int i = startPointY, j  = StartJ ; i < windowHeight + point.getY() && i < AssetVector.size(); i++, j++)
	{
		for (int ii = startPointX, jj = StartJJ; ii < windowWidth + point.getX() && ii < AssetVector[i].size(); ii++, jj++)
		{
			window.setTextAtPoint(Vector2(jj, j), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
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

void CustomAsset::setCharAtPoint(Vector2 Point, char m_Text)
{
	AssetVector[Point.getY()][Point.getX()].setChar(m_Text);
}

void CustomAsset::setColourAtPoint(Vector2 Point, int m_Colour)
{
	AssetVector[Point.getY()][Point.getX()].setColour(m_Colour);
}

char CustomAsset::getCharAtPoint(Vector2 Point)
{
	return AssetVector[Point.getY()][Point.getX()].getChar();
}

int CustomAsset::getColourAtPoint(Vector2 Point)
{
	return AssetVector[Point.getY()][Point.getX()].getColour();
}
