#include "pch.h"
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineDemos.h"
#include "SYDEEngineAssets.h"
#include "SYDEMainDemos.h"
#include "SYDESounds.h"
#include "SydeRogueLikeMainControl.h"
#include <stdlib.h>
#include <stdio.h>

extern char** environ;

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
	//override the config
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	bool debug = false;	//ARGUMENT SETTINGS
	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--Debug")
		{
			debug = true;
		}
	}


	for (char** current = environ; *current; current++) {
		puts(*current);
		cout << *current << endl;
	}
	SYDEGamePlay::setConfig(config);
	SYDEGamePlay::getConfig().ColourPalette(hOut);
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	srand(time(NULL));
	LPCWSTR title = L"SYDE Roguelike";
	SYDECredits::_GAMETITLE = "SYDE Roguelike";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	SYDECredits::_OTHERCREDITS = "";
	SetConsoleTitleW(title);
	BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_NML);
	Font_Settings_Func::set_up_courier(16);
	SYDEFPS::setAnchor(SLA_Right);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	if (debug)
	{
		SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
		BaseSYDESoundSettings::changeDefaultVolume(SYDE_VOLUME_OFF);
		SYDEGamePlay::showFPS(true);
		SYDEGamePlay::set_FPS_Position(Vector2(54, 1));
	}
	else
	{
		//CustomAsset m_FmodSplash = CustomAsset(60, 20, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\fmodlogo.bmp", 30, 20));
		SYDEGamePlay::opening_splashscreens(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
		//SYDEGamePlay::customSplashscreen(window,windowWidth, windowHeight, m_FmodSplash);
	}
	SYDEGamePlay::EnableClicking(hOut);

	//SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_ESCAPE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('W'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('A'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('S'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('D'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SPACE));

	CustomAnimationAsset::SetDeltatimeBasedAnimation(true);
	CustomAnimationAsset::setStandardMaxFrameTime(0.03f);

	window.setStartingLine(1);
	SYDERogueLikeMainControl m_MainControl;
	while (true)
	{
		window = SYDEGamePlay::play(&m_MainControl, start, hOut, window, windowWidth, windowHeight, deltaTime);
		window.writeConsoleOptimized();
	}
	EnableMenuItem(hmenu, SC_CLOSE, MF_ENABLED);
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
}