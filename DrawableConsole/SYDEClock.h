#pragma once

#include "Defaults.h"
#include "ConsoleWindow.h"
class SYDEClock_Timer {
public:
	SYDEClock_Timer(float interval) { m_Interval = interval; }
	virtual ~SYDEClock_Timer() {}

	/// <summary>
	/// Tick function, call every fram clock is in use
	/// </summary>
	void Tick();

	/// <summary>
	/// Set the main function for the button
	/// </summary>
	/// <param name="f"></param>
	void SetFunc(void(*f)()) { m_Function = f; }
	/// <summary>
	/// Draw the ui on screen (Note, uses tick func)
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window);
	void SetPos(Vector2 p) { m_Pos = p; }
	void SetColour(ColourClass c) { TextColour = c; }

private:
	Vector2 m_Pos = Vector2(0, 0);
	ColourClass TextColour = WHITE;
protected:
	float m_Interval;
	float m_TickTime = 0;
	void(*m_Function)();
};