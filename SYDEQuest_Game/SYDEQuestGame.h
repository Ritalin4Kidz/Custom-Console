#pragma once
#include "Scene.h"
#include "SYDEstdafx.h"
#include "SYDEEngineUI.h"
#include "StatusAnimations.h"
#include "Character.h"
#include "BuildCharacter.h"
#include "SQFunctions.h"
#include <functional>
#include <ctime>
#include <fstream>
#include <istream>
#include <sstream>
#include "json.hpp"
#include "FightWindow.h"
#include "Buildings.h"
#include "Bounties.h"

#define STARTING_GOLD_AMOUNT 5000

using json = nlohmann::json;

class SYDEMapGame : public SYDEWindowGame {
public:
	SYDEMapGame();
	virtual ~SYDEMapGame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	static void setAnimation_UI_EVENT(CustomAnimationAsset _Anim, std::string _Header) { m_MoveAnimation = _Anim; m_MoveAnimation.setFrame(0); UI_STATE_EVENT = true; _AnimHeader = _Header; }
	static ConsoleWindow Animation_UI_EVENT(ConsoleWindow window, CustomAnimationAsset& _anim);
	void SwitchScene();

	static AssetsClass astVars;
	static bool UI_STATE_EVENT;
	static FightWindow _FWindow;
	static Player m_Player;
	static Vector2 camera_Pos;
	static Vector2 movement_Pos;
	static float movementSpeed;
	static vector<string> Split(string a_String, char splitter);
	static CustomAnimationAsset StringToAnimation(std::string s);
	//Animations
	static CustomAnimationAsset m_MoveAnimation;
	static std::string _AnimHeader;

	//ENEMY ANIMATIONS
	static CustomAnimationAsset m_ORC;
	static CustomAnimationAsset m_BLUE_FISH;
	static CustomAnimationAsset m_WOLF;
	static CustomAnimationAsset m_CRAB;
	static CustomAnimationAsset m_BEE;
	static CustomAnimationAsset m_RABBIT;
#pragma region BossAnimations
	//BOSS ANIMATIONS
	static CustomAnimationAsset m_SMOKE_CRAB;
	static CustomAnimationAsset m_SMOKE_CRAB_CUTSCENE;
	static CustomAnimationAsset m_SMOKE_CRAB_CUTSCENE_WON;

	static CustomAnimationAsset m_FREEBEE;
	static CustomAnimationAsset m_FREEBEE_CUTSCENE;
	static CustomAnimationAsset m_FREEBEE_CUTSCENE_WON;
#pragma endregion

private:
	GameScene* m_Scene = new GameScene();

};



#pragma region Scenes
class BattleScene : public GameScene {
public:
	BattleScene();
	~BattleScene() {}
	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow fight_header(ConsoleWindow window, int windowWidth, int windowHeight);

	static void setPlayer(Player p) { m_Player = p; }
	static void setEnemy(Enemy e) { m_Enemy = e; m_Enemy.setAnimationLoop(true); }

	static void SetUpFight();
	static void WonFight(ConsoleWindow window);
	static void Handle_Fight_Tags(Character* c);
	static void Handle_Player_Abilities(Character* c);

	static void DeathCheck(ConsoleWindow window);

	static void CleanUpFight(bool PlayerDead);

	static bool DoStatusAnimation(Character* c, bool& CanFight);

	static void DoPlayerAttack(int i);
	static void DoEnemyAttack();
private:
	static Player m_Player;
	static Enemy m_Enemy;
	static SYDEMenu _FightOptions;
	static SYDEMenu _MoveOptions;
	static bool enemy_attack;
	static bool _StatusApplied;
};
class MainMenuScene : public GameScene {
public:
	MainMenuScene();
	~MainMenuScene();
	void BattleTestSetup();
	void MainMapTestSetup();
	void BuildingTestSetup();
	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	static CustomAnimationAsset m_MainMenu_BG;
	//static float time_passed;
	static SYDEMenu _Options;
};
struct WildFightArea {
	WildFightArea(Vector2 v, std::string e) { m_Loc = v; wfa_EnemyStr = e; }
	Vector2 m_Loc;
	std::string wfa_EnemyStr;
};

struct DockArea {
	DockArea(Vector2 v) { m_Loc = v; }
	Vector2 m_Loc;
};

struct DockChoice
{
	DockChoice(string island, int cost) { NextIsland = island; FerryCost = cost; }
	string NextIsland;
	int FerryCost;
};

struct MoveChoice
{
	MoveChoice(Move* _Move, int cost) { m_Move = _Move; m_Cost = cost; }
	void Clear() { delete[] m_Move;}

	Move* m_Move;
	int m_Cost;
};

enum MainMapSceneState {
	MState_Normal,
	MState_Shopping,
	MState_Docking,
	MState_Sailing,
	MState_MoveSwap,
	MState_Cutscene,
	MState_GameWon,
	MState_Paused
};

enum Cutscene_Return_State {
	CSR_MainMap,
	CSR_EndGame,
	CSR_BossFight
};

