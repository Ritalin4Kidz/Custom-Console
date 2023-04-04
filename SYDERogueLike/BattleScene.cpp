#include "BattleScene.h"

bool BattleScene::doMoveCall = false;
bool BattleScene::isItemMove = false;
bool BattleScene::canUseItem = false;
BattleSceneViewState BattleScene::m_ViewState = BSVS_Normal;
int BattleScene::selectedMove = 0;
int BattleScene::selectedInv = 0;
int BattleScene::inventoryStart = 0;
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
	if (!BattleScene::m_ViewState == BSVS_Normal)
	{
		BattleScene::callMove();
	}
}

void inventoryClick()
{
	if (BattleScene::m_ViewState == BSVS_Inventory)
	{
		BattleScene::m_ViewState = BSVS_Normal;
	}
	else
	{
		BattleScene::m_ViewState = BSVS_Inventory;
	}
	BattleScene::refreshInv();
}

void detailsClick()
{
	BattleScene::m_ViewState = BSVS_EnemDetail;
}


void inventoryNextClick()
{
	BattleScene::addInvStart(4);
}

void inventoryPrevClick()
{
	BattleScene::addInvStart(-4);
}

void nullClick()
{
	
}

void inventoryItemNullClick()
{
	BattleScene::m_ViewState = BSVS_InvDetail;
	BattleScene::setSelectedInvInt(stoi(CustomAsset_Clickable::getLastButtonTag()));
	BattleScene::canUseItem = false;
}

void inventoryItemClick()
{
	BattleScene::m_ViewState = BSVS_InvDetail;
	BattleScene::canUseItem = true;
	BattleScene::setSelectedInvInt(stoi(CustomAsset_Clickable::getLastButtonTag()));
}

void inventoryItemConfirmClick()
{
	BattleScene::m_ViewState = BSVS_Normal;
	BattleScene::setSelectedMoveInt(BattleScene::getSelectedInvInt());
	BattleScene::setUsesItem();
	BattleScene::callMove();
}

void inventoryItemBackClick()
{
	BattleScene::m_ViewState = BSVS_Inventory;
}



void moveClick()
{
	if (BattleScene::m_ViewState == BSVS_Normal || BattleScene::m_ViewState == BSVS_EnemDetail)
	{
		BattleScene::setSelectedMoveInt(stoi(SYDEClickableButton::getLastButtonTag()));
		BattleScene::callMove();
	}
}

ConsoleWindow BattleScene::drawInvDetailsScreen(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window.setTextAtPoint(Vector2(22, 1), "Item: " + SydeRogueLikeStatics::getPlayer()->getInventory().at(selectedInv)->getName(), BRIGHTWHITE);

	window = backItemButton.draw_ui(window);
	if (canUseItem)
	{
		window = confirmItemButton.draw_ui(window);
	}

	return window;
}

