#pragma once
#include "ConsoleWindow.h"

/// <summary>
/// Back when this engine started, i had this idea to build a point and click game inside the console. At this point the engine didn't even have bmp loading, so i attempted with some hardcoded
//	artwork. It's the worst way to go around it but nevertheless it works, plus it was all developed when i was working at a dead end job so it passed the time pretty well
// - Callum/Rit@lin
/// </summary>
class SYDEOldCodeCharacters {
public:
	SYDEOldCodeCharacters() {}
	virtual ~SYDEOldCodeCharacters() {}

	//FIRST APPEARANCE, OPENING CUTSCENE
	ConsoleWindow draw_truck_syde_001(ConsoleWindow window, Vector2 point);
	ConsoleWindow draw_girl_diptio_park(ConsoleWindow window, Vector2 point);

	//FIRST APPEARANCE, BREAK_ROOM_001
	ConsoleWindow draw_player(ConsoleWindow window, Vector2 point, ColourClass Clothes1, ColourClass Clothes2, ColourClass Accessory, ColourClass Skin, string lookAngle, string charName);
	ConsoleWindow draw_player_wireframe(ConsoleWindow window, Vector2 point, ColourClass Clothes1, ColourClass Clothes2, ColourClass Accessory, ColourClass Skin, string lookAngle, string charName);
private:
};