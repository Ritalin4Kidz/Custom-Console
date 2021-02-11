#pragma once
#include "SYDEstdafx.h"
#include "SYDEScreenshot.h"
#include "SYDEEngineAssets.h"
#include "SYDEEngineMath.h"
#include "SYDEEngineUI.h"

class SYDEMainDemos {
public:
	SYDEMainDemos();
	virtual ~SYDEMainDemos();
	void GenerateTriangle();
	void TicTacToe(bool isAIp1, bool isAIp2, int offset, string OBrain, string XBrain);
	void PixelArt(ColourClass skinOuter, ColourClass skinMiddle, ColourClass skinInner, ColourClass Meat, ColourClass Seed, ColourClass BG, string a_text);
	void Options(vector<string> options);
	void generateart();
	void scene1();
	void scene2();
	void scene3();
	void scene4();
	void scenes();
	void Test();
	void Cutscene();
	void outputVar();
	void drawBrain(string AIBrain);
	void playTicTacToe();
	void nodePath();
	ColourClass determineColour(ColourClass main, ColourClass bg);
	void PlayLevel(string level, bool jumpAllowed, bool dropAllowed);
	void play_syde();
	void bmp_test();
	void bmp_test2(CustomAsset asset_to_draw); //Keep As Intructions
	void animation_test();
	void animation_test_turtle();
	void Sprite_Sheet_Test();
	void animation_test_player();
	void set_up_custom_assets();
	void set_up_window_properties();
	void set_up_shape_test();

protected:
	vector<string> Split(string a_String, char splitter);
	bool GetKeyDown(char KeyCode)	{ return GetAsyncKeyState(KeyCode) && 0x8000; }
	bool charHitBoxCheck(Vector2 point, Vector2 obj, int startX, int endX, int startY, int endY);
	void introductionScript();
	string returnRandomNonsense();
	void drawTitle(int baseY, int baseX);
	void introMenu();
	void drawBee(int baseY, int baseX, bool setUp);
	void poweredBySYDEEngine(int baseY, int baseX);
	void introCreditsScript();
	wstring s2ws(const string& s);
	void opening();
private:
	const string dir = "BrainFiles\\";
	Settings config = Settings("EngineFiles\\Settings\\configSettings.sc");
	ConsoleWindow window = ConsoleWindow(windowHeight);
	int windowWidth = 40;
	const int windowHeight = 20;
	int XWins = 0;
	int OWins = 0;
	int Draws = 0;
	//GAME VALUES
	COORD start = { (SHORT)0, (SHORT)0 };
	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Vector2 startPosition = Vector2(5, 19);
	string cutsceneStr = "SYDE_Ep1_Intro";
	bool consoleOpen = false;
	bool isScene = true;
	bool watermelonIsCutScene = true;
	int generations = 0;
	bool foundPath = false;
	bool Cheat_CanJump = false;
	bool Cheat_Wireframe = false;
	//SYDE VALUES
	string levelBonus = "Break_Room";
	string command = "";
	string info = "";
	string lookAngleStr = "Right";
	//CHARACTER SKINS
	string characterName1 = "Officer_Man";
	vector<ColourClass> charSkin1 = { DARKBLUE_DARKBLUE_BG, BLACK, BRIGHTYELLOW_BRIGHTYELLOW_BG, WHITE_WHITE_BG };
	string characterName2 = "Nude_Lunatic";
	vector<ColourClass> charSkin2 = { WHITE_WHITE_BG, WHITE_WHITE_BG, WHITE_WHITE_BG, WHITE_WHITE_BG };
	string characterName3 = "Sunday_Sport";
	vector<ColourClass> charSkin3 = { BRIGHTRED_BRIGHTRED_BG, LIGHTBLUE_PURPLE_BG, LIGHTBLUE_LIGHTBLUE_BG, WHITE_WHITE_BG };
	string characterName4 = "Green_Person";
	vector<ColourClass> charSkin4 = { BRIGHTGREEN_BRIGHTGREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG, BRIGHTGREEN_BRIGHTGREEN_BG };
	vector<vector<ColourClass>> charSkins{ charSkin1, charSkin2, charSkin3, charSkin4 };
	vector<string> charNames = { characterName1, characterName2, characterName3, characterName4 };
	int skinNumber = 0;
	//DRAWING SETTINGS
	BackgroundClass bgVars;
	Characters charVars;
	Artwork artVars;
	//OTHER ASSETS
	AssetsClass astVars;
	CustomAnimationAsset testAnimation;
	//DECLARE CUSTOM ASSETS HERE
	CustomAsset testBmp;
	CustomAsset fieldTestBmp;
};