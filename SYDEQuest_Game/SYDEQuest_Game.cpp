#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include "SYDEstdafx.h"
#include "SYDEQuestGame.h"
#include <fstream>
#include <istream>
#include <sstream>

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
Artwork artVars;
//OTHER ASSETS
AssetsClass astVars;
//DECLARE CUSTOM ASSETS HERE
COORD start = { (SHORT)0, (SHORT)0 };
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CustomAnimationAsset testAnimation;
//CHEATS
vector<string> cheatCodes;
static ULONG_PTR gdiplusToken;
static GdiplusStartupInput startupInput;

DWORD VOLUME_LOW = DWORD(858993459);
DWORD VOLUME_NML = DWORD(1717986918);
DWORD VOLUME_MED = DWORD(-1717986918);
DWORD VOLUME_HIG = DWORD(-858993459);
DWORD VOLUME_OFF = DWORD(0);

bool _Debug_Window = false;

void volumeControl(int volume) {
	switch (volume)
	{
	case 0:
		waveOutSetVolume(0, VOLUME_OFF);
		break;
	case 1:
		waveOutSetVolume(0, VOLUME_LOW);
		break;
	case 2:
		waveOutSetVolume(0, VOLUME_NML);
		break;
	case 3:
		waveOutSetVolume(0, VOLUME_MED);
		break;
	case 4:
		waveOutSetVolume(0, VOLUME_HIG);
		break;
	default:
		waveOutSetVolume(0, VOLUME_NML);
		volume = 2;
		break;
	}
}


int main(int argc, char* argv[])
{
	//MOTSDefaults::ColourPalette(hOut);
	volumeControl(0);
	//CHEAT CODES
	std::srand(std::time(nullptr));
	LPCWSTR title = L"SYDE Quest";
	SYDECredits::_GAMETITLE = "SYDE Quest";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	//CONSOLE SETTINGS
	//SYDE ENGINE SETTINGS
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	SetConsoleTitleW(title);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	for (int i = 0; i < windowWidth; i++)
	{
		for (int j = 0; j < windowHeight; j++)
		{
			window.setTextAtPoint(Vector2(i, j), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
	}
	bool dev_mode = false;
	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--dev_mode")
		{
			dev_mode = true;
		}
		else if (arg == "--debug_ui")
		{

		}
	}

	//set the animation variables before we create the game
	CustomAnimationAsset::SetDeltatimeBasedAnimation(true);
	CustomAnimationAsset::setStandardMaxFrameTime(0.03f);

	SYDEMapGame m_MapSYDE;
	//KEYS
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('A'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('W'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('S'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('D'));
	//SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('R')); //TETRIS
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_TAB));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SHIFT));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SPACE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('T'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_BACK));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('I'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('M'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('K'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('P'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_F12));

	if (dev_mode)
	{
		SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
		SYDEGamePlay::showFPS(true);
	}
	else
	{
		SYDEGamePlay::opening_splashscreens(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	}
	SYDEGamePlay::EnableClicking(hOut);
	//MAIN GAMEPLAY LOOP
	SYDEScreenshotError e;
	SYDEScreenshot::init();
	SYDELabel m_fps = SYDELabel("", Vector2(34, 1), Vector2(6, 1), BRIGHTGREEN, true);

	while (true)
	{
		window = SYDEGamePlay::play(&m_MapSYDE, start, hOut, window, windowWidth, windowHeight, deltaTime);
		window.writeConsoleOptimized();
		if ((SYDEKeyCode::get_key(VK_F12)._CompareState(KEYDOWN)))
		{
			SYDEScreenshot::Take_Screenshot(window, windowWidth, windowHeight, e);
		}

		//SYDEFunctions::SYDESleep(30, SYDEDefaults::getDeltaTime());
	}
	system("cls");
	return NULL;

}