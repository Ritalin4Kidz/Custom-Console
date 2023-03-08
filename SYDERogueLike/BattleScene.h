#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"
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

enum BattleState
{
	m_BS_Prework = 0,
	m_BS_Animation = 1,
	m_BS_Postwork = 2
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

	static void validateInventory();

	string getStatusString(_SQStatus s);

	ColourClass getStatusColour(_SQStatus s);

	void endBattle();

	void test();

	static void callMove() { HideUI();  doMoveCall = true; }
	static void setUsesItem() { isItemMove = true; }
	static void setSelectedMoveInt(int index) { selectedMove = index; }
	void doMovePreWork();

	void doStatus(std::shared_ptr<Character> charac, bool enemy);
	void doSleepStatus(std::shared_ptr<Move>* move, std::shared_ptr<Character> charac);

	ConsoleWindow doMoves(ConsoleWindow window);

	void ValidateUI();

	static bool getMoveCall() { return doMoveCall; }
	static bool inventoryActive;
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
private:
	static bool doMoveCall;
	static bool isItemMove;
	static int selectedMove;

	static int inventoryStart;

	SYDEClickableButton invPrev;
	SYDEClickableButton invNext;

	float playerHeight;
	float enemyHeight;

	const float fallSpeed = 22.5f;

	BattleSceneStates m_SceneState = m_BSS_Normal;

	std::shared_ptr<Enemy> m_Enemy;
	std::shared_ptr<Player> m_Player;

	vector<MoveTurn> m_MovesForTurn = vector<MoveTurn>();

	BattleState m_BattleState = m_BS_Prework;

	std::string windowText_Top = "";
	std::string windowText_Bottom = "";
	float timeTakenPostWork = 0;
};