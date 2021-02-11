#include "pch.h"
#include "ConsoleWindow3D.h"

ConsoleWindow3D::ConsoleWindow3D(int width, int height)
{

}

ConsoleWindow3D::~ConsoleWindow3D()
{
}

ConsoleWindow ConsoleWindow3D::flattenedWindow()
{
	ConsoleWindow window(windowHeight);
	window.ClearWindow(true);
	for (int l = 0; l < windowHeight; l++)
	{
		for (int m = 0; m < windowWidth; m++)
		{
			window.addToLine(m, " ", NULLCOLOUR);
		}
	}


	for (int i = 0; i < m_WindowLevels.size(); i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			for (int iii = 0; iii < windowWidth; iii++)
			{
				window.setTextAtPoint(Vector2(iii, ii), window.getTextAtPoint(Vector2(iii, ii)), m_WindowLevels[i].window.getTextColourAtPoint(Vector2(iii, ii)));
			}
		}
	}

	return window;
}

void ConsoleWindow3D::writeConsole()
{
	ConsoleWindow window = flattenedWindow();
	Line blank;
	for (int i = 0; i < offset.getY() + _StartingLine; i++)
	{
		blank.writeLine();
	}
	for (int i = _StartingLine; i < windowHeight; i++)
	{
		window.getLine(i).writeLineOptimized(offset.getX());
	}
}

void ConsoleWindow3D::sortLevels()
{
	//TODO, IMPLEMENT SORTING
}

ConsoleLevels* ConsoleWindow3D::operator[](int level)
{
	for (int i = 0; i < m_WindowLevels.size(); i++)
	{
		if (level == m_WindowLevels[i].m_Level)
		{
			return &m_WindowLevels[i];
		}
	}
	m_WindowLevels.push_back(ConsoleLevels(level, windowWidth, windowHeight));
	sortLevels();
	return &m_WindowLevels[level];
}

void ConsoleWindow3D::setTextAtPosition(Vector3 point, string text, ColourClass colour)
{
	if (point.getY() < windowHeight && point.getY() > 0)
	{
		if (point.getX() < windowWidth)
		{
			if (colour != NULLCOLOUR)
			{
				m_WindowLevels[point.getZ()].window.addLayerToLine((int)point.getY(), text, colour, NULL, (int)point.getX());
			}
		}
	}
}

