#pragma once

#include "Defaults.h"
#include "ConsoleWindow.h"

enum SYDEClock_Draw_State
{
	Percentage,
	TimeTicked_OutOf_IntervalTime,
	TimeTicked
};

class SYDEClock_Timer {
public:
	SYDEClock_Timer(float interval) { m_Interval = interval; }
	virtual ~SYDEClock_Timer() { if (m_Function != NULL) delete& m_Function; }

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

	void TogglePause() { m_Paused = !m_Paused; }
	void setPaused(bool b) { m_Paused = b; }
	bool getPaused() { return m_Paused; }

	/// <summary>
	/// Set the draw state of the timer (e.g. percentage)
	/// </summary>
	/// <param name="s"></param>
	void setState(SYDEClock_Draw_State s) { _state = s; }

	void setValueLength(int i) { max_value_length = i; }

	void setStopOnTick(bool b) { stop_on_tick = b; }
private:
	Vector2 m_Pos = Vector2(0, 0);
	ColourClass TextColour = WHITE;
	bool m_Paused = false;
	SYDEClock_Draw_State _state = TimeTicked_OutOf_IntervalTime;
	int max_value_length = 2;


	bool stop_on_tick = false;
protected:
	float m_Interval;
	float m_TickTime = 0;
	void(*m_Function)();
};