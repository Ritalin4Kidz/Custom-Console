// SYDEEngine_ApplicationDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// CODE BY CALLUM HANDS
// ritalin4kidz.github.io
// callum@hands.net.au
#include "pch.h"
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
	Concerto m_Concerto;
	std::string GameState = "";
	//ARGUMENT SETTINGS
	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "concerto")
		{
			LPCWSTR title = L"Concerto";
			SYDECredits::_GAMETITLE = "Concerto";
			SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
			SetConsoleTitleW(title);
			GameState = "Concerto";
			break;
		}
	}
	//while (true) { //deltaTime test, comment out
	//	deltaTime.refreshTime();
	//	SYDEDefaults::setDeltaTime(deltaTime.getDeltaTime());
	//	cout << to_string(SYDEDefaults::getDeltaTime()) << endl;
	//	Sleep(200);
	//}
	//set_up_window_properties();
	////NECCESARY ON STARTUP
	////CENTER THE WINDOW
	//window.setOffset(config.getOffset());
	//Font_Settings_Func::set_up_consola(16);
	//Font_Settings_Func::set_up_consolas(16);
	//Font_Settings_Func::set_up_consolas(32);
	//Font_Settings_Func::set_up_arial(16);
	//INIT CUSTOMASSETS
	//SYDEMainDemos demos;
	//demos.set_up_custom_assets();
	//set_up_shape_test();
	//INITIALIZE CHEAT VALUES
	//cheatCodes = config.ReturnCheats();
	//for (int i = 0; i < cheatCodes.size(); i++)
	//{
	//	if (cheatCodes[i] == "JumpAllowed")
	//	{
	//		Cheat_CanJump = true;
	//	}
	//	else if (cheatCodes[i] == "Wireframe")
	//	{
	//		Cheat_Wireframe = true;
	//	}
	//}
	config.volumeControl(0);
	config.ColourPalette(hOut);
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	srand(time(NULL));
	Font_Settings_Func::set_up_courier(16);
	SYDEFPS::setAnchor(SLA_Right);

	//Concerto
	//DinseyPlanes m_Planes(astVars);
	//opening();
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	//SYDEGamePlay::opening_splashscreens(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	//SYDEGamePlay::hidden_splashsceen_001(astVars.get_squish_file_path(), start, hOut, window, windowWidth, windowHeight, astVars);
	//SYDEGamePlay::showFPS(true);
	SYDEGamePlay::EnableClicking(hOut);

	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('Q'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('E'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('W'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('S'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('A'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SPACE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('D'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('B'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('M'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_TAB));

	SYDEGamePlay::showFPS(true);

	window.setStartingLine(1);
	while (true)
	{
		if (GameState == "Concerto")
		{
			window = SYDEGamePlay::play(&m_Concerto, start, hOut, window, windowWidth, windowHeight, deltaTime);
		}
		else 
		{
			break;
		}
		//SYDEFunctions::SYDESleep(50, SYDEDefaults::getDeltaTime());
		window.writeConsoleOptimized();
	}
	//END CONCERTO

	//REInvent The Wheel
	/*GAME_RTW m_ReinventTheWheel;
	LPCWSTR title = L"Re-Invent The Wheel";
	SetConsoleTitleW(title);
	opening();
	while (true)
	{
		CONSOLE_CURSOR_INFO cInfo;
		GetConsoleCursorInfo(hOut, &cInfo);
		cInfo.bVisible = false;
		SetConsoleCursorInfo(hOut, &cInfo);
		cout.flush();
		SetConsoleCursorPosition(hOut, start);
		window = m_ReinventTheWheel.window_draw_game(window, windowWidth, windowHeight);
		window.writeConsole();
		Sleep(30);
	}*/
	// END REINVENT THE WHEEL

	//Sprite_Sheet_Test();
	//animation_test_player();
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
	//bmp_test2(fieldTestBmp);
	//play_syde();
	/* REGION ENGINE TESTS
	//MAKE A SEPERATE WINDOW
	//generateart();
	//scenes();
	//generateTriangle();
	//Test();
	//PlayLevel(levelBonus);
	//// WATERMELON
	//PixelArt(GREEN_GREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, RED_RED_BG, BRIGHTRED_BRIGHTRED_BG, BLACK, WHITE);
	//system("pause");
	////Next Level, ETC
	//PlayLevel(levelBonus);
	// select fruit based off level
	//BOW BASED OFF WATERMELON
	//PixelArt(BLACK, BLACK, YELLOW_YELLOW_BG, BLACK, BRIGHTWHITE_BRIGHTWHITE_BG, WHITE);
	//Jump Simulation
	//outputVar();
	//playTicTacToe();
	//window.ClearWindow(false);
	//drawBrain(dir + "AIBrainO.txt");
	//while (!foundPath)
	//{
	//	nodePath();
	//	generations++;
	//}
	//window.setLine(10, "Attempts Required For Path : " + to_string(generations), WHITE);
	//window.ClearWindow(false);
	//window.writeConsole();
	*/
	//system("pause");
}