class MainMapScene : public GameScene {
public:
	MainMapScene();
	~MainMapScene();
	void LoadGameScene();
	void DestroyScene(bool quitGame);

	ConsoleWindow Selecting(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Sailing(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Shopping(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Building(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow MoveSwap(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow GameWon(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Paused(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow BossCutscene(ConsoleWindow window, int windowWidth, int windowHeight);

	void setSail(string a_STATE) { sailingTime = 0.0f; m_IslandBMP = a_STATE; _MapState = MState_Sailing; }
	static void setUpCutscene(ConsoleWindow window, Cutscene_Return_State csr, bool getWindow);

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	int AddEnemy(Vector2 pixelLoc, Gdiplus::Color pixelColour);
	std::string getEnemy(Vector2 loc);
	void SetEnemyFromTag(Enemy& e);
	int CheckWFA(char tempChar);
	static void AddWildChar(Vector2 loc, char ico, std::string data, int col);
	static void AddDockChar(Vector2 loc, char ico);
	static void AddShopChar(Vector2 loc, char ico);
	static void AddBossChar(Vector2 loc, int col);
	static void AddBlankChar(Vector2 loc, int col);
	static void AddFlowerChar(Vector2 loc);
	static void AddBuildingChar(Vector2 loc, char ico, std::string data);

	static string getBossTag() { return m_BossTAG; }
	static void setBossTag(string tag) { m_BossTAG = tag; }
	static void clearBossTag() { m_BossTAG = ""; }
	static void RefreshRun() { gold_from_run = STARTING_GOLD_AMOUNT; _MapState = MState_Normal; m_BossTAG = ""; isFightingBoss = false; m_IslandsDeep = 0;}
	static void AddGold(int amt) { gold_from_run += amt; }
	static void RefreshDockChoices();
	static void DeleteMoveChoices();
	static void RefreshMoveChoices();
	static void RefreshPlayerMenuChoices();
	static void RefreshStartIsland() { m_IslandBMP = "Start Island"; if (hasLoaded) { hasLoaded = false; } }

	static bool getIsFightingBoss() { return isFightingBoss; }
	static void setIsFightingBoss(bool b) { isFightingBoss = b; }

	static Cutscene_Return_State getCSR() { return m_CSR_State; }

	static int randomFlowerColour() { int col = rand() % 4; 
	if (col == 0) return 36; 
	if (col == 1) return 43;
	if (col == 2) return 39;
	if (col == 3) return 37;
	return 36;
	}

	static Enemy* getRandomEnemyFromPool(int pool, int minLvl);

	static SYDEParticleBurst m_GameOverFireworks;
	static SYDEClock_Timer m_FireworksTimer;

private:
	static SYDEMenu _PauseOptions;
	static SYDEMenu _DockOptions;
	static SYDEMenu _ShopOptions;
	static SYDEMenu _PlayerMenuOptions;
	static CustomAsset _DockOptionsUI;
	static CustomAnimationAsset m_SAIL;
	static float sailingTime;
	static float maxSailTime;
	static int gold_from_run;
	static MainMapSceneState _MapState;
	//static bool isSailing;
	static bool isFightingBoss;
	static CustomAsset m_bg;
	static CustomAsset m_Map;
	static std::vector<WildFightArea> _FightingAreas;
	//static std::vector<DockArea> _DockAreas;
	static bool hasLoaded;
	static Move* _MoveToSwapIn;
	static std::vector<DockChoice> _DockChoices;
	static std::vector<MoveChoice> _MoveChoices;
	static string m_IslandBMP;

	static string m_BossTAG;
	static Cutscene_Return_State m_CSR_State;
	static ConsoleWindow windowAtCutsceneTime;
	static CustomAnimationAsset m_BossCutscene;

	static int m_IslandsDeep;
};


struct MoveStats {
	MoveStats() {}
	MoveStats(int null);
	MoveStats(json j);
	_SQType m_Type;
	std::string m_Name;
	float BasePower;
	std::vector<_SQType> m_TeachAbleTypes;
	std::string typesToString();
};
enum MSS_States {
	EquippedMoves,
	UnlockedMoves
};
class MoveSelectionScene : public GameScene {
public:
	MoveSelectionScene();
	~MoveSelectionScene();
	void Configure_EO();
	void Configure_UO();
	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	SYDEMenu _MoveOptions;
	SYDEMenu _UnlockedOptions;
	int UnlockedPage = 0;
	int MaxUnlockPages = 0;
	MoveStats mvs;
	MSS_States mss = EquippedMoves;
};


#pragma endregion

#pragma region CutScenes
class LoadScene : public GameScene {
public:
	LoadScene();
	LoadScene(_SQScene s);
	~LoadScene();
	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	CustomAnimationAsset m_LoadSceneAnimation;
	_SQScene m_LoadScene;
};
#pragma endregion


#pragma region TimerStuff
void TickFunc();
#pragma endregion
