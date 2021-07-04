/*
BASED OFF D6 Game
*/
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
#include "pch.h"

#include "SRL.h"
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineDemos.h"
#include "SYDEEngineAssets.h"
#include "SYDEMainDemos.h"
#include "SYDESounds.h"
#include "SRLSteamAchievements.h"
#include "steam_api.h"
#include <stdlib.h>
#include <stdio.h>

extern char** environ;

using namespace std;
using namespace Gdiplus;

// Defining our achievements
enum EAchievements
{
	SRL_FIRST_SEASON = 0,
	SRL_HIGH_ROLLER = 1,
	SRL_BANKRUPT = 2,
	SRL_HANGING_ON = 3,
	SRL_NO_DOUBT = 4,
	SRL_PREMIERSHIP_TIP = 5,
	SRL_ALWAYS_DOUBT = 6,
	SRL_SHORT_SEASON = 7,
	SRL_MEDIUM_SEASON = 8,
	SRL_NORMAL_SEASON = 9,
	SRL_LONG_SEASON = 10,
	SRL_EXTREME_SEASON = 11,
	SRL_ENDURANCE_SEASON = 12,
	SRL_GAMBLING_ADDICT = 13,
	SRL_NOT_PROBLEM = 14,
	SRL_BIG_PROBLEM = 15,
	SRL_FORMAT_TEAMS = 16,
	SRL_NEWSPAPER = 17,
	SRL_CONTROVERSY = 18,
	SRL_SPOONBET = 19,
	SRL_BET_CHALLENGE1 = 20,
	SRL_BET_CHALLENGE2 = 21,
	SRL_BET_CHALLENGE3 = 22,
	SRL_BET_CHALLENGE4 = 23,
	SRL_REGEN = 24,
	SRL_BET_NICE = 25,
	SRL_FREEBEE_NETWORK = 26,
	SRL_AUSMUSIC_TEAM = 27,
	SRL_ROUND_ROBIN = 28,
	SRL_MINIMME_COMM = 29
};

// Achievement array which will hold data about the achievements and their state
Achievement_t g_Achievements[] =
{
	_ACH_ID(SRL_FIRST_SEASON, "Simulator Novice"),
	_ACH_ID(SRL_HIGH_ROLLER, "Virtual High Roller"),
	_ACH_ID(SRL_BANKRUPT, "Bankrupt"),
	_ACH_ID(SRL_HANGING_ON, "Not Completely Gone"),
	_ACH_ID(SRL_NO_DOUBT, "Never In Doubt"),
	_ACH_ID(SRL_ALWAYS_DOUBT, "Should Have Been In Doubt"),
	_ACH_ID(SRL_SHORT_SEASON, "Summer Break"),
	_ACH_ID(SRL_MEDIUM_SEASON, "Pandemic Affected"),
	_ACH_ID(SRL_NORMAL_SEASON, "Same Old Same Old"),
	_ACH_ID(SRL_LONG_SEASON, "Making Up For Lost Time"),
	_ACH_ID(SRL_EXTREME_SEASON, "24 Hours 7 Days A Week"),
	_ACH_ID(SRL_ENDURANCE_SEASON, "Cult Of Rugby League"),
	_ACH_ID(SRL_GAMBLING_ADDICT, "Addicted"),
	_ACH_ID(SRL_NOT_PROBLEM, "Not A Problem If I'm Winning"),
	_ACH_ID(SRL_BIG_PROBLEM, "1800-858-858"),
	_ACH_ID(SRL_FORMAT_TEAMS, "Fresh Start"),
	_ACH_ID(SRL_NEWSPAPER, "SYDE Daily"),
	_ACH_ID(SRL_CONTROVERSY, "Bad PR"),
	_ACH_ID(SRL_SPOONBET, "Disappointment"),
	_ACH_ID(SRL_BET_CHALLENGE1, "Master Tipper"),
	_ACH_ID(SRL_BET_CHALLENGE2, "Quit Whilst You're Ahead"),
	_ACH_ID(SRL_BET_CHALLENGE3, "50/50"),
	_ACH_ID(SRL_BET_CHALLENGE4, "Close But No Cigar"),
	_ACH_ID(SRL_REGEN, "Regeneration Powers"),
	_ACH_ID(SRL_BET_NICE, "Nice"),
	_ACH_ID(SRL_FREEBEE_NETWORK, "Freebee Network"),
	_ACH_ID(SRL_AUSMUSIC_TEAM, "AusMusic Community"),
	_ACH_ID(SRL_ROUND_ROBIN, "Enough To Go Around"),
	_ACH_ID(SRL_MINIMME_COMM, "Minimme Community"),
};

