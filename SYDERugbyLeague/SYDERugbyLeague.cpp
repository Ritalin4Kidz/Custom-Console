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
	// Initialize Steam
	bool bRet = SteamAPI_Init();
	// Create the SteamAchievements object if Steam was successfully initialized
	if (bRet)
	{
		g_SteamAchievements = new CSteamAchievements(g_Achievements, 4);
	}



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
	while (!SRLGame::exitConfirmedCall)
	{
		window = SYDEGamePlay::play(&m_SRL, start, hOut, window, windowWidth, windowHeight, deltaTime);
		SteamAPI_RunCallbacks();
		window = SRLGame::m_GamePlaySoundtrack.playWindow(window);
		window.writeConsoleOptimized();
		DoAchievements(SRLGame::AchievementStrings);
		SRLGame::AchievementStrings.clear();
	}
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