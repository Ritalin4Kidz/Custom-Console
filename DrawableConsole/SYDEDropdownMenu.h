#pragma once
#include <string>
#include <vector>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"

struct SYDEDropdownMenuOption
{
	SYDEDropdownMenuOption() {  }
	string m_Text;
	string m_Tag;
};

class SYDEDropdownMenu : public SYDEUI {
public:
	SYDEDropdownMenu() {  }
	virtual ~SYDEDropdownMenu() {}

	ConsoleWindow draw_ui(ConsoleWindow window) override;


protected:

	ColourClass TextColour = NULLCOLOUR;
	bool isDroppedDown = false;
	vector<SYDEDropdownMenuOption> MenuOptions;
	string m_SelectedOptionStr = "";

};