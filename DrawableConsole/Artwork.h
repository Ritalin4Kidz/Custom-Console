#pragma once
#include "ConsoleWindow.h"
#include "Vector2.h"

/// <summary>
/// Various artwork, done for init
/// </summary>
class Artwork {
public:
	Artwork() {}
	virtual ~Artwork() {}

	/// <summary>
	/// Draw the freebee bee to the window
	/// </summary>
	/// <param name="window"></param>
	/// <param name="baseX"></param>
	/// <param name="baseY"></param>
	/// <returns></returns>
	ConsoleWindow draw_freebee_bee(ConsoleWindow window, int baseX, int baseY);

	/// <summary>
	/// draw the syde engine logo on the window
	/// </summary>
	/// <param name="window"></param>
	/// <param name="baseX"></param>
	/// <param name="baseY"></param>
	/// <returns></returns>
	ConsoleWindow draw_syde_engine_logo(ConsoleWindow window, int baseX, int baseY);

private:
};