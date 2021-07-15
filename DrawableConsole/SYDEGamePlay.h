#pragma once
#include "SYDEWindowGame.h"
#include "ConsoleWindow.h"
#include "ConsoleWindow3D.h"
#include "SYDETime.h"
#include <windows.h>
#include <iostream>
#include <string>
#include "Artwork.h"
#include "AssetsClass.h"
#include "CustomAnimationAsset.h"
#include "SYDEScreenshot.h"
#include "CustomAsset.h"
#include "Activation.h"
#include "SYDECredits.h"
#include "Settings.h"
#include <vector>
#include <gdiplus.h>
#include "SYDEFPS.h"
#include "SYDETime.h"
#include "Defaults.h"
#include "SYDEKeyCode.h"
using namespace std;
using namespace Gdiplus;
class SYDEGamePlay {
public:

	static void setConfig(Settings _Config) { config = _Config; }
	static Settings getConfig() { return config; }
	/// <summary>
	/// Initialize window to the size windows class created with
	/// </summary>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	static void initialize_window(const HANDLE hOut, ConsoleWindow& window);
	/// <summary>
	/// Add FPS counter to main play function call
	/// </summary>
	/// <param name="b"></param>
	static void showFPS(bool b) { FPS_Counter = b; }
	
	/// <summary>
	/// Change if scrollbar is removed on window init
	/// </summary>
	/// <param name="remove"></param>
	static void Remove_Scrollbar_On_Init(bool remove) { remove_scrollbar = remove; }

	/// <summary>
	/// Change if the window is resized on window init
	/// </summary>
	/// <param name="resize"></param>
	static void Resize_Window_On_Init(bool resize) { resize_window_on_init = resize; }

	/// <summary>
	/// Opening splashscreens (optional for starting up the program)
	/// </summary>
	/// <param name="chimePath"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="artVars"></param>
	static void opening_splashscreens(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);
	/// <summary>
	/// quick startup, splashscreens required for play_game function
	/// </summary>
	/// <param name="chimePath"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="artVars"></param>
	static void activate_bySplashscreen(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);


	static void customSplashscreen(ConsoleWindow& window, int windowWidth, int windowHeight, CustomAsset splashscreen);

	static void hidden_splashsceen_001(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, AssetsClass astVars);
	/// <summary>
	/// reset the window to initialize settings, useful if window starts to mess up
	/// </summary>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	static void reset_void(COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight);
	/// <summary>
	/// OLDER VERSION OF THE PLAY_GAME LOOP FUNCTION
	/// AS OF 5/10/2020 THIS FUNCTION IS LEFT IN FOR LEGACY
	/// </summary>
	/// <param name="SYDE_GAME"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="deltaTime"></param>
	/// <returns></returns>
	static ConsoleWindow play_game(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight, SYDETIME& deltaTime);
	/// <summary>
	/// Core game loop for running SYDEWindow games
	/// </summary>
	/// <param name="SYDE_GAME"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="deltaTime"></param>
	/// <returns></returns>
	static ConsoleWindow play(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight, SYDETIME& deltaTime);

	/// <summary>
	/// Set the position of the FPS display
	/// </summary>
	/// <param name="position"></param>
	static void set_FPS_Position(Vector2 position) {
		SYDEFPS::setPos(position);
	}

	/// <summary>
	/// Core game loop for running SYDEWindow games
	/// </summary>
	/// <param name="SYDE_GAME"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="deltaTime"></param>
	/// <returns></returns>
	static ConsoleWindow3D play3D(SYDEWindowGame3D* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow3D window, int windowWidth, int windowHeight, SYDETIME& deltaTime);

	/// <summary>
	/// Enable clicking and getting mouse position
	/// </summary>
	/// <param name="hOut"></param>
	static void EnableClicking(HANDLE hOut);

	/// <summary>
	/// disable clicking
	/// </summary>
	/// <param name="hOut"></param>
	static void DisableClicking(HANDLE hOut);

	/// <summary>
	/// get the last point clicked
	/// </summary>
	/// <returns></returns>
	static Vector2 GetPointClicked() { return LastPointClicked; }

	/// <summary>
	/// shutdown gdiplus
	/// </summary>
	static void exit() {
		GdiplusShutdown(gdiplusToken);
	}
private:
	/// <summary>
	/// Introduction Script Void
	/// </summary>
	static void _introductionScript();
	/// <summary>
	/// Display introduction credits on the window
	/// </summary>
	/// <param name="window"></param>
	static void _introCreditsScript(ConsoleWindow& window);
	/// <summary>
	/// freebee bee
	/// </summary>
	/// <param name="baseY"></param>
	/// <param name="baseX"></param>
	/// <param name="setUp"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="artVars"></param>
	static void _drawBee(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);
	/// <summary>
	/// SYDE Engine splashscreen
	/// </summary>
	/// <param name="baseY"></param>
	/// <param name="baseX"></param>
	/// <param name="setUp"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="artVars"></param>
	static void _poweredBySYDEEngine(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);

	static bool _activated;
	static bool FPS_Counter;

	static string _returnRandomNonsense();
	static Settings config;

	//ClickValues
	static Vector2 LastPointClicked;
	static bool ClickEnabled;
	static INPUT_RECORD InputRecord;
	static DWORD Events;
	static COORD coord;
	static CONSOLE_CURSOR_INFO cci;
	static HANDLE hin;
	static DWORD prev_mode;
	static void SYDE_MouseClickFunction();

	//cheats
	static vector<string> cheatCodes;

	//GDI VALUES
	static ULONG_PTR gdiplusToken;
	static GdiplusStartupInput startupInput;

	//OTHER SETTINGS
	static bool resize_window_on_init;
	static bool remove_scrollbar;
};