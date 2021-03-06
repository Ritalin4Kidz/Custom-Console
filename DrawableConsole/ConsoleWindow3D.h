#pragma once
#include <vector>
#include <stdlib.h>
#include "Line.h"
#include <string>

#include "Vector2.h"
#include "Vector3.h"
#include "ConsoleWindow.h"

struct ConsoleLevels {
public:
	ConsoleLevels(int lvl, int width, int height) { m_Level = lvl; m_windowHeight = height; m_windowWidth = width; }
	ConsoleWindow window;
	int m_Level;
	int m_windowHeight;
	int m_windowWidth;

	void operator=(ConsoleLevels other);
};

/// <summary>
/// Note: This class is experimental, and it's highly reccomended to use ConsoleWindow for non-experienced users
/// </summary>
class ConsoleWindow3D {
public:
	ConsoleWindow3D(int width, int height);
	virtual ~ConsoleWindow3D();

	ConsoleWindow flattenedWindow();

	/// <summary>
	/// Optimized console write function
	/// </summary>
	void writeConsole();

	void sortLevels();

	ConsoleLevels* operator[](int level);
	ConsoleLevels* get(int level);

	ConsoleWindow* getWindow(int level);

	void setTextAtPosition(Vector3 point, string text, ColourClass colour);

	void setOffset(Vector2 a_offset) { offset.setX(a_offset.getX()); offset.setY(a_offset.getY()); }
	void operator=(ConsoleWindow3D other);

protected:
	std::vector<ConsoleLevels> m_WindowLevels = std::vector<ConsoleLevels>();
private:
	int windowWidth;
	int windowHeight;
	Vector2 offset;
	int _StartingLine = 0;
};