ConsoleWindow BattleScene::drawDetailsScreen(ConsoleWindow window, int windowWidth, int windowHeight)
{

	window.setTextAtPoint(Vector2(22, 2), m_Enemy->getName(), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(22, 3), "Level: " + to_string(m_Enemy->getLevel()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(22, 4), "Type: " + SydeRogueLikeStatics::TypeToString(m_Enemy->getType()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(22, 5), "Moves: ", BRIGHTWHITE);
	for (int i = 0; i < m_Enemy->getMoves().size(); i++)
	{
		window.setTextAtPoint(Vector2(22, (i + 6)), m_Enemy->getMoveAtIndex(i)->getName() + ": " +
			SydeRogueLikeStatics::TypeToString(m_Enemy->getMoveAtIndex(i)->getType())
			, BRIGHTWHITE);
	}

	window.setTextAtPoint(Vector2(22, 16), "Ability: " + m_Enemy->getAbility().m_AbilityName, BRIGHTWHITE);
	window.setTextAtPoint(Vector2(22, 17), m_Enemy->getAbility().m_Description, BRIGHTWHITE);
	return window;
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

	if (m_ViewState == BSVS_Inventory)
	{
		return drawInventoryScreen(window, windowWidth, windowHeight);
	}
	else if (m_ViewState == BSVS_EnemDetail)
	{
		return drawDetailsScreen(window, windowWidth, windowHeight);
	}
	else if (m_ViewState == BSVS_InvDetail)
	{
		return drawInvDetailsScreen(window, windowWidth, windowHeight);
	}


	window = drawChars(window);

	if (m_SceneState == m_BSS_Normal)
	{
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
	else if (m_SceneState == m_BSS_EndFall)
	{
		if (m_Player->getHealth() <= 0)
		{
			playerHeight += fallSpeed * SYDEDefaults::getDeltaTime();
		}
		if (m_Enemy->getHealth() <= 0)
		{
			enemyHeight += fallSpeed * SYDEDefaults::getDeltaTime();
		}
		if (playerHeight > 50 || enemyHeight > 50)
		{
			m_SceneState = m_BSS_Normal;
			m_Player->clearStatus();
			SydeRogueLikeStatics::setSceneTag("Post Battle Scene");
		}
		return window;
	}
	return window;
}

ConsoleWindow BattleScene::drawChars(ConsoleWindow window)
{
	if (m_Enemy->getRequireBG())
	{
		window = m_EnemBG.draw_asset(window, Vector2(m_Enemy->getDrawPos(), enemyHeight));
	}
	window = m_Enemy->drawAnimationAsset(window, Vector2(m_Enemy->getDrawPos(), enemyHeight));
	for (int i = 0; i < ((float)m_Enemy->getHealth() / m_Enemy->getMaxHealth()) * 19; i++)
	{
		window.setTextAtPoint(Vector2(21 + i, 1), " ", RED_RED_BG);
	}
	window.setTextAtPoint(Vector2(21, 2), m_Enemy->getName() + " " + to_string(m_Enemy->getHealth()) + "/" + to_string(m_Enemy->getMaxHealth()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(21, 3), getStatusString(m_Enemy->getStatus()), getStatusColour(m_Enemy->getStatus()));

	window = m_Player->drawAnimationAsset(window, Vector2(20, playerHeight));
	for (int i = 0; i < ((float)m_Player->getHealth() / m_Player->getMaxHealth()) * 19; i++)
	{
		window.setTextAtPoint(Vector2(40 + i, 19), " ", RED_RED_BG);
	}
	window.setTextAtPoint(Vector2(40, 18), m_Player->getName() + " " + to_string(m_Player->getHealth()) + "/" + to_string(m_Player->getMaxHealth()), BRIGHTWHITE);
	window.setTextAtPoint(Vector2(40, 17), getStatusString(m_Player->getStatus()), getStatusColour(m_Player->getStatus()));
	return window;
}

void BattleScene::onNewScene()
{
	m_ViewState = BSVS_Normal;
	canUseItem = false;
	isItemMove = false;
	m_SceneState = m_BSS_Normal;
	playerHeight = 10;
	enemyHeight = 1;
	m_Player = SydeRogueLikeStatics::getPlayer();
	m_Player->saveStats();
	m_Enemy = SydeRogueLikeStatics::getEnemy();
	invPrev = SYDEClickableButton(
		"<<",
		Vector2(1, 5),
		Vector2(2, 1),
		BRIGHTWHITE_GREEN_BG,
		NULLCOLOUR,
		false,
		inventoryPrevClick,
		"prevInv",
		"prevInv"
	);
	invPrev.setEnabled(true);
	invNext = SYDEClickableButton(
		">>",
		Vector2(16, 5),
		Vector2(2, 1),
		BRIGHTWHITE_GREEN_BG,
		NULLCOLOUR,
		false,
		inventoryNextClick,
		"nextInv",
		"nextInv"
	);
	invNext.setEnabled(true);

	validateInventory();

	for (int i = 0; i < m_Player->getMoves().size(); i++)
	{
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
			m_Player->getMoveAtIndex(i)->getName(),
			Vector2(1, 8 + (i * 2)),
			Vector2(18, 1),
			BLACK_BRIGHTWHITE_BG,
			NULLCOLOUR,
			false,
			moveClick,
			to_string(i),
			"MoveData-" + to_string(i)
		)));
		addToUIControl(std::shared_ptr<SYDEUI>(new SYDELabel(
			to_string(m_Player->getMoveAtIndex(i)->getUsagesLeft()) + "/" + to_string(m_Player->getMoveAtIndex(i)->getMaxUsages()),
			Vector2(1, 9 + (i * 2)),
			Vector2(18, 1),
			BLACK,
			true,
			"LabelData-" + to_string(i))));
	}
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		m_Player->getLastEffortMove()->getName(),
		Vector2(1, 17),
		Vector2(18, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		moveClick,
		to_string(4),
		"MoveData-" + to_string(4)
	)));

	//INVENTORY
	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"    Inventory    ",
		Vector2(1, 4),
		Vector2(17, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		inventoryClick,
		"Inventory",
		"Inventory"
	)));

	addToUIControl(std::shared_ptr<SYDEUI>(new SYDEClickableButton(
		"  Enemy Details  ",
		Vector2(1, 6),
		Vector2(17, 1),
		BLACK_BRIGHTWHITE_BG,
		NULLCOLOUR,
		false,
		detailsClick,
		"Enemy Details",
		"Enemy Details"
	)));


	confirmItemButton = SYDEClickableButton(
		"CONFIRM",
		Vector2(50, 19),
		Vector2(7, 1),
		BRIGHTWHITE_GREEN_BG,
		NULLCOLOUR,
		false,
		inventoryItemConfirmClick,
		to_string(4),
		""
	);
	backItemButton = SYDEClickableButton(
		"GO BACK",
		Vector2(22, 19),
		Vector2(7, 1),
		BRIGHTWHITE_RED_BG,
		NULLCOLOUR,
		false,
		inventoryItemBackClick,
		to_string(4),
		""
	);

	ValidateUI();
	ShowUI();
	SydeRogueLikeStatics::toggleFightSuccess(true);
}

