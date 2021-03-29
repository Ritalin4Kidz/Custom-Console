#include "pch.h"
#include "CustomAsset_Draggable.h"


ConsoleWindow CustomAsset_Draggable::draw_asset(ConsoleWindow window, Vector2 point)
{
	if (isInDraggedState)
	{
		offset = SYDEKeyCode::getMousePosition() - point;
	}
	point += offset;
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			window.setTextAtPoint(Vector2(ii + point.getX(), i + point.getY()), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
		}
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN))
	{
		if (pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition(), point))
		{
			if (!isHoldClickRequired)
				isInDraggedState = !isInDraggedState;
			else
				isInDraggedState = true;
		}
		else if (isInDraggedState && !isHoldClickRequired)
		{
			isInDraggedState = false;
		}
	}
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP) && isHoldClickRequired)
	{
		isInDraggedState = false;
	}
	return window;
}

ConsoleWindow CustomAsset_Draggable::draw_asset(ConsoleWindow window, Vector2 point, int windowWidth, int windowHeight)
{
	if (isInDraggedState)
	{
		offset = SYDEKeyCode::getMousePosition() - point;
	}
	point += offset;
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
	for (int i = startPointY, j = StartJ; i < windowHeight + point.getY() && i < AssetVector.size(); i++, j++)
	{
		for (int ii = startPointX, jj = StartJJ; ii < windowWidth + point.getX() && ii < AssetVector[i].size(); ii++, jj++)
		{
			window.setTextAtPoint(Vector2(jj, j), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
		}
	}

	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN))
	{
		if (pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition(), point))
		{
			if (!isHoldClickRequired)
				isInDraggedState = !isInDraggedState;
			else
				isInDraggedState = true;
		}
		else if (isInDraggedState && !isHoldClickRequired)
		{
			isInDraggedState = false;
		}
	}
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP) && isHoldClickRequired)
	{
		isInDraggedState = false;
	}

	return window;
}

bool CustomAsset_Draggable::pointIsInButtonRange(Vector2 Point, Vector2 m_Pos)
{
	Vector2 bottomRight = Vector2(AssetVector[0].size(), AssetVector.size());
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() && (Point.getX() < m_Pos.getX() + bottomRight.getX()));
	bool withinHeightBoundaries = (Point.getY() >= m_Pos.getY() && (Point.getY() < m_Pos.getY() + bottomRight.getY()));
	return withinHeightBoundaries && withinLengthBoundaries;
}
