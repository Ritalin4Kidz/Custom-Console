#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEEngineUI.h"
#include <SYDEClickableButton.h>
#include "Enemy.h"
#include "Player.h"
#include "MovesHeader.h"

enum BattleSceneStates
{
	m_BSS_Normal = 0,
	m_BSS_DoMovePreWork = 1,
	m_BSS_DoMoves = 2,
	m_BSS_EndFall = 3
};

enum BattleSceneViewState
{
	BSVS_Normal,
	BSVS_Inventory,
	BSVS_InvDetail,
	BSVS_EnemDetail
};

enum BattleState
{
	m_BS_Prework = 0,
	m_BS_Animation = 1,
	m_BS_Postwork = 2,
	m_BS_StatChangeAnimation = 3
};

struct StoredStatsObj
{
	StoredStatsObj(int a, int d, int mA, int mD, int s) { atk = a; def = d; mAtk = mA; mDef = mD; spd = s; }
	int atk;
	int def;
	int mDef;
	int mAtk;
	int spd;
};


struct StatChangeObj
{
	StatChangeObj(std::string s, int a, bool p, bool i, CustomAnimationAsset anim) { stat = s; amount = a; isPlayer = p; isIncrease = i;  animation = anim; }
	std::string stat;
	int amount;
	bool isPlayer;
	bool isIncrease;
	CustomAnimationAsset animation;
};

struct MoveTurn
{
	MoveTurn(std::shared_ptr<Move> m, bool e) { move = m; enemyTurn = e; }
	std::shared_ptr<Move> move;
	bool enemyTurn = false;
};


class BattleScene : public GameScene
{
public:
	BattleScene() { m_SceneTag = "Battle Scene"; m_isTransient = true; }
	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow drawChars(ConsoleWindow window);

	void onNewScene() override;
	void destroyScene() override;

	ConsoleWindow drawInventoryScreen(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow drawInvDetailsScreen(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow drawDetailsScreen(ConsoleWindow window, int windowWidth, int windowHeight);

	static void validateInventory();

	void addStatChanges(StoredStatsObj obj, Character c, bool isPlayer);

	void checkTags(std::string moveTag);

	string getStatusString(_SQStatus s);

	ColourClass getStatusColour(_SQStatus s);

	void endBattle();

	void test();

	static void callMove() { HideUI();  doMoveCall = true; }
	static void setUsesItem() { isItemMove = true; }
	static void setSelectedMoveInt(int index) { selectedMove = index; }
	static void setSelectedInvInt(int index) { selectedInv = index; }

	static int getSelectedInvInt() { return selectedInv; }

	void doMovePreWork();

	void doStatus(std::shared_ptr<Character> charac, bool enemy);
	void doSleepStatus(std::shared_ptr<Move>* move, std::shared_ptr<Character> charac);

	ConsoleWindow doMoves(ConsoleWindow window);

	void ValidateUI();

	static bool canUseItem;

	static bool getMoveCall() { return doMoveCall; }
	static void refreshInv() { inventoryStart = 0; }
	static void addInvStart(int amt) {
		if ((inventoryStart + amt) >= SydeRogueLikeStatics::getPlayer()->getInventory().size())
		{
			return;
		}
		inventoryStart += amt;
		if (inventoryStart < 0)
		{
			inventoryStart = 0;
		}
	}

	static BattleSceneViewState m_ViewState;

private:
	static bool doMoveCall;
	static bool isItemMove;
	static int selectedMove;
	static int selectedInv;

	static int inventoryStart;

	SYDEClickableButton invPrev;
	SYDEClickableButton invNext;

	float playerHeight;
	float enemyHeight;

	const float fallSpeed = 22.5f;

	BattleSceneStates m_SceneState = m_BSS_Normal;

	std::shared_ptr<Enemy> m_Enemy;
	std::shared_ptr<Player> m_Player;

	std::vector<StatChangeObj> m_StatChanges = std::vector<StatChangeObj>();

	vector<MoveTurn> m_MovesForTurn = vector<MoveTurn>();

	BattleState m_BattleState = m_BS_Prework;
	CustomAsset m_EnemBG = CustomAsset(28, 12, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\EnemBG.bmp", 14, 12));
	std::string windowText_Top = "";
	std::string windowText_Bottom = "";
	float timeTakenPostWork = 0;

	const CustomAnimationAsset m_StatDown = CustomAnimationAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BattleAnim\\StatDrop.bmp", 80, 32, 8, 8, 0, 40));
	const CustomAnimationAsset m_StatUp = CustomAnimationAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\BattleAnim\\StatIncrease.bmp", 80, 32, 8, 8, 0, 40));

	SYDEClickableButton confirmItemButton;
	SYDEClickableButton backItemButton;
};