void BattleScene::destroyScene()
{
	//ALL THE WORK WE NEED TO DO BEFORE MOVING TO ANOTHER SCENE :P
	m_Player->reviveStats();

	for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getInventory().size(); i++)
	{
		SydeRogueLikeStatics::getPlayer()->SetInventoryDetailsAtIndex(i, nullptr, "");
	}

	SydeRogueLikeStatics::setPlayer(m_Player);
//	for (int i = 0; i < m_MovesForTurn.size(); i++)
//	{
//		delete m_MovesForTurn[i];
//	}
	m_MovesForTurn.clear();
	m_StatChanges.clear();
	ShowUI();
	m_Player = NULL;
}

ConsoleWindow BattleScene::drawInventoryScreen(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; (i + inventoryStart) < SydeRogueLikeStatics::getPlayer()->getInventory().size() && i < 4; i++)
	{
		int x = (20 * (i % 2)) + 24;
		int y = i % 4 >= 2 ? 12 : 2;
		window = SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(i + inventoryStart)->getItemIcon().draw_asset(window, Vector2(x, y));
		window.setTextAtPoint(Vector2(x, y + 7), SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(i + inventoryStart)->getName(), BRIGHTWHITE);
	}
	window = invNext.draw_ui(window);
	window = invPrev.draw_ui(window);
	return window;
}

void BattleScene::validateInventory()
{
	for (int i = 0; i < SydeRogueLikeStatics::getPlayer()->getInventory().size(); i++)
	{
		if (SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(i)->isUsableInBattle())
		{
			SydeRogueLikeStatics::getPlayer()->SetInventoryDetailsAtIndex(i, inventoryItemClick, to_string(i));
		}
		else
		{
			SydeRogueLikeStatics::getPlayer()->SetInventoryDetailsAtIndex(i, inventoryItemNullClick, to_string(i));
		}
	}
	inventoryStart = 0;
}

void BattleScene::checkTags(std::string moveTag)
{
	if (moveTag == "RELIGHT")
	{
		m_MovesForTurn[0].enemyTurn ? m_Enemy->refillMoves() : m_Player->refillMoves();
	}
}

