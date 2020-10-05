#include "pch.h"
#include "SYDEClock.h"

void SYDEClock_Timer::Tick()
{
	m_TickTime += SYDEDefaults::getDeltaTime();
	if (m_TickTime >= m_Interval)
	{
		m_TickTime -= m_Interval;
		//Do The Function Called Up
		m_Function();
	}
}

ConsoleWindow SYDEClock_Timer::draw_ui(ConsoleWindow window)
{
	ColourClass _TXT = TextColour;
	std::string str = std::to_string(m_TickTime) + "/" + std::to_string(m_Interval);
	for (int i = m_Pos.getX(); i < m_Pos.getX() + str.length(); i++)
	{
		_TXT = window.determineColourAtPoint(Vector2(i, m_Pos.getY()), TextColour, true);
		window.setTextAtPoint(Vector2(i, m_Pos.getY()), str.substr(i - m_Pos.getX(), 1), _TXT);
	}
	Tick();
	return window;
}
