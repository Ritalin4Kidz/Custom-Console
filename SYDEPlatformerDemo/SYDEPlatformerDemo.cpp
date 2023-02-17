#include "pch.h"

#include "SYDEPlatformer.h"
#include "SYDEPlatformerConfigs.h"
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineDemos.h"
#include "SYDEEngineAssets.h"
#include "SYDEMainDemos.h"
#include "json.hpp"

using namespace std;
using namespace Gdiplus;
using json = nlohmann::json;
//INITIALIZING VARIABLES
const string dir = "BrainFiles\\";
Settings config("EngineFiles\\Settings\\configSettings.sc");
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

std::string getConfigFrom(string key, string defaultKey)
{
	try
	{
		std::ifstream ifs{ "EngineFiles\\Settings\\controls.json" };
		json save_file = json::parse(ifs);
		if (save_file.contains(key))
		{
			return save_file[key];
		}
		return defaultKey;
	}
	catch(exception ex)
	{
		return defaultKey;
	}
}

void saveSettings()
{

	json save_file;
	//PlayerStats
	save_file["jump"] = SYDEPlatformerControls::getJumpButton();
	save_file["left"] = SYDEPlatformerControls::getLeftButton();
	save_file["right"] = SYDEPlatformerControls::getRightButton();
	save_file["down"] = SYDEPlatformerControls::getDownButton();
	string filePath = string("EngineFiles\\Settings\\controls.json");
	std::ofstream ofs(filePath);
	ofs << save_file;
}

// MAIN FUNCTION
int main(int argc, char* argv[])
{
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	SYDEPlatformer m_Platformer;
	LPCWSTR title = L"Asterix Man";
	SYDECredits::_GAMETITLE = "Asterix Man";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	SetConsoleTitleW(title);
	//ARGUMENT SETTINGS
	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
	}
	config.volumeControl(1);
	config.ColourPalette(hOut);
	ConsoleWindow window(config.getConsoleHeight());
	srand(time(NULL));
	Font_Settings_Func::set_up_courier(16);
	SYDEFPS::setAnchor(SLA_Right);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, config.getConsoleWidth(), config.getConsoleHeight(), artVars);
	SYDEGamePlay::EnableClicking(hOut);

	SYDEPlatformerControls::setJumpButton(getConfigFrom("jump", SYDEPlatformerControls::getJumpButton()));
	SYDEPlatformerControls::setLeftButton(getConfigFrom("left", SYDEPlatformerControls::getLeftButton()));
	SYDEPlatformerControls::setRightButton(getConfigFrom("right", SYDEPlatformerControls::getRightButton()));
	SYDEPlatformerControls::setDownButton(getConfigFrom("down", SYDEPlatformerControls::getDownButton()));

	saveSettings();

	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_ESCAPE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(SYDEPlatformerControls::getJumpButton().at(0)));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(SYDEPlatformerControls::getDownButton().at(0)));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(SYDEPlatformerControls::getLeftButton().at(0)));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(SYDEPlatformerControls::getRightButton().at(0)));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SPACE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('T'));

	std::vector<std::string> v = config.ReturnCheats();

	if (std::find(v.begin(), v.end(), "DEBUGCONTROLS") != v.end())
	{
		SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('Q'));
		SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('E'));
	}

	SYDEGamePlay::showFPS(true);
	SYDEGamePlay::set_FPS_Position(Vector2(config.getConsoleWidth() - 6, 1));
	window.setStartingLine(1);
	while (true)
	{
		window = SYDEGamePlay::play(&m_Platformer, start, hOut, window, config.getConsoleWidth(), config.getConsoleHeight(), deltaTime);
		window.writeConsoleOptimized();
	}
	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hOut, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);
	cout.flush();
}
