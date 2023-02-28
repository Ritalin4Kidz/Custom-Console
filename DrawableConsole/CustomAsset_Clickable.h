#pragma once
#include <vector>
#include "ConsoleWindow.h"
#include "CustomAsset.h"
#include "SYDEKeyCode.h"
using namespace std;
class CustomAsset_Clickable : public CustomAsset {
public:
	CustomAsset_Clickable() {}
	CustomAsset_Clickable(int width, int height, vector<ColourClass> colour_array) { setAsset(width, height, colour_array); }
	CustomAsset_Clickable(int width, int height, vector<ColourClass> colour_array, void(*f)()) { setAsset(width, height, colour_array); m_Function = f;}
	CustomAsset_Clickable(int width, int height, vector<ColourClass> colour_array, void(*f)(), string a_Tag) { setAsset(width, height, colour_array); m_Function = f; tag = a_Tag; }


	/// <summary>
	/// Draw the asset onto the window at a point
	/// </summary>
	/// <param name="window"></param>
	/// <param name="point"></param>
	/// <returns></returns>
	ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point) override;
	/// <summary>
	/// draw the asset onto the window, with a max window size
	/// </summary>
	/// <param name="window"></param>
	/// <param name="point"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <returns></returns>
	ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point, int windowWidth, int windowHeight) override;

	/// <summary>
	/// Set the main function for the button
	/// </summary>
	/// <param name="f"></param>
	void SetFunc(void(*f)()) { m_Function = f; }
	void setTag(string newTag) { tag = newTag; }
	string getTag() { return tag; }
	void ForceHighlight() { highlighted = true; }
	void setHilightColour(ColourClass c) { hilightColour = c; canHighlight = true; }
	void clearHighlight() { highlighted = false; }
	static string getLastButtonTag() { return lastTag; }
	bool allowNullClick(bool isOn) { allowNullColourClick = isOn; }
private:
	static string lastTag;
	string tag = "";
protected:
	/// <summary>
	/// Execute the main button function
	/// </summary>
	void DoFunc() { m_Function(); }
private:
	void(*m_Function)();
	bool pointIsInButtonRange(Vector2 Point, Vector2 m_Pos);
	bool canClick = true;
	bool canHighlight = false;
	bool highlighted = false;
	bool allowNullColourClick = false;
	ColourClass hilightColour;
};