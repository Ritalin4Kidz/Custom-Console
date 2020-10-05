#include "pch.h"
#include "SYDEFPS.h"
SYDELabel SYDEFPS::m_fps = SYDELabel("", Vector2(35, 1), Vector2(5, 1), BRIGHTGREEN, true);
void SYDEFPS::draw(ConsoleWindow& w)
{
	float fps = 1.0f / SYDEDefaults::getDeltaTime();
	m_fps.setText(std::to_string((int)fps) + "fps");
	w = m_fps.draw_ui(w);
}
