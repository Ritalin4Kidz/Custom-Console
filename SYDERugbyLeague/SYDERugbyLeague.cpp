/*
BASED OFF D6 Game
*/

#include "pch.h"

#include "SRL.h"
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineDemos.h"
#include "SYDEEngineAssets.h"
#include "SYDEMainDemos.h"
#include "SYDESounds.h"

using namespace std;
using namespace Gdiplus;
//INITIALIZING VARIABLES
int windowWidth = 60;
const int windowHeight = 20;
const string dir = "BrainFiles\\";
Settings config("EngineFiles\\Settings\\configSettings.sc");
ConsoleWindow window(windowHeight);
//DRAWING SETTINGS
BackgroundClass bgVars;
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
	bool debug = false;
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	srand(time(NULL));
	LPCWSTR title = L"SYDE Rugby League Simulator";
	SYDECredits::_GAMETITLE = "SYDE Rugby League Simulator";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	SetConsoleTitleW(title);
	//ARGUMENT SETTINGS
	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--Debug")
		{
			debug = true;
		}
	}
	BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_NML);
	config.ColourPalette(hOut);
	Font_Settings_Func::set_up_courier(16);
	SYDEFPS::setAnchor(SLA_Right);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	if (debug)
	{
		SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
		BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_OFF);
	}
	else
	{
		SYDEGamePlay::opening_splashscreens(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	}
	SYDEGamePlay::EnableClicking(hOut);

	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_ESCAPE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_UP));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_DOWN));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('A'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SPACE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('D'));
	//SYDEGamePlay::showFPS(true);
	window.setStartingLine(1);
	SRLGame m_SRL;
	while (true)
	{
		window = SYDEGamePlay::play(&m_SRL, start, hOut, window, windowWidth, windowHeight, deltaTime);
		window = SRLGame::m_GamePlaySoundtrack.playWindow(window);
		window.writeConsoleOptimized();
	}
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
}