string BattleScene::getStatusString(_SQStatus s)
{
	if (s == Status_Sleep)
	{
		return "SLP";
	}
	else if (s == Status_Burnt)
	{
		return "BRN";
	}
	else if (s == Status_Sabotaged)
	{
		return "SBT";
	}
	else if (s == Status_Enchanted)
	{
		return "ECT";
	}
	return "";
}

ColourClass BattleScene::getStatusColour(_SQStatus s)
{
	if (s == Status_Sleep)
	{
		return BLACK_BRIGHTWHITE_BG;
	}
	if (s == Status_Burnt)
	{
		return BRIGHTWHITE_RED_BG;
	}
	if (s == Status_Sabotaged)
	{
		return BLACK_BRIGHTYELLOW_BG;
	}
	if (s == Status_Enchanted)
	{
		return BRIGHTWHITE_PURPLE_BG;
	}
	return NULLCOLOUR;
}

void BattleScene::endBattle()
{
	m_MovesForTurn.clear();
	/*
	CREATE A POST-BATTLE SCENE
	SHOW STATS FROM THE BATTLE
	HERE WILL BE AN OPTION TO GO BACK TO THE MAP
	DELAY BETWEEN LAST HIT AND GOING TO THIS SCREEN, PERHAPS AN ANIMATION
	IF BOSS BATTLE, NEED A WAY TO SHOW THE DEATH ANIMATION THEN A STAGE WIN SCREEN AFTER
	*/
	if (m_Player->getHealth() <= 0)
	{
		m_Player->setHealth(0);
		SydeRogueLikeStatics::toggleFightSuccess(false);
	}
	else
	{
		m_Enemy->setHealth(0);
		SydeRogueLikeStatics::toggleFightSuccess(true);
	}
}

void BattleScene::test()
{
	//m_Enemy = new OrcEnemy(5);

	//m_UIControl.push_back(new SYDELabel("Battle", Vector2(0, 1), Vector2(6, 1), BLACK, true));

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
	std::shared_ptr<Move> PlayerMove;

	if (isItemMove)
	{
		PlayerMove = SydeRogueLikeStatics::getPlayer()->getInventoryAtIndex(selectedMove);
		SydeRogueLikeStatics::getPlayer()->removeInventoryAtIndex(selectedMove);
	}

	else
	{
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
	}

	//GENERATE ENEMY MOVE
	std::shared_ptr<Move> EnemyMove = m_Enemy->determineMove(*m_Player);
	//ADD STATUS AFFECTS NOW
	doStatus(m_Player, false);
	doStatus(m_Enemy, true);
	//DETERMINE THE ORDER OF THE MOVES

	int enemySpeed = m_Enemy->getSpeed() + (((EnemyMove->getType() ==  m_Enemy->getType()) && m_Enemy->getAbility().m_Ability == Ability_Hasten) ? 50 : 0);
	int playerSpeed = m_Player->getSpeed() + (((PlayerMove->getType() == m_Player->getType()) && m_Player->getAbility().m_Ability == Ability_Hasten) ? 50 : 0);

	if (enemySpeed >= playerSpeed && !isItemMove)
	{
		m_MovesForTurn.push_back(MoveTurn(EnemyMove, true));
		m_MovesForTurn.push_back(MoveTurn(PlayerMove, false));
	}
	else
	{
		m_MovesForTurn.push_back(MoveTurn(PlayerMove, false));
		m_MovesForTurn.push_back(MoveTurn(EnemyMove, true));
	}
	//ANY OTHER LOADING
	windowText_Top = "";
	windowText_Bottom = "";
	isItemMove = false;
	validateInventory();
	m_BattleState = m_BS_Prework;
	//FINISH
	m_SceneState = m_BSS_DoMoves;
}

void BattleScene::doStatus(std::shared_ptr<Character> charac, bool enemy)
{
	if (charac->getStatus() == Status_Burnt)
	{
		m_MovesForTurn.push_back(MoveTurn(std::shared_ptr<Move>(new BurntStatus()), enemy));
	}
}

