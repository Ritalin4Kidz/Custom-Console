#pragma once
#include "ConsoleWindow.h"
#include "SYDELabel.h"
#include "Defaults.h"

class SYDEFPS {
public:
	/// <summary>
	/// Draw fps counter onto the window
	/// </summary>
	/// <param name="w"></param>
	static void draw(ConsoleWindow& w);
	/// <summary>
	/// Set the position of the fps counter
	/// </summary>
	/// <param name="v"></param>
	static void setPos(Vector2 v) { m_fps.setPos(v); }
	/// <summary>
	/// set the colour of the FPS counter
	/// </summary>
	/// <param name="c"></param>
	static void setColour(ColourClass c) { m_fps.setColour(c); }
private:

protected:
	static SYDELabel m_fps;
};