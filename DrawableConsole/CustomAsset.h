#pragma once
#include <vector>
#include "ConsoleWindow.h"

using namespace std;

class CustomAsset {
public:
	CustomAsset() {}
	CustomAsset(int width, int height, vector<ColourClass> colour_array) { setAsset(width, height, colour_array); }


	virtual ~CustomAsset() {}

	void operator=(CustomAsset other);
	/// <summary>
	/// Draw the asset onto the window at a point
	/// </summary>
	/// <param name="window"></param>
	/// <param name="point"></param>
	/// <returns></returns>
	virtual ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point);
	/// <summary>
	/// draw the asset onto the window, with a max window size
	/// </summary>
	/// <param name="window"></param>
	/// <param name="point"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <returns></returns>
	virtual ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point,int windowWidth, int windowHeight);
	/// <summary>
	/// Set the asset
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="colourClassArray"></param>
	void setAsset(int width, int height, vector<ColourClass> colourClassArray);
	/// <summary>
	/// set the asset
	/// </summary>
	/// <param name="asset"></param>
	void setAsset(vector<vector<TextItem>> asset) { AssetVector = asset; }
	/// <summary>
	/// clear the asset
	/// </summary>
	void ClearAsset() { for (int i = 0; i < AssetVector.size(); i++) AssetVector[i].clear(); AssetVector.clear(); }
	/// <summary>
	/// add the asset onto another
	/// </summary>
	/// <param name="other"></param>
	/// <param name="point"></param>
	void AddAssetOnto(CustomAsset other, Vector2 point);

	/// <summary>
	/// change a specific point of the asset (char)
	/// </summary>
	/// <param name="Point"></param>
	/// <param name="m_Text"></param>
	void setCharAtPoint(Vector2 Point, char m_Text);
	/// <summary>
	/// change a specific point of the asset (colour)
	/// </summary>
	/// <param name="Point"></param>
	/// <param name="m_Text"></param>
	void setColourAtPoint(Vector2 Point, int m_Colour);

	/// <summary>
	/// change all the instances of a colour
	/// </summary>
	/// <param name="oldColour"></param>
	/// <param name="newColour"></param>
	void changeAllInstancesOfColour(ColourClass oldColour, ColourClass newColour);

	/// <summary>
	/// return the character at a certain point in the asset
	/// </summary>
	/// <param name="Point"></param>
	/// <returns></returns>
	char getCharAtPoint(Vector2 Point);
	/// <summary>
	/// return the colour at a certain point in the asset
	/// </summary>
	/// <param name="Point"></param>
	/// <returns></returns>
	int getColourAtPoint(Vector2 Point);

	/// <summary>
	/// return the point where the colour is first displayed on the asset
	/// </summary>
	/// <param name="a_Colour">colour to find</param>
	/// <returns></returns>
	Vector2 returnPointOfFirstInstance(ColourClass a_Colour);
protected:
	vector<vector<TextItem>> AssetVector;
	string getStringFromChar(char x) { return string(1, x); }
};