void BattleScene::doSleepStatus(std::shared_ptr<Move>* move, std::shared_ptr<Character> charac)
{
	json tag = charac->getJSONTag();
	if (charac->getStatus() == Status_Sleep)
	{
		*move = std::shared_ptr<Move>(new SleepStatus());
	}
	else if (charac->getStatus() == Status_Sabotaged)
	{
		int Chance = rand() % 100;
		if (Chance > 65)
		{
			*move = std::shared_ptr<Move>(new SabotagedMoveEffect());
		}
	}
}




ConsoleWindow BattleScene::doMoves(ConsoleWindow window)
{
	if (m_BattleState == m_BS_Prework)
	{
		if (m_MovesForTurn.size() == 0)
		{
			m_SceneState = m_BSS_Normal;
			ValidateUI();
			ShowUI();
			return window;
		}
		//CHECK STATUS
		doSleepStatus(&m_MovesForTurn[0].move, m_MovesForTurn[0].enemyTurn ? std::shared_ptr<Character>(m_Enemy) : std::shared_ptr<Character>(m_Player));

		windowText_Top = (m_MovesForTurn[0].enemyTurn ? m_Enemy->getName() : m_Player->getName()) + " Used";
		windowText_Bottom = m_MovesForTurn[0].move->getName();
		//TODO: GET STATUS AND IF FAILED
		//IF MISS, USGAE DECREMENTS
		//IF STATUS AFFECTED, USAGES STAY SAME
		//ELSE ASSUME MOVE WAS USED
		m_MovesForTurn[0].move->decrementUsages();
		std::string moveTag;
		m_Player->validateCurrentJsonTag();
		m_Enemy->validateCurrentJsonTag();
		json player = m_Player->getJSONTag();
		json enemy = m_Enemy->getJSONTag();
		m_MovesForTurn[0].move->resetAnimation();
		m_BattleState = m_BS_Animation;
	}
	else if (m_BattleState == m_BS_StatChangeAnimation)
	{
		window = m_StatChanges[0].animation.draw_asset(window, m_StatChanges[0].isPlayer ? Vector2(46 , 11) : Vector2(17, 2));
		window.setTextAtPoint(m_StatChanges[0].isPlayer ? Vector2(40, m_StatChanges[0].isIncrease? 15 : 14) : Vector2(28, m_StatChanges[0].isIncrease ? 6 : 5), to_string(m_StatChanges[0].amount) + " " + m_StatChanges[0].stat, BRIGHTWHITE);
		if (m_StatChanges[0].animation.getFrame() >= m_StatChanges[0].animation.getFrameSize() - 1)
		{
			m_StatChanges.erase(m_StatChanges.begin());
			if (m_StatChanges.size() == 0)
			{
				m_BattleState = m_BS_Prework;
				return window;
			}
		}

	}
	else if (m_BattleState == m_BS_Animation)
	{
		window = m_MovesForTurn[0].move->drawAnimation(window, Vector2(20, 1));
		if (m_MovesForTurn[0].move->getAnimation().getFrame() >= m_MovesForTurn[0].move->getAnimation().getFrameSize() - 1)
		{
			m_Player->validateCurrentJsonTag();
			StoredStatsObj playStats = StoredStatsObj(m_Player->getAttack(), m_Player->getDefence(), m_Player->getMagicAttack(), m_Player->getMagicDefence(), m_Player->getSpeed());
			m_Enemy->validateCurrentJsonTag();
			StoredStatsObj enemStats = StoredStatsObj(m_Enemy->getAttack(), m_Enemy->getDefence(), m_Enemy->getMagicAttack(), m_Enemy->getMagicDefence(), m_Enemy->getSpeed());
			std::string moveTag;
			json player = m_Player->getJSONTag();
			json enemy = m_Enemy->getJSONTag();
			//ANIMATION DONE
			timeTakenPostWork = 0;
			if (!m_MovesForTurn[0].move->ExecuteMove(
				m_MovesForTurn[0].enemyTurn ? &enemy : &player,
				m_MovesForTurn[0].enemyTurn ? &player : &enemy,
				&moveTag))
			{
				m_MovesForTurn[0].move = std::shared_ptr<Move>(new FailedMove());
			}
			else
			{
				checkTags(moveTag);
				m_MovesForTurn.erase(m_MovesForTurn.begin());
			}

			m_Player->validateFromJson(player);
			m_Enemy->validateFromJson(enemy);

			//CALCULATE ALL STAT CHANGES
			//PUT THEM INTO A LIST OF STRINGS
			addStatChanges(playStats, *m_Player, true);
			addStatChanges(enemStats, *m_Enemy, false);


			//IF ONE PLAYER DEAD
			if (m_Player->getHealth() <= 0 || m_Enemy->getHealth() <= 0)
			{
				endBattle();
				m_SceneState = m_BSS_EndFall;
				return window;
			}
			else if (m_StatChanges.size() != 0)
			{
				m_BattleState = m_BS_StatChangeAnimation;
			}
			else
			{
				m_BattleState = m_BS_Prework;
			}

		}
		else
		{
			for (int i = 0; i < 20; i++)
			{
				window.setTextAtPoint(Vector2(i, 2), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
			}
			for (int i = 0; i < 20; i++)
			{
				window.setTextAtPoint(Vector2(i, 3), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
			}
			window.setTextAtPoint(Vector2(0, 2), windowText_Top, BLACK_BRIGHTWHITE_BG);
			window.setTextAtPoint(Vector2(0, 3), windowText_Bottom, BLACK_BRIGHTWHITE_BG);
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
	for (int i = 0; i < getUISize(); i++)
	{
		if (findLabelInUI("LabelData", i) != std::string::npos)
		{
			int moveIndex = stoi(getLabelInUI(i).substr(getLabelInUI(i).size() - 1, 1));
			setUIText(to_string(m_Player->getMoveAtIndex(moveIndex)->getUsagesLeft()) + "/" + to_string(m_Player->getMoveAtIndex(moveIndex)->getMaxUsages()),i);
		}
		if (findLabelInUI("MoveData", i) != std::string::npos)
		{
			int moveIndex =stoi(getLabelInUI(i).substr(getLabelInUI(i).size() - 1, 1));
			if (moveIndex >= m_Player->getMoves().size())
			{
				setUIEnabled(m_Player->getUsableMoves().size() <= 0 || m_Player->getAbility().m_Ability == Ability_Constant_Struggle, i);
			}
			else
			{
				setUIEnabled(m_Player->getMoveAtIndex(moveIndex)->getUsagesLeft() > 0, i);
			}
		}
	}
}

void BattleScene::addStatChanges(StoredStatsObj obj, Character c, bool isPlayer)
{
	bool increase = false;
	if (obj.atk != c.getAttack())
	{
		increase = obj.atk < c.getAttack();
		m_StatChanges.push_back(StatChangeObj("Attack", abs(obj.atk - c.getAttack()), isPlayer, increase, increase ? m_StatUp : m_StatDown));
	}
	if (obj.def != c.getDefence())
	{
		increase = obj.def < c.getDefence();
		m_StatChanges.push_back(StatChangeObj("Defence", abs(obj.def - c.getDefence()), isPlayer, increase, increase ? m_StatUp : m_StatDown));
	}
	if (obj.mAtk != c.getMagicAttack())
	{
		increase = obj.mAtk < c.getMagicAttack();
		m_StatChanges.push_back(StatChangeObj("M Attack", abs(obj.mAtk - c.getMagicAttack()), isPlayer, increase, increase ? m_StatUp : m_StatDown));
	}
	if (obj.mDef != c.getMagicDefence())
	{
		increase = obj.mDef < c.getMagicDefence();
		m_StatChanges.push_back(StatChangeObj("M Defence", abs(obj.mDef - c.getMagicDefence()), isPlayer, increase, increase ? m_StatUp : m_StatDown));
	}
	if (obj.spd != c.getSpeed())
	{
		increase = obj.spd < c.getSpeed();
		m_StatChanges.push_back(StatChangeObj("Speed", abs(obj.spd - c.getSpeed()), isPlayer, increase, increase ? m_StatUp : m_StatDown));
	}
}