// Global access to Achievements object
CSteamAchievements* g_SteamAchievements = NULL;
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


void DoAchievements(vector<string> temp)
{
	for (int i = 0; i < temp.size(); i++)
	{
		if (g_SteamAchievements)
			g_SteamAchievements->SetAchievement(temp[i].c_str());
	}
}

// MAIN FUNCTION
int main(int argc, char* argv[])
{
	//override the config
	//BASE WINDOWS 10
	bool customOffset = false;;
	bool debug = false;	//ARGUMENT SETTINGS
	bool api_init = true;
	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--Debug")
		{
			debug = true;
		}
		if (arg == "--NoOffset")
		{
			config.setOffset(0, 0);
		}
		if (arg == "--CustomOffset")
		{
			customOffset = true;
		}
		if (arg == "--NoInit")
		{
			api_init = false;
		}
	}
	if (!customOffset)
	{
		config.setOffset(2, 0);
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
	bool fmodInit = SRLGame::m_GamePlaySoundtrack.init();
	if (!fmodInit)
	{
		return 0;
	}
	// Initialize Steam
	if (api_init)
	{
		bool bRet = SteamAPI_Init();
		// Create the SteamAchievements object if Steam was successfully initialized
		if (bRet)
		{
			cout << "Steam API Initialization Successful" << endl;
			g_SteamAchievements = new CSteamAchievements(g_Achievements, 30);
		}
		else
		{
			cout << "Steam API Initialization Was Not Successful" << endl;
		}
	}
	system("pause");
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	srand(time(NULL));
	LPCWSTR title = L"SYDE Rugby League Simulator";
	SYDECredits::_GAMETITLE = "SYDE Rugby League Simulator";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	SYDECredits::_OTHERCREDITS = "Made with FMOD Studio by Firelight Technologies Pty Ltd.";
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
	}
	else
	{
		//CustomAsset m_FmodSplash = CustomAsset(60, 20, astVars.get_bmp_as_array(L"EngineFiles\\Bitmaps\\fmodlogo.bmp", 30, 20));
		SYDEGamePlay::opening_splashscreens(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
		//SYDEGamePlay::customSplashscreen(window,windowWidth, windowHeight, m_FmodSplash);
	}
	SYDEGamePlay::EnableClicking(hOut);

	//SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_ESCAPE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_UP));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_DOWN));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_LEFT));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_RIGHT));
	//SYDEGamePlay::showFPS(true);
	window.setStartingLine(1);
	try {
		SRLGame m_SRL;
		while (!SRLGame::exitConfirmedCall)
		{
			window = SYDEGamePlay::play(&m_SRL, start, hOut, window, windowWidth, windowHeight, deltaTime);
			SteamAPI_RunCallbacks();
			window = SRLGame::m_GamePlaySoundtrack.playWindow(window);
			window.writeConsoleOptimized();
			DoAchievements(SRLGame::AchievementStrings);
			SRLGame::AchievementStrings.clear();
		}
	}
	catch (exception e)
	{

	}
	EnableMenuItem(hmenu, SC_CLOSE, MF_ENABLED);
	SRLGame::m_GamePlaySoundtrack.shutdown();
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
	// Shutdown Steam
	SteamAPI_Shutdown();
	// Delete the SteamAchievements object
	if (g_SteamAchievements)
		delete g_SteamAchievements;
}