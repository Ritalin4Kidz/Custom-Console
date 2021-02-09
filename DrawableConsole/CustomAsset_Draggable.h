#pragma once
#include <vector>
#include "ConsoleWindow.h"
#include "CustomAsset.h"
#include "SYDEKeyCode.h"
using namespace std;
class CustomAsset_Draggable : public CustomAsset {
public:
	CustomAsset_Draggable() {}
	CustomAsset_Draggable(int width, int height, vector<ColourClass> colour_array) { setAsset(width, height, colour_array); }

	virtual ~CustomAsset_Draggable() {}


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

	bool getIsInDraggedState() { return isInDraggedState; }

	void setIsHoldClickRequired(bool state) { isHoldClickRequired = state; }
	bool getIsHoldClickRequired() { return isHoldClickRequired; }

protected:
	bool isInDraggedState = false;
	void setIsInDraggedState(bool state) { isInDraggedState = state; }
	bool isHoldClickRequired = false;

	Vector2 offset = Vector2(0);

private:
	bool pointIsInButtonRange(Vector2 Point, Vector2 m_Pos);
};