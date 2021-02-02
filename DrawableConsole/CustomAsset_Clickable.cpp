#include "pch.h"
#include "CustomAsset_Clickable.h"


ConsoleWindow CustomAsset_Clickable::draw_asset(ConsoleWindow window, Vector2 point)
{
	for (int i = 0; i < AssetVector.size(); i++)
	{
		for (int ii = 0; ii < AssetVector[i].size(); ii++)
		{
			window.setTextAtPoint(Vector2(ii + point.getX(), i + point.getY()), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
		}
	}

	if (SYDEKeyCode::LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition(), point))
	{
		DoFunc();
	}

	return window;
}

ConsoleWindow CustomAsset_Clickable::draw_asset(ConsoleWindow window, Vector2 point, int windowWidth, int windowHeight)
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
	for (int i = startPointY, j = StartJ; i < windowHeight + point.getY() && i < AssetVector.size(); i++, j++)
	{
		for (int ii = startPointX, jj = StartJJ; ii < windowWidth + point.getX() && ii < AssetVector[i].size(); ii++, jj++)
		{
			window.setTextAtPoint(Vector2(jj, j), getStringFromChar(AssetVector[i][ii].getChar()), window._intToColour(AssetVector[i][ii].getColour()));
		}
	}

	if (SYDEKeyCode::LEFT_CLICK_MOUSE._CompareState(KEYDOWN) && pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition(), point))
	{
		DoFunc();
	}

	return window;
}

bool CustomAsset_Clickable::pointIsInButtonRange(Vector2 Point, Vector2 m_Pos)
{
	Vector2 bottomRight = Vector2(AssetVector[0].size(), AssetVector.size());
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() && (Point.getX() < m_Pos.getX() + bottomRight.getX()));
	bool withinHeightBoundaries = (Point.getY() >= m_Pos.getY() && (Point.getY() < m_Pos.getY() + bottomRight.getY()));
	return withinHeightBoundaries && withinLengthBoundaries;
}
