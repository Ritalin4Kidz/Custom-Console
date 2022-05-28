#include "BattleScene.h"

bool BattleScene::doMoveCall = false;
int BattleScene::selectedMove = 0;
/*
TO DO LIST FOR BATTLE SCENE:
- ADD ACCURACY INTO MOVE (DONE)
- ADD STATUS EFFECTS INTO BATTLE
- ADD DEATH ANIMATIONS TO CHARACTERS
- ADD MOVE TO NEW SCENE WHEN BATTLE WON
- MAYBE INVENTORY (SO HEALING ITEMS AND SHIT NOT A PRIORITY)
*/
void startMove()
{
	BattleScene::callMove();
}

void moveClick()
{

	BattleScene::setSelectedMoveInt(stoi(SYDEClickableButton::getLastButtonTag()));
	BattleScene::callMove();
}

ConsoleWindow BattleScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTGREY_LIGHTGREY_BG);
		}
	}

	window = m_Enemy->drawAnimationAsset(window, Vector2(40, 1));
	for (int i = 0; i < ((float)m_Enemy->getHealth() / m_Enemy->getMaxHealth()) * 19; i++)
	{
			window.setTextAtPoint(Vector2(21 + i, 1), " ", RED_RED_BG);
	}
	window.setTextAtPoint(Vector2(21, 2), m_Enemy->getName() + " " + to_string(m_Enemy->getHealth()) + "/" + to_string(m_Enemy->getMaxHealth()), BRIGHTWHITE);

	window = m_Player->drawAnimationAsset(window, Vector2(20, 10));
	for (int i = 0; i < ((float)m_Player->getHealth() / m_Player->getMaxHealth()) * 19; i++)
	{
		window.setTextAtPoint(Vector2(40 + i, 19), " ", RED_RED_BG);
	}
	window.setTextAtPoint(Vector2(40, 18), m_Player->getName() + " " + to_string(m_Player->getHealth()) + "/" + to_string(m_Player->getMaxHealth()), BRIGHTWHITE);

	if (m_SceneState == m_BSS_Normal)
	{
		for (int i = 0; i < m_UIControl.size(); i++)
		{
			window = m_UIControl[i]->draw_ui(window);
		}
		if (doMoveCall)
		{
			doMoveCall = false;
			m_SceneState = m_BSS_DoMovePreWork;
		}
	}
	else if (m_SceneState == m_BSS_DoMovePreWork)
	{
		doMovePreWork();
		return window;
	}
	else if (m_SceneState == m_BSS_DoMoves)
	{
		window = doMoves(window);
		return window;
	}
	return window;
}

