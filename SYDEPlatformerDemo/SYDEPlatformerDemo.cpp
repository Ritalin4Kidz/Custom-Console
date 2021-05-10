#include "pch.h"

#include "SYDEPlatformer.h"
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineDemos.h"
#include "SYDEEngineAssets.h"
#include "SYDEMainDemos.h"

using namespace std;
using namespace Gdiplus;
//INITIALIZING VARIABLES
int windowWidth = 40;
const int windowHeight = 20;
const string dir = "BrainFiles\\";
Settings config("EngineFiles\\Settings\\configSettings.sc");
ConsoleWindow window(windowHeight);
//DRAWING SETTINGS
BackgroundClass bgVars;
Characters charVars;
Artwork artVars;
//OTHER ASSETS
AssetsClass astVars;
//CHEATS
vector<string> cheatCodes;
//GDI VALUES
ULONG_PTR gdiplusToken;
GdiplusStartupInput startupInput;
//OTHER VALUES

//GAME VALUES
COORD start = { (SHORT)0, (SHORT)0 };
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

// MAIN FUNCTION
int main(int argc, char* argv[])
{
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	SYDEPlatformer m_Platformer;
	LPCWSTR title = L"SYDE";
	SYDECredits::_GAMETITLE = "SYDE";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	SetConsoleTitleW(title);
	//ARGUMENT SETTINGS
	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
	}
	config.volumeControl(0);
	config.ColourPalette(hOut);
	srand(time(NULL));
	Font_Settings_Func::set_up_courier(16);
	SYDEFPS::setAnchor(SLA_Right);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	SYDEGamePlay::EnableClicking(hOut);

	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('Q'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('E'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('W'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('S'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('A'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SPACE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('D'));

	SYDEGamePlay::showFPS(true);

	window.setStartingLine(1);
	while (true)
	{
		window = SYDEGamePlay::play(&m_Platformer, start, hOut, window, windowWidth, windowHeight, deltaTime);
		window.writeConsoleOptimized();
	}
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
}
