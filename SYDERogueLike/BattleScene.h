#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"

#include "SYDEstdafx.h"
#include "SYDEUI.h"
#include <SYDEClickableButton.h>
#include "OrcEnemy.h"
#include "Player.h"

enum BattleSceneStates
{
	m_BSS_Normal = 0,
	m_BSS_DoMovePreWork = 1,
	m_BSS_DoMoves = 2
};

enum BattleState
{
	m_BS_Prework = 0,
	m_BS_Animation = 1,
	m_BS_Postwork = 2
};


class BattleScene : public GameScene
{
public:
	BattleScene() { m_SceneTag = "Battle Scene"; m_isTransient = true; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	void destroyScene() override;


	void endBattle();

	void test();

	static void callMove() { doMoveCall = true; }
	static void setSelectedMoveInt(int index) { selectedMove = index; }
	void doMovePreWork();

	ConsoleWindow doMoves(ConsoleWindow window);

	void ValidateUI();

private:
	static bool doMoveCall;
	static int selectedMove;
	BattleSceneStates m_SceneState = m_BSS_Normal;

	Enemy* m_Enemy;
	Player* m_Player;

	vector<Move*> m_MovesForTurn = vector<Move*>();
	bool enemyTurn = false;

	BattleState m_BattleState = m_BS_Prework;

	std::string windowText_Top = "";
	std::string windowText_Bottom = "";
	float timeTakenPostWork = 0;
};