void BattleScene::onNewScene()
{
	m_SceneState = m_BSS_Normal;

	m_UIControl.clear();
	test();
	for (int i = 0; i < m_Player->getMoves().size(); i++)
	{
		m_UIControl.push_back(new SYDEClickableButton(
			m_Player->getMoveAtIndex(i)->getName(),
			Vector2(1, 8 + (i * 2)),
			Vector2(18, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			moveClick,
			to_string(i),
			"MoveData-" + to_string(i)
		));
		m_UIControl.push_back(new SYDELabel(
			to_string(m_Player->getMoveAtIndex(i)->getUsagesLeft()) + "/" + to_string(m_Player->getMoveAtIndex(i)->getMaxUsages()),
			Vector2(1, 9 + (i * 2)),
			Vector2(18, 1),
			BLACK,
			true,
			"LabelData-" + to_string(i)));
	}
	m_UIControl.push_back(new SYDEClickableButton(
		m_Player->getLastEffortMove()->getName(),
		Vector2(1, 17),
		Vector2(18, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		moveClick,
		to_string(4),
		"MoveData-" + to_string(4)
	));
	ValidateUI();
}

void BattleScene::test()
{
	m_Enemy = new OrcEnemy(5);
	m_Player = new PlayerFuri(5);

	m_UIControl.push_back(new SYDELabel("Battle", Vector2(0, 1), Vector2(6, 1), BLACK, true));

	//m_UIControl.push_back(new SYDEClickableButton(
	//	"Test Move",
	//	Vector2(4, 15),
	//	Vector2(9, 1),
	//	BLACK_BRIGHTWHITE_BG,
	//	NULLCOLOUR,
	//	false,
	//	startMove
	//));
}

void BattleScene::doMovePreWork()
{
	Move* PlayerMove;
	if (selectedMove >= 4)
	{
		PlayerMove = m_Player->getLastEffortMove();
	}
	else
	{
		PlayerMove = m_Player->getMoveAtIndex(selectedMove);
	}
	if (PlayerMove->getUsagesLeft() <= 0 && !PlayerMove->isLastEffortMove())
	{
		m_SceneState = m_BSS_Normal;
		return;
	}


	//GENERATE ENEMY MOVE
	Move* EnemyMove = m_Enemy->determineMove(*m_Player);
	EnemyMove->resetAnimation();
	PlayerMove->resetAnimation();
	//DETERMINE THE ORDER OF THE MOVES
	if (m_Enemy->getSpeed() >= m_Player->getSpeed())
	{
		enemyTurn = true;
	}
	if (enemyTurn)
	{
		m_MovesForTurn.push_back(EnemyMove);
		m_MovesForTurn.push_back(PlayerMove);
	}
	else
	{
		m_MovesForTurn.push_back(PlayerMove);
		m_MovesForTurn.push_back(EnemyMove);
	}
	//ANY OTHER LOADING
	windowText_Top = "";
	windowText_Bottom = "";
	m_BattleState = m_BS_Prework;
	//FINISH
	m_SceneState = m_BSS_DoMoves;
}

ConsoleWindow BattleScene::doMoves(ConsoleWindow window)
{
	if (m_BattleState == m_BS_Prework)
	{
		if (m_MovesForTurn.size() == 0)
		{
			m_SceneState = m_BSS_Normal;
			ValidateUI();
			return window;
		}
		windowText_Top = (enemyTurn ? m_Enemy->getName() : m_Player->getName()) + " Used";
		windowText_Bottom = m_MovesForTurn[0]->getName();
		//TODO: GET STATUS AND IF FAILED
		//IF MISS, USGAE DECREMENTS
		//IF STATUS AFFECTED, USAGES STAY SAME

		//ELSE ASSUME MOVE WAS USED
		m_MovesForTurn[0]->decrementUsages();
		std::string moveTag;
		m_Player->validateCurrentJsonTag();
		m_Enemy->validateCurrentJsonTag();
		json player = m_Player->getJSONTag();
		json enemy = m_Enemy->getJSONTag();
		if (!m_MovesForTurn[0]->isSuccessful(enemyTurn ? &enemy : &player,enemyTurn ? &player : &enemy, &moveTag))
		{
			//TODO: SHOW AN ATTACK FAILED SCREEN
			m_BattleState = m_BS_Postwork;
			m_MovesForTurn.erase(m_MovesForTurn.begin());
		}
		else
		{
			m_BattleState = m_BS_Animation;
		}
	}
	else if (m_BattleState == m_BS_Animation)
	{
		window = m_MovesForTurn[0]->drawAnimation(window, Vector2(20, 1));
		if (m_MovesForTurn[0]->getAnimation().getFrame() >= m_MovesForTurn[0]->getAnimation().getFrameSize() - 1)
		{
			m_Player->validateCurrentJsonTag();
			m_Enemy->validateCurrentJsonTag();
			std::string moveTag;
			json player = m_Player->getJSONTag();
			json enemy = m_Enemy->getJSONTag();
			//ANIMATION DONE
			timeTakenPostWork = 0;
			m_MovesForTurn[0]->Execute(
				enemyTurn ? &enemy : &player,
				enemyTurn ? &player : &enemy,
				&moveTag);
			enemyTurn = !enemyTurn;

			m_MovesForTurn.erase(m_MovesForTurn.begin());

			m_Player->validateFromJson(player);
			m_Enemy->validateFromJson(enemy);
			m_BattleState = m_BS_Prework;
		}
		else
		{
			for (int i = 0; i < 14; i++)
			{
				window.setTextAtPoint(Vector2(45 + i, 17), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
			}
			for (int i = 0; i < 14; i++)
			{
				window.setTextAtPoint(Vector2(45 + i, 18), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
			}
			window.setTextAtPoint(Vector2(45, 17), windowText_Top, BLACK_BRIGHTWHITE_BG);
			window.setTextAtPoint(Vector2(45, 18), windowText_Bottom, BLACK_BRIGHTWHITE_BG);
		}
	}
	else if (m_BattleState == m_BS_Postwork)
	{
		timeTakenPostWork += SYDEDefaults::getDeltaTime();
		if (timeTakenPostWork >= 1.5f)
		{
			m_BattleState = m_BS_Prework;
		}
	}
	return window;
}

void BattleScene::ValidateUI()
{
	int FinishedMoves = 4;
	for (int i = 0; i < m_UIControl.size(); i++)
	{
		if (m_UIControl[i]->m_Label.find("LabelData") != std::string::npos)
		{
			int moveIndex = stoi(m_UIControl[i]->m_Label.substr(m_UIControl[i]->m_Label.size() - 1, 1));
			m_UIControl[i]->m_Text = to_string(m_Player->getMoveAtIndex(moveIndex)->getUsagesLeft()) + "/" + to_string(m_Player->getMoveAtIndex(moveIndex)->getMaxUsages());
		}
		if (m_UIControl[i]->m_Label.find("MoveData") != std::string::npos)
		{
			int moveIndex =stoi(m_UIControl[i]->m_Label.substr(m_UIControl[i]->m_Label.size() - 1, 1));
			if (moveIndex >= m_Player->getMoves().size())
			{
				m_UIControl[i]->setEnabled(m_Player->getUsableMoves().size() <= 0);
			}
			else
			{
				m_UIControl[i]->setEnabled(m_Player->getMoveAtIndex(moveIndex)->getUsagesLeft() > 0);
			}
		}
	}
}
