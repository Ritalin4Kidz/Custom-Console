#include "pch.h"
#include "SYDEClock.h"

void SYDEClock_Timer::Tick()
{
	if (m_Paused) return;


	m_TickTime += SYDEDefaults::getDeltaTime();
	if (m_TickTime >= m_Interval)
	{
		m_TickTime -= m_Interval;
		//Do The Function Called Up
		m_Function();
		if (stop_on_tick)
			m_Paused = true;
	}
}

ConsoleWindow SYDEClock_Timer::draw_ui(ConsoleWindow window)
{
	ColourClass _TXT = TextColour;
	std::string str = "";
	switch (_state)
	{
	case Percentage:
		str = std::to_string((m_TickTime / m_Interval) * 100).substr(0,max_value_length) + "%";
		break;
	case TimeTicked_OutOf_IntervalTime:
		str = std::to_string(m_TickTime).substr(0, max_value_length) + "/" + std::to_string(m_Interval).substr(0, max_value_length);
		break;
	case TimeTicked:
		str = std::to_string(m_TickTime).substr(0, max_value_length) + "s";
		break;
	}
	for (int i = m_Pos.getX(); i < m_Pos.getX() + str.length(); i++)
	{
		_TXT = window.determineColourAtPoint(Vector2(i, m_Pos.getY()), TextColour, true);
		window.setTextAtPoint(Vector2(i, m_Pos.getY()), str.substr(i - m_Pos.getX(), 1), _TXT);
	}
	Tick();
	return window;
}
