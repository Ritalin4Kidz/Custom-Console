#include "..\SYDERogueLike\MainMapScene.h"
#pragma once
#include "SYDEQuestGame.h"

#pragma region  StaticInitVars
bool SYDEMapGame::UI_STATE_EVENT = false;
Vector2 SYDEMapGame::camera_Pos = Vector2(0, 0);
Vector2 SYDEMapGame::movement_Pos = Vector2(0, 0);
float SYDEMapGame::movementSpeed = 30.0f;
FightWindow SYDEMapGame::_FWindow = FightWindow();
std::string SYDEMapGame::_AnimHeader = "";
AssetsClass SYDEMapGame::astVars = AssetsClass();
Player SYDEMapGame::m_Player = Player();
//float MainMenuScene::time_passed = 0;;
CustomAnimationAsset MainMenuScene::m_MainMenu_BG = CustomAnimationAsset();
SYDEMenu MainMenuScene::_Options = SYDEMenu();
Player BattleScene::m_Player = Player();
Enemy BattleScene::m_Enemy = Enemy();
SYDEMenu BattleScene::_FightOptions = SYDEMenu();
SYDEMenu BattleScene::_MoveOptions = SYDEMenu();
bool BattleScene::enemy_attack = false;
bool BattleScene::_StatusApplied = false;
int MainMapScene::m_IslandsDeep = 0;

SYDERadialMenu_Basic MainMapScene::m_RadialPause = SYDERadialMenu_Basic();
#pragma endregion

#pragma region MapLoadingVars
bool MainMapScene::hasLoaded = false;
CustomAsset MainMapScene::m_Map = CustomAsset();
CustomAsset MainMapScene::m_bg = CustomAsset();
string MainMapScene::m_IslandBMP = "Start Island";
std::vector<WildFightArea> MainMapScene::_FightingAreas = std::vector<WildFightArea>();
//std::vector<DockArea> MainMapScene::_DockAreas = std::vector<DockArea>();
std::vector<DockChoice> MainMapScene::_DockChoices = std::vector<DockChoice>();
#pragma endregion

#pragma region DockVars
SYDEMenu MainMapScene::_DockOptions = SYDEMenu();
CustomAsset MainMapScene::_DockOptionsUI = CustomAsset();
#pragma endregion

#pragma region StoreVars
SYDEMenu MainMapScene::_ShopOptions = SYDEMenu();
SYDEMenu MainMapScene::_PlayerMenuOptions = SYDEMenu();
std::vector<MoveChoice> MainMapScene::_MoveChoices = std::vector<MoveChoice>();
Move* MainMapScene::_MoveToSwapIn = new Move();
#pragma endregion

#pragma region BossVars
SYDEClock_Timer MainMapScene::m_FireworksTimer = SYDEClock_Timer(0.75f);
SYDEParticleBurst MainMapScene::m_GameOverFireworks = SYDEParticleBurst(Vector2(0, 0), Vector2(-2, -2), Vector2(2, 2));
string MainMapScene::m_BossTAG = "";
ConsoleWindow MainMapScene::windowAtCutsceneTime = ConsoleWindow();
CustomAnimationAsset MainMapScene::m_BossCutscene = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_SMOKE_CRAB_CUTSCENE = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_SMOKE_CRAB_CUTSCENE_WON = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_FREEBEE_CUTSCENE = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_FREEBEE_CUTSCENE_WON = CustomAnimationAsset();
Cutscene_Return_State MainMapScene::m_CSR_State = CSR_MainMap;
bool MainMapScene::isFightingBoss = false;
#pragma endregion



#pragma region SailVars
CustomAnimationAsset MainMapScene::m_SAIL = CustomAnimationAsset();
float MainMapScene::sailingTime = 0.0f;
float MainMapScene::maxSailTime = 5.5f;
//bool MainMapScene::isSailing = false;
#pragma endregion

#pragma region StaticAnimationVars
CustomAnimationAsset SYDEMapGame::m_ORC = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_BLUE_FISH = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_WOLF = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_CRAB = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_SMOKE_CRAB = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_FREEBEE = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_BEE = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_RABBIT = CustomAnimationAsset();
CustomAnimationAsset SYDEMapGame::m_MoveAnimation = CustomAnimationAsset();
#pragma endregion

#pragma region RunVars
MainMapSceneState MainMapScene::_MapState = MState_Normal;
int MainMapScene::gold_from_run = 0;
#pragma endregion


const std::string MAP_BEACHED_BUTTHOLE = "Beached Butthole";
const std::string MAP_BEACHED_ENTRANCE = "Beached Entrance";
const std::string MAP_CAPID_ISLE = "Capid Isle";
const std::string MAP_CAPID_COAST = "Capid Coast";
const std::string MAP_FLOWERED_FIELDS = "Flowered Fields";
const std::string MAP_KELIN_ISLAND = "Kelin Island";
const std::string MAP_MEOW_COAST = "Meow Coast";
const std::string MAP_START_ISLAND = "Start Island";
const std::string MAP_GREYLOT = "Greylot";

void PauseMenuExitFunc()
{
	MainMapScene::setMapState(MState_Normal);
	MainMapScene::DestroyScene(true);
	GameScene::SetScene(MainMenu);
}
void PauseMenuResumeFunc()
{
	MainMapScene::setMapState(MState_Normal);
}


SYDEMapGame::SYDEMapGame()
{
	Bounties::Load();

	m_BLUE_FISH.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BlueFish.bmp", astVars, 40, 100, 10, 10, 0, 39));
	m_ORC.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\TestEnemy.bmp", astVars, 100, 30, 10, 10, 0, 27));
	m_WOLF.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\Wolf.bmp", astVars, 120, 30, 10, 10, 0, 36));
	m_CRAB.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\CrabAnimation.bmp", astVars, 40, 30, 10, 10, 0, 11));
	m_BEE.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BeeEnem.bmp", astVars, 40, 40, 10, 10, 0, 16));
	m_RABBIT.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BunnyAnimation.bmp", astVars, 40, 180, 10, 10, 0, 72));

	m_SMOKE_CRAB.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\CrabAnimationSmoking.bmp", astVars, 40, 130, 10, 10, 0, 51));
	m_SMOKE_CRAB_CUTSCENE.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\SmokingCrabFightCutscene.bmp", astVars, 200, 120, 20, 20, 0, 61));
	m_SMOKE_CRAB_CUTSCENE_WON.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\SmokingCrabDeathCutscene.bmp", astVars, 100, 160, 20, 20, 0, 40));

	m_FREEBEE.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\Freebee.bmp", astVars, 100, 40, 10, 10, 0, 40));
	m_FREEBEE_CUTSCENE.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\FreebeeCutscene.bmp", astVars, 200, 120, 20, 20, 0, 61));
	m_FREEBEE_CUTSCENE_WON.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\FreebeeDeathCutscene.bmp", astVars, 200, 100, 20, 20, 0, 50));
	StatusAnimations::LoadAnimations();

	MainMapScene::m_RadialPause = SYDERadialMenu_Basic(Vector2(20, 10),
	SYDERadialOption("Player", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "P", Vector2(0, 1)),
	SYDERadialOption("???", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "?", Vector2(0, 1)),
	SYDERadialOption("Exit", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "X", Vector2(0, 1), PauseMenuExitFunc),
	SYDERadialOption("Resume", BLACK_BRIGHTWHITE_BG, RED_LIGHTBLUE_BG, "R", Vector2(0, 1), PauseMenuResumeFunc));
}

ConsoleWindow SYDEMapGame::Animation_UI_EVENT(ConsoleWindow window, CustomAnimationAsset& _anim)
{
	window = _anim.draw_asset(window, Vector2(0));
	window.setTextAtPoint(Vector2(0, 1), _AnimHeader, BLACK_BRIGHTWHITE_BG);
	if (_anim.getFrame() == _anim.getFrameSize() - 1)
	{
		UI_STATE_EVENT = false;
	}
	return window;
}

ConsoleWindow SYDEMapGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	try
	{
		if (GameScene::GetSceneTag() != GameScene::GetSceneTagPrev())
		{
			SwitchScene();
			GameScene::SetScenePrev(GameScene::GetSceneTag());
		}
		window = m_Scene->window_draw(window, windowWidth, windowHeight);
		if (UI_STATE_EVENT) {
			window = Animation_UI_EVENT(window, m_MoveAnimation);
		}
	}
	catch(std::exception ex)
	{
		delete m_Scene;
		m_Scene = new MainMenuScene();
		window = m_Scene->window_draw(window, windowWidth, windowHeight);
		//TODO: Display An Error Message
	}
	return window;
}
void SYDEMapGame::SwitchScene()
{
	if (m_Scene != NULL)
	{
		delete m_Scene;
	}
	switch (GameScene::GetSceneTag())
	{
		case MainMenu:
			m_Scene = new MainMenuScene();
			break;
		case Battle:
			m_Scene = new BattleScene();
			break;
		case MainMap:
			m_Scene = new MainMapScene();
			break;
		case LoadingScene:
			m_Scene = new LoadScene(MainMap);
			break;
		case PlayerSelect:
			m_Scene = new BuildCharacter();
			break;
		case MoveSelection:
			m_Scene = new MoveSelectionScene();
			break;
		case TestBuilding:
			m_Scene = new Test_Building();
			break;
		default:
			GameScene::SetScene(MainMenu);
			m_Scene = new MainMenuScene();
			break;
	}
}

BattleScene::BattleScene()
{
	_FightOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("Fight", Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton("Run", Vector2(1, 3), Vector2(20, 1), WHITE, true)
	});

	_FightOptions[0].m_Label = "0";
	_FightOptions[1].m_Label = "1";

	_FightOptions.setActive(true);
	_FightOptions.setPos(Vector2(1, 2));


	for (int i = 0; i < _FightOptions.getSize(); i++)
	{
		_FightOptions[i].setHighLight(RED);
	}
}

ConsoleWindow BattleScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	DeathCheck(window);

	window = fight_header(window, windowWidth, windowHeight);

	if (_FightOptions.getActive() && !SYDEMapGame::UI_STATE_EVENT)
	{
		window = _FightOptions.draw_menu(window);
		if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
		{
			_FightOptions.nextSelect();
		}
		if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
		{
			if (_FightOptions.getSelected().m_Label == "0")
			{
				//_FightOptions.setActive(false);
				_MoveOptions.setActive(true);
			}
			else if (_FightOptions.getSelected().m_Label == "1")
			{
				//IF RUN WAS SUCCESSFUL
				int _chance = std::rand() % 100;
				if (_chance < m_Enemy.getRunChance())
				{
					SYDEMapGame::_FWindow.clear();
					SYDEMapGame::m_Player.setHealth(m_Player.getHealth());

					CleanUpFight(false);

					GameScene::SetScene(MainMap);
				}
				else {
					enemy_attack = true;
					SYDEMapGame::_FWindow.AddFString("Player Failed To Run Away");
				}
			}
		}
	}
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off fight options this frame and allow input next frame
	}
	else if (_MoveOptions.getActive() && !enemy_attack)
	{
		window = _MoveOptions.draw_menu(window);
		if (SYDEMapGame::UI_STATE_EVENT)
		{
			return window;
		}
		if (_StatusApplied)
		{
			DoPlayerAttack(std::stoi((_MoveOptions.getSelected().m_Label)));
		}
		else if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
		{
			_MoveOptions.nextSelect();
		}
		else if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)) && !enemy_attack)
		{
			//BACK OPTION
			bool CanFight;
			if (_MoveOptions.getSelected().m_Label == "5")
			{
				_FightOptions.setActive(true);
				_MoveOptions.setActive(false);
			}
			else if (!DoStatusAnimation(&m_Player,CanFight))
			{
				DoPlayerAttack(std::stoi((_MoveOptions.getSelected().m_Label)));
			}
			else if (_StatusApplied)
			{
				if (!CanFight)
				{
					enemy_attack = true;
					_StatusApplied = false;
				}
			}
		}
	}
	if (enemy_attack && !SYDEMapGame::UI_STATE_EVENT)
	{
		//ENEMY SHOULD DO PROPER ATTACK
		bool CanFight;
		if (_StatusApplied || !DoStatusAnimation(&m_Enemy,CanFight))
		{
			DoEnemyAttack();
		}
		else if (_StatusApplied)
		{
			if (!CanFight)
			{
				enemy_attack = false;
				_StatusApplied = false;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), SYDEMapGame::_FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(m_Player.getHealth()), BRIGHTWHITE);
	return window;
}

ConsoleWindow BattleScene::fight_header(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//WINDOW DRAW
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), m_Enemy.getName(), BLACK_WHITE_BG);
	window = m_Enemy.drawAnimationAsset(window, Vector2(20, 2));
	for (int m = 20; m < windowWidth; m++)
	{
		window.setTextAtPoint(Vector2(m, 11), " ", BLACK_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(20, 11), "Health:" + std::to_string(m_Enemy.getHealth()) + ",LVL:" + std::to_string(m_Enemy.getLevel()), BLACK_WHITE_BG);
	return window;
}

void BattleScene::SetUpFight()
{
	_MoveOptions = SYDEMenu();
	_FightOptions = SYDEMenu();
	_MoveOptions = SYDEMenu(vector<SYDEButton> {
			SYDEButton(m_Player.getMoves()[0]->getName(), Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton(m_Player.getMoves()[1]->getName(), Vector2(1, 3), Vector2(20, 1), WHITE, true),
			SYDEButton(m_Player.getMoves()[2]->getName(), Vector2(1, 4), Vector2(20, 1), WHITE, true),
			SYDEButton(m_Player.getMoves()[3]->getName(), Vector2(1, 5), Vector2(20, 1), WHITE, true),
			SYDEButton(m_Player.getMoves()[4]->getName(), Vector2(1, 6), Vector2(20, 1), WHITE, true),
			SYDEButton("Back", Vector2(1, 7), Vector2(20, 1), WHITE, true)
	});

	_MoveOptions[0].m_Label = "0";
	_MoveOptions[1].m_Label = "1";
	_MoveOptions[2].m_Label = "2";
	_MoveOptions[3].m_Label = "3";
	_MoveOptions[4].m_Label = "4";
	_MoveOptions[5].m_Label = "5";

	_MoveOptions.setActive(false);
	_MoveOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _MoveOptions.getSize(); i++)
	{
		_MoveOptions[i].setHighLight(RED);
	}
	_FightOptions.setActive(true);

	enemy_attack = false;


	_StatusApplied = false;
}

void BattleScene::WonFight(ConsoleWindow window)
{
	//enemy_dead();
	enemy_attack = false;
	_StatusApplied = false;
	if (!SYDEMapGame::UI_STATE_EVENT)
	{
		//END THE FIGHT HERE
		//m_Enemy.ClearMoves();
		//m_Player.ClearMoves();
		SYDEMapGame::m_Player.setHealth(m_Player.getHealth());
		//STATS TOTAL
		SYDEMapGame::m_Player.AddXP((m_Enemy.getLevel() + m_Enemy.getAttack() + m_Enemy.getDefence() + m_Enemy.getMagicAttack() + m_Enemy.getMagicDefence() + m_Enemy.getMaxHealth()), m_Enemy.getStatToIncrease());
		//GOLD RETURNED = LEVEL * 10
		MainMapScene::AddGold((m_Enemy.getLevel() * 10));

		if (MainMapScene::getIsFightingBoss())
		{
			MainMapScene::setBossTag(MainMapScene::getBossTag() + " WON");
			MainMapScene::setIsFightingBoss(false);
			//MainMapScene::clearBossTag();
			if (MainMapScene::getBossTag() == "SMOKING CRAB WON")
			{
				MainMapScene::setUpCutscene(window, CSR_EndGame, false);
			}
			if (MainMapScene::getBossTag() == "FREEBEE WON")
			{
				MainMapScene::setUpCutscene(window, CSR_EndGame, false);
			}


			if (MainMapScene::getCSR() == CSR_EndGame)
				CleanUpFight(true);
			else
				CleanUpFight(false);
		}
		else
		{
			CleanUpFight(false);
		}

		GameScene::SetScene(MainMap);
		SYDEMapGame::_FWindow.clear();
	}
}

void BattleScene::Handle_Fight_Tags(Character* c)
{
	json j;
	if (c->getJSONTag() != "")
	{
		j = json::parse(c->getJSONTag());
	}
	else
		return;

	if (j.find("Marked") != j.end())
	{
		if (j["Marked"] == 1)
		{
			if (c->getDefence() > Player::getMinimumDefence())
			{
				c->setDefence(c->getDefence() - 10);
				if (c->getDefence() < Player::getMinimumDefence())
				{
					c->setDefence(Player::getMinimumDefence());
				}
			}
		}
	}


	std::string jsonData = j.dump();
	c->setJSONTag(jsonData);

}

void BattleScene::Handle_Player_Abilities(Character* c)
{
	if (c->getAbility() == Ability_Hasten)
		c->setSpeed(c->getSpeed() + 10);

	else if (c->getAbility() == Ability_Insomnia && c->getStatus() == Status_Sleep)
	{
		c->setStatus(Status_None);
	}
}

void BattleScene::DeathCheck(ConsoleWindow window)
{
	//DEATH CHECKS
	if (m_Enemy.getHealth() <= 0)
	{
		//enemy_dead();
		WonFight(window);
		//return window;
	}
	if (m_Player.getHealth() <= 0)
	{
		_StatusApplied = false;
		if (!SYDEMapGame::UI_STATE_EVENT)
		{
			CleanUpFight(true);

			GameScene::SetScene(MainMenu);
		}
		//return window;
	}
}

void BattleScene::CleanUpFight(bool PlayerDead)
{
	enemy_attack = false;
	if (PlayerDead)
		m_Player.ClearMoves();

	m_Enemy.ClearMoves();
	SYDEMapGame::_FWindow.clear();
}

bool BattleScene::DoStatusAnimation(Character* c, bool& CanFight)
{	
	//Player Abilities
	Handle_Player_Abilities(c);
	/*
	DO ALL JSON STUFF HERE
	*/
	Handle_Fight_Tags(c);

	if (_StatusApplied)
	{
		return false;
	}
	_StatusApplied = true;
	_SQStatus s = c->getStatus();
	if (s == Status_None)
	{
		return false;
	}
	int Chance_One = 0;
	int Chance_Two = 0;

	//E.G. Standard Speed = 30
	/*
	100 / 30 = 3.3 = 3
	Faster Speed 
	Faster speeds have higher chance of ignoring status
	*/

	int StandardChance = (100/c->getSpeed());
	if (StandardChance == 0)
		StandardChance = 1;
	switch (s)
	{
		case Status_Frozen:
			Chance_One = rand() % StandardChance;
			Chance_Two = rand() % StandardChance;
			if (Chance_One == Chance_Two)
			{
				c->clearStatus();
				SYDEMapGame::setAnimation_UI_EVENT(StatusAnimations::m_ThawedAnimation, c->getName() + " Has Thawed");
				SYDEMapGame::_FWindow.AddFString(c->getName() + " Has Thawed Out");
			}
			else
			{
				SYDEMapGame::setAnimation_UI_EVENT(StatusAnimations::m_FrozenAnimation, c->getName() + " Is Frozen Solid");
			}
			CanFight = false;
			return true;
		case Status_Sleep:
			Chance_One = rand() % StandardChance;
			Chance_Two = rand() % StandardChance;
			if (Chance_One == Chance_Two)
			{
				c->clearStatus();
				SYDEMapGame::setAnimation_UI_EVENT(StatusAnimations::m_AwakeAnimation, c->getName() + " Has Woken Up");
				SYDEMapGame::_FWindow.AddFString(c->getName() + " Has Woken Up");
				CanFight = true;
			}
			else
			{
				SYDEMapGame::setAnimation_UI_EVENT(StatusAnimations::m_SleepAnimation, c->getName() + " Is Asleep");
				CanFight = false;
			}
			return true;
		case Status_Burnt:
			SYDEMapGame::setAnimation_UI_EVENT(StatusAnimations::m_BurntAnimation, c->getName() + " Is Burning");
			c->AddHealth(-(c->getMaxHealth()/15));
			CanFight = true;
			return true;
		case Status_Paralyzed:
			SYDEMapGame::setAnimation_UI_EVENT(StatusAnimations::m_ParalyzedAnimation, c->getName() + " Is Paralyzed");
			Chance_One = rand() % StandardChance;
			Chance_Two = rand() % StandardChance;
			if (Chance_One == Chance_Two)
			{
				CanFight = true;
			}
			else 
			{
				CanFight = false;
			}
			return true;
	}
	return false;
}

void BattleScene::DoPlayerAttack(int i)
{
	SYDEMapGame::setAnimation_UI_EVENT(m_Player.getMoves()[i]->getAnimation(), "Player Used " + m_Player.getMoves()[i]->getName());
	m_Player.getMoves()[i]->Execute(&m_Player, &m_Enemy, &SYDEMapGame::_FWindow);
	enemy_attack = true;
	_StatusApplied = false;
}

void BattleScene::DoEnemyAttack()
{
	int EnemyMove = rand() % m_Enemy.getMoves().size();
	SYDEMapGame::setAnimation_UI_EVENT(m_Enemy.getMoves()[EnemyMove]->getAnimation(), m_Enemy.getName() + " Used " + m_Enemy.getMoves()[EnemyMove]->getName());
	m_Enemy.getMoves()[EnemyMove]->Execute(&m_Enemy, &m_Player, &SYDEMapGame::_FWindow);
	enemy_attack = false;
	_StatusApplied = false;
}

MainMenuScene::MainMenuScene()
{
	m_MainMenu_BG.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\MainMenuAnim.bmp", SYDEMapGame::astVars, 100, 180, 20, 20, 0, 45));
	m_MainMenu_BG.setLooping(true);

	m_MainMenu_BG.setMaxDeltatime(0.15f);

	_Options = SYDEMenu();
	_Options = SYDEMenu(vector<SYDEButton> {
		SYDEButton("", Vector2(0, 2), Vector2(30, 1), WHITE, true),
			SYDEButton("", Vector2(0, 3), Vector2(20, 1), WHITE, true),
			//SYDEButton("", Vector2(0, 4), Vector2(20, 1), WHITE, true),
			//SYDEButton("", Vector2(0, 5), Vector2(20, 1), WHITE, true)
	});

	_Options[0].m_Label = "0";
	_Options[1].m_Label = "1";
	//_Options[2].m_Label = "2";
	//_Options[3].m_Label = "3";

	//_Options[0].setText("Continue");
	_Options[0].setText("New Game");
	//_Options[2].setText("Controls");
	_Options[1].setText("Exit Game");

	_Options.setActive(true);
	_Options.setPos(Vector2(0, 1));
	for (int i = 0; i < _Options.getSize(); i++)
	{
		_Options[i].setHighLight(RED);
	}
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::BattleTestSetup()
{
	//Battle Test
	Enemy orc;
	orc.SetAnimation(SYDEMapGame::m_ORC);
	orc.setName("Test Orc");
	orc.setMaxHealth(100);
	orc.setHealth(100);
	orc.setLevel(5);
	orc.setType(Grass);
	orc.SetMoves(std::vector<Move*>{ new Water_Blast(), new Smoke_Break(), new Smoke_Cloud(), new Slash(), new Bone_Club() });
	SYDEMapGame::m_Player.setMaxHealth(100);
	SYDEMapGame::m_Player.setHealth(100);
	SYDEMapGame::m_Player.setAttack(2);
	SYDEMapGame::m_Player.setType(Water);
	SYDEMapGame::m_Player.SetMoves(std::vector<Move*>{ new Water_Slime(), new Entangle(), new Sudden_Cold(), new Fireball(), new Lightning_Slime() });
	SYDEMapGame::m_Player.setLevel(5);
	BattleScene::setEnemy(orc);
	BattleScene::setPlayer(SYDEMapGame::m_Player);
	BattleScene::SetUpFight();
	GameScene::SetScene(Battle);
}

void MainMenuScene::MainMapTestSetup()
{
	SYDEMapGame::camera_Pos = Vector2(74,45 );
	GameScene::SetScene(LoadingScene);

	SYDEMapGame::m_Player.setMaxHealth(100);
	SYDEMapGame::m_Player.setHealth(100);
	SYDEMapGame::m_Player.setAttack(2);
	SYDEMapGame::m_Player.setType(Water);
	SYDEMapGame::m_Player.setName("Rit@lin");
	SYDEMapGame::m_Player.SetMoves(std::vector<Move*>{ new Flashbang(), new Rainbow(), new Lightning_Punch(), new Fireball(), new Knights_Sword() });
	SYDEMapGame::m_Player.setLevel(5);
}

void MainMenuScene::BuildingTestSetup()
{
	SYDEMapGame::camera_Pos = Vector2(0, 0);
	GameScene::SetScene(TestBuilding);

	SYDEMapGame::m_Player.setMaxHealth(100);
	SYDEMapGame::m_Player.setHealth(100);
	SYDEMapGame::m_Player.setAttack(2);
	SYDEMapGame::m_Player.setType(Water);
	SYDEMapGame::m_Player.setName("Rit@lin");
	SYDEMapGame::m_Player.SetMoves(std::vector<Move*>{ new Flashbang(), new Rainbow(), new Lightning_Punch(), new Fireball(), new Knights_Sword() });
	SYDEMapGame::m_Player.setLevel(5);
}

ConsoleWindow MainMenuScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_MainMenu_BG.draw_asset(window, Vector2(0, 0));
	window = _Options.draw_menu(window);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_Options.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		//if (_Options.getSelected().m_Label == "0")
		//{
		//	//BattleTestSetup();
		//	BuildingTestSetup();
		//}
		if (_Options.getSelected().m_Label == "0")
		{
			//MainMapTestSetup();
			MainMapScene::RefreshRun();
			MainMapScene::RefreshStartIsland();

			GameScene::SetScene(PlayerSelect);
		}
		else if (_Options.getSelected().m_Label == "1")
		{
			exit(NULL);
		}
	}
	window.setTextAtPoint(Vector2(15, 1), "SYDE QUEST", RED_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(0, 19), "TAB - CYCLE OPTIONS, SPACE - SELECT           ", BLACK_BRIGHTWHITE_BG);
	return window;
}

void FightWindow::AddFString(string fstring)
{
	if (_fightStrings.size() >= 8)
	{
		for (int i = 1; i < 8; i++)
		{
			_fightStrings[i - 1] = _fightStrings[i];
		}
		_fightStrings[7] = fstring;
	}
	else {
		_fightStrings.push_back(fstring);
	}
}

MainMapScene::MainMapScene()
{
	m_FireworksTimer.SetFunc(TickFunc);
	LoadGameScene();

	m_SAIL.setMaxDeltatime(0.05f);

	///
	/*
	_LevelAsset.setCharAtPoint(m_Point, WildFightChar);
	_LevelAsset.setColourAtPoint(m_Point, 32);
	*/
}

MainMapScene::~MainMapScene()
{
	_FightingAreas.clear();
	//_DockAreas.clear();
	DeleteMoveChoices();
}

void MainMapScene::LoadGameScene()
{
	if (!hasLoaded)
	{
		_FightingAreas = std::vector<WildFightArea>();
		m_bg = CustomAsset(60, 30, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
		_DockOptionsUI = CustomAsset(40, 20, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\UI\\DockMenu.bmp", 20, 20));
		m_SAIL.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\SailingAnimation.bmp", SYDEMapGame::astVars, 160, 20, 20, 20, 0, 8));
		m_SAIL.setLooping(true);
		string IslandBmp = "EngineFiles\\Bitmaps\\Islands\\" + m_IslandBMP + ".bmp";
		string IslandOverlay = "EngineFiles\\Bitmaps\\WildSpawns\\" + m_IslandBMP + "_WildSpawns.bmp";
		wstring wIslandBmp = wstring(IslandBmp.begin(), IslandBmp.end());
		wstring wIslandOverlay = wstring(IslandOverlay.begin(), IslandOverlay.end());
		//m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\StartIsland.bmp", 100, 100));
		m_Map = CustomAsset(200, 100, SYDEMapGame::astVars.get_bmp_as_direct_colour_class_array((WCHAR*)wIslandBmp.c_str(), 100, 100));
		Bitmap* SpawnData = new Bitmap((WCHAR*)wIslandOverlay.c_str(), FALSE);
		for (int i = 0; i < 100; i++)
		{
			for (int ii = 0; ii < 100; ii++)
			{
				Gdiplus::Color* pixelColor = new Gdiplus::Color();
				SpawnData->GetPixel(ii + 1, i, pixelColor);
				AddEnemy(Vector2(ii * 2, i), *pixelColor);
				delete[] pixelColor;
			}
		}
		m_IslandsDeep++;
		RefreshDockChoices();
		RefreshMoveChoices();
		delete[] SpawnData;
		//SpawnData.~Bitmap();
		hasLoaded = true;
	}
}

void MainMapScene::DestroyScene(bool quitGame)
{
	_FightingAreas.clear();
	//_DockAreas.clear();
	//_MoveChoices.clear();
	m_Map.ClearAsset();
	_DockChoices.clear();
	DeleteMoveChoices();
	if (quitGame)
	{
		m_SAIL.ClearAsset();
		BattleScene::CleanUpFight(true);
	}

	hasLoaded = false;
}

ConsoleWindow MainMapScene::Selecting(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window =_DockOptionsUI.draw_asset(window, Vector2(0, 0));
	window = _DockOptions.draw_menu(window);
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", WHITE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 19), "Level: " + to_string(SYDEMapGame::m_Player.getLevel()) + ", HP: " + to_string(SYDEMapGame::m_Player.getHealth()) + "/" + to_string(SYDEMapGame::m_Player.getMaxHealth()) + ", Gold: " + to_string(gold_from_run), RED_WHITE_BG);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_DockOptions.nextSelect();
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		_MapState = MState_Normal;
		if (_DockOptions[_DockOptions.getSelectedNumber()].m_Label != "ExitDockMenu")
		{
			if (gold_from_run >= _DockChoices[_DockOptions.getSelectedNumber()].FerryCost)
			{
				gold_from_run -= _DockChoices[_DockOptions.getSelectedNumber()].FerryCost;
				DestroyScene(false);
				setSail(_DockOptions[_DockOptions.getSelectedNumber()].m_Label);
			}
		}
		return window;
	}
	return window;
}

ConsoleWindow MainMapScene::Sailing(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_SAIL.draw_asset(window, Vector2(0, 0));
	sailingTime += SYDEDefaults::getDeltaTime();
	window.setTextAtPoint(Vector2(0, 1), "Traveling To '" + m_IslandBMP + "'", BLACK_WHITE_BG);
	if (sailingTime >= maxSailTime)
	{
		_MapState = MState_Normal;
		LoadGameScene();
	}
	return window;
}

ConsoleWindow MainMapScene::Shopping(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = _DockOptionsUI.draw_asset(window, Vector2(0, 0));
	window = _ShopOptions.draw_menu(window);
	bool PlayerHasMove = false;
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", WHITE_WHITE_BG);
	}
	if (_ShopOptions[_ShopOptions.getSelectedNumber()].m_Label == "ExitMenu")
	{
		window.setTextAtPoint(Vector2(0, 19), "Level: " + to_string(SYDEMapGame::m_Player.getLevel()) + ", HP: " + to_string(SYDEMapGame::m_Player.getHealth()) + "/" + to_string(SYDEMapGame::m_Player.getMaxHealth()) + ", Gold: " + to_string(gold_from_run), RED_WHITE_BG);
	}
	else
	{
		PlayerHasMove = SYDEMapGame::m_Player.HasMove(_MoveChoices[_ShopOptions.getSelectedNumber()].m_Move->getMoveInt());
		if (_MoveChoices[_ShopOptions.getSelectedNumber()].m_Move->getIfTeachable(SYDEMapGame::m_Player.getType()) && !PlayerHasMove)
		{
			window.setTextAtPoint(Vector2(0, 19), "CAN LEARN MOVE", RED_WHITE_BG);
		}
		else if (PlayerHasMove)
		{
			window.setTextAtPoint(Vector2(0, 19), "MOVE ALREADY LEARNED", RED_WHITE_BG);
		}
		else 
		{
			window.setTextAtPoint(Vector2(0, 19), "NOT LEARNABLE", RED_WHITE_BG);
		}
	}
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_ShopOptions.nextSelect();
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		_MapState = MState_Normal;
		//IF WE TRYING TO BUY AN ITEM WE CAN
		if (_ShopOptions[_ShopOptions.getSelectedNumber()].m_Label != "ExitMenu" 
			&& _ShopOptions[_ShopOptions.getSelectedNumber()].m_Label != "LOCKED" 
			&& _MoveChoices[_ShopOptions.getSelectedNumber()].m_Move->getIfTeachable(SYDEMapGame::m_Player.getType())
			&& !PlayerHasMove)
		{
			if (gold_from_run >= _MoveChoices[_ShopOptions.getSelectedNumber()].m_Cost)
			{
				gold_from_run -= _MoveChoices[_ShopOptions.getSelectedNumber()].m_Cost;
				_MoveToSwapIn = _MoveChoices[_ShopOptions.getSelectedNumber()].m_Move;
				_ShopOptions[_ShopOptions.getSelectedNumber()].m_Text = "---BOUGHT---";
				_ShopOptions[_ShopOptions.getSelectedNumber()].m_Label = "LOCKED";
				//GO TO SWAP SCENE
				RefreshPlayerMenuChoices();
				_MapState = MState_MoveSwap;
			}
		}
		return window;
	}
	return window;
}

ConsoleWindow MainMapScene::Building(ConsoleWindow window, int windowWidth, int windowHeight)
{
	return window;
}

ConsoleWindow MainMapScene::MoveSwap(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	window.setTextAtPoint(Vector2(13, 1), "MOVE SELECTION", BLACK_WHITE_BG);

	window = _PlayerMenuOptions.draw_menu(window);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_PlayerMenuOptions.nextSelect();
		//json j = json::parse(_MoveOptions.getSelected().m_Label);
		//mvs = MoveStats(j);
	}
	window.setTextAtPoint(Vector2(2, 13), "MOVE STATS:", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(2, 14), "MOVE: " + SYDEMapGame::m_Player.getMoveAtIndex(_PlayerMenuOptions.getSelectedNumber())->getName(), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(2, 15), "TYPE: " + SQFunctions::TypeToString(SYDEMapGame::m_Player.getMoveAtIndex(_PlayerMenuOptions.getSelectedNumber())->getType()), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(2, 16), "POWER: " + std::to_string(SYDEMapGame::m_Player.getMoveAtIndex(_PlayerMenuOptions.getSelectedNumber())->getPower()), BLACK_WHITE_BG);
	if (SYDEKeyCode::get_key('I')._CompareState(KEYDOWN))
	{
		GameScene::SetScene(MainMap);
		return window;
	}
	else if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		SYDEMapGame::m_Player.SetMoveAtIndex(_PlayerMenuOptions.getSelectedNumber(), _MoveToSwapIn);
		_MapState = MState_Normal;
		return window;
	}
	return window;
}

ConsoleWindow MainMapScene::GameWon(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = windowAtCutsceneTime;
	m_GameOverFireworks.draw(window);
	m_FireworksTimer.Tick();
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", WHITE_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 19), "YOU WIN: Press Space To Return To Menu", RED_WHITE_BG);
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		_MapState = MState_Normal;
		DestroyScene(true);
		GameScene::SetScene(MainMenu);
		return window;
	}
	return window;
}

ConsoleWindow MainMapScene::Paused(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_RadialPause.draw_ui(window);
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", WHITE_WHITE_BG);
	}
	return window;
}

ConsoleWindow MainMapScene::BossCutscene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	std::string str = "";
	json j;
	Enemy _skcb;
	window = windowAtCutsceneTime;
	window = m_BossCutscene.draw_asset(window, Vector2(0, 0));
	if (m_BossCutscene.getFrame() >= m_BossCutscene.getFrameSize() -1)
	{
		switch (m_CSR_State)
		{
		case CSR_BossFight:
			//SET UP FIGHT
			if (m_BossTAG == "SMOKING CRAB")
			{
				json JsonData;
				Enemy* e = new Smoking_Crab(20);
				e->to_json(JsonData);
				str = JsonData.dump();
				delete e;
			}
			else if (m_BossTAG == "FREEBEE")
			{
				json JsonData;
				Enemy* e = new Freebee(20);
				e->to_json(JsonData);
				str = JsonData.dump();
				delete e;
			}
			j = json::parse(str);
			_skcb.from_json(j);
			SetEnemyFromTag(_skcb);
			_MapState = MState_Normal;
			BattleScene::setEnemy(_skcb);
			BattleScene::setPlayer(SYDEMapGame::m_Player);
			BattleScene::SetUpFight();
			GameScene::SetScene(Battle);
			isFightingBoss = true;
			break;
		case CSR_EndGame:
			m_GameOverFireworks.setColour(YELLOW);
			m_GameOverFireworks.setCharacter("*");
			m_GameOverFireworks.RainbowOn(true);
			m_GameOverFireworks.setMaxParticles(35);
			m_GameOverFireworks.setFinishingColour(WHITE);
			clearBossTag();
			_MapState = MState_GameWon;
			break;
		case CSR_MainMap:
		default:
			_MapState = MState_Normal;
			break;
		}
	}
	return window;
}


void MainMapScene::setUpCutscene(ConsoleWindow window, Cutscene_Return_State csr, bool getWindow)
{

	AddBlankChar(SYDEMapGame::camera_Pos, window.determineColourAtPoint(SYDEMapGame::camera_Pos, BLACK, true));
	if (getWindow) { windowAtCutsceneTime = window; }
	if (m_BossTAG == "SMOKING CRAB")
	{
		m_BossCutscene = SYDEMapGame::m_SMOKE_CRAB_CUTSCENE;
	}
	else if (m_BossTAG == "SMOKING CRAB WON")
	{
		Bounties::UnlockBounty("Crab Unlocked", Bounties::CrabBounty_Unlocked);
		m_BossCutscene = SYDEMapGame::m_SMOKE_CRAB_CUTSCENE_WON;
	}
	else if (m_BossTAG == "FREEBEE")
	{
		m_BossCutscene = SYDEMapGame::m_FREEBEE_CUTSCENE;
	}
	else if (m_BossTAG == "FREEBEE WON")
	{
		m_BossCutscene = SYDEMapGame::m_FREEBEE_CUTSCENE_WON;
	}
	m_BossCutscene.setPaused(false);
	m_BossCutscene.setFrame(0);
	_MapState = MState_Cutscene;
	m_CSR_State = csr;
}

void TickFunc()
{
	if (MainMapScene::m_GameOverFireworks.isDead())
	{
		float _x = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40 - 0)));
		float _y = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (19 - 0)));
		MainMapScene::m_GameOverFireworks.setPos(Vector2(_x, _y));
		MainMapScene::m_GameOverFireworks.burst();
	}
}

ConsoleWindow MainMapScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (_MapState == MState_Docking) { return Selecting(window, windowWidth, windowHeight); }
	if (_MapState == MState_Sailing) { return Sailing(window, windowWidth, windowHeight); }
	if (_MapState == MState_Shopping) { return Shopping(window, windowWidth, windowHeight); }
	if (_MapState == MState_MoveSwap) { return MoveSwap(window, windowWidth, windowHeight); }
	if (_MapState == MState_Cutscene) {return BossCutscene(window, windowWidth, windowHeight);}
	if (_MapState == MState_GameWon) { return GameWon(window, windowWidth, windowHeight); }

	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = m_Map.draw_asset(window, Vector2(SYDEMapGame::camera_Pos.getX() - 20, SYDEMapGame::camera_Pos.getY() - 10), windowWidth, windowHeight);

	if (_MapState == MState_Paused) { return Paused(window, windowWidth, windowHeight); }
	float _dt = SYDEDefaults::getDeltaTime() * SYDEMapGame::movementSpeed;
	Vector2 MovementBuffer(0);
	//PlayerPos
	window.setTextAtPoint(Vector2(20, 10), "><", window.determineColourAtPoint(Vector2(20, 10), BLACK, true));
	char tempChar = m_Map.getCharAtPoint(SYDEMapGame::camera_Pos);
	//BOSS FIGHT
	if (tempChar == '.')
	{
		setUpCutscene(window, CSR_BossFight, true);
		return window;
	}
	//if (SYDEKeyCode::get_key('I')._CompareState(KEYDOWN))
	//{
	//	GameScene::SetScene(MoveSelection);
	//	return window;
	//}
	if (SYDEKeyCode::get_key('P')._CompareState(KEYDOWN))
	{
		_MapState = MState_Paused;
		return window;
	}
	if (SYDEKeyCode::get_key('S')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20 + MovementBuffer.getX(), 11 + MovementBuffer.getY())));
		if ((temp.compare("17") != 0 && temp.compare("16") != 0))
		{
			SYDEMapGame::movement_Pos.addY(1 * _dt);
			if (SYDEMapGame::movement_Pos.getY() > 1)
			{
				SYDEMapGame::movement_Pos.addY(-1);
				SYDEMapGame::camera_Pos.addY(1);
				MovementBuffer.addY(1);
			}
			else {
				MovementBuffer.addY(1 * _dt);
			}
		}
		int WFA = CheckWFA(tempChar);
		if (WFA == 1) { return window; }
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20 + MovementBuffer.getX(), 9 + MovementBuffer.getY())));
		if ((temp.compare("17") != 0 && temp.compare("16") != 0))
		{
			SYDEMapGame::movement_Pos.addY(-1 * _dt);
			if (SYDEMapGame::movement_Pos.getY() < -1)
			{
				SYDEMapGame::movement_Pos.addY(1);
				SYDEMapGame::camera_Pos.addY(-1);
				MovementBuffer.addY(-1);
			}
			else {
				MovementBuffer.addY(-1 * _dt);
			}
		}
		int WFA = CheckWFA(tempChar);
		if (WFA == 1) { return window; }
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(22 + MovementBuffer.getX(), 10 + MovementBuffer.getY())));
		if ((temp.compare("17") != 0 && temp.compare("16") != 0))
		{
			SYDEMapGame::movement_Pos.addX(2 * _dt);
			if (SYDEMapGame::movement_Pos.getX() > 2)
			{
				SYDEMapGame::movement_Pos.addX(-2);
				SYDEMapGame::camera_Pos.addX(2);
				MovementBuffer.addX(2);
			}
			else {
				MovementBuffer.addX(2 * _dt);
			}
		}
		int WFA = CheckWFA(tempChar);
		if (WFA == 1) { return window; }
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(18 + MovementBuffer.getX(), 10 + MovementBuffer.getY())));
		if ((temp.compare("17") != 0 && temp.compare("16") != 0))
		{
			SYDEMapGame::movement_Pos.addX(-2 * _dt);
			if (SYDEMapGame::movement_Pos.getX() < -2)
			{
				SYDEMapGame::movement_Pos.addX(2);
				SYDEMapGame::camera_Pos.addX(-2);
				MovementBuffer.addX(-2);
			}
			else {
				MovementBuffer.addX(-2 * _dt);
			}
		}
		int WFA = CheckWFA(tempChar);
		if (WFA == 1) { return window; }
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		//DOCK
		if (tempChar == '-')
		{
			//NEEDS TO BE CHANGED TO A MENU OF THREE CHOICES
			_DockOptions.setActive(true);
			_MapState = MState_Docking;
			return window;
		}
		//Shop
		else if (tempChar == '=')
		{
			//NEEDS TO BE CHANGED TO A MENU OF THREE CHOICES
			_ShopOptions.setActive(true);
			_MapState = MState_Shopping;
			return window;
		}
	}
	window.setTextAtPoint(Vector2(0, 1), m_IslandBMP, RED_WHITE_BG);
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", WHITE_WHITE_BG);
	}
	if (tempChar == '-')
	{
		window.setTextAtPoint(Vector2(0, 19), "Dock: Press Space To Travel", RED_WHITE_BG);
	}
	else
	{
		window.setTextAtPoint(Vector2(0, 19), "Level: " + to_string(SYDEMapGame::m_Player.getLevel()) + ", HP: " + to_string(SYDEMapGame::m_Player.getHealth()) + "/" + to_string(SYDEMapGame::m_Player.getMaxHealth()) + ", Gold: " + to_string(gold_from_run), RED_WHITE_BG);
	}
	return window;
}

int MainMapScene::AddEnemy(Vector2 pixelLoc, Gdiplus::Color pixelColour)
{
	//ADD FLOWERS
	if (pixelColour.GetRed() == 243 && pixelColour.GetGreen() == 21 && pixelColour.GetBlue() == 246)
	{
		AddFlowerChar(pixelLoc);
		return 1;
	}
	//ADD START
	if (pixelColour.GetRed() == 12 && pixelColour.GetGreen() == 12 && pixelColour.GetBlue() == 12)
	{
		SYDEMapGame::camera_Pos = pixelLoc;
		return 1;
	}
	//ADD DOCK
	if (pixelColour.GetRed() == 193 && pixelColour.GetGreen() == 156 && pixelColour.GetBlue() == 0)
	{
		AddDockChar(pixelLoc, '-');
	}
	//ADD SHOP
	else if (pixelColour.GetRed() == 56 && pixelColour.GetGreen() == 104 && pixelColour.GetBlue() == 104)
	{
		AddShopChar(pixelLoc, '=');
	}
#pragma endregion
#pragma region EnemiesStructured
	//CODE R = Type / 115 = Enemy
	//CODE G = Level Minimum
	//CODE B = Pool Of Enemies To Spawn From
	else if (pixelColour.GetRed() == 115)
	{
		json JsonData;
		std::string str = "";
		//Enemy* e = new Bee(3 + (rand() % 5));
		Enemy * e = getRandomEnemyFromPool(pixelColour.GetBlue(), pixelColour.GetGreen());
		e->to_json(JsonData);
		str = JsonData.dump();
		delete e;
		AddWildChar(pixelLoc, 'v', str, BLACK_GREEN_BG);
	}
#pragma endregion

	//SMOKING CRAB
	else if (pixelColour.GetRed() == 218 && pixelColour.GetGreen() == 4 && pixelColour.GetBlue() == 246)
	{
		m_BossTAG = "SMOKING CRAB";
		AddBossChar(pixelLoc, BLACK_LIGHTGREY_BG);
	}
	else if (pixelColour.GetRed() == 21 && pixelColour.GetGreen() == 143 && pixelColour.GetBlue() == 246)
	{
		m_BossTAG = "FREEBEE";
		AddBossChar(pixelLoc, BLACK_LIGHTGREY_BG);
	}
	return 0;
}

std::string MainMapScene::getEnemy(Vector2 loc)
{
	for (int i = 0; i < _FightingAreas.size(); i++)
	{
		if (_FightingAreas[i].m_Loc == loc)
		{
			return _FightingAreas[i].wfa_EnemyStr;
		}
	}
	//FIRST ENEMY IN LIST AS A DEFAULT (STOPS CRASH)
	return _FightingAreas[0].wfa_EnemyStr;
}

vector<string> SYDEMapGame::Split(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}

CustomAnimationAsset SYDEMapGame::StringToAnimation(std::string s)
{
	if (s == "ORC")
		return m_ORC;
	else if (s == "BLUE_FISH")
		return m_BLUE_FISH;
	else if (s == "WOLF")
		return m_WOLF;
	else if (s == "CRAB")
		return m_CRAB;
	else if (s == "BEE")
		return m_BEE;
	else if (s == "RABBIT")
		return m_RABBIT;
	else if (s == "SMOKE_CRAB")
		return m_SMOKE_CRAB;
	else if (s == "FREEBEE")
		return m_FREEBEE;
	return m_ORC;
}

void MainMapScene::AddWildChar(Vector2 loc, char ico, std::string data, int col)
{
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, col);
	_FightingAreas.push_back({ WildFightArea(loc, data) });
	loc.addX(1);
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, col);
}

void MainMapScene::AddDockChar(Vector2 loc, char ico)
{
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, BLACK_YELLOW_BG);
	//_DockAreas.push_back({ DockArea(loc) });
	loc.addX(1);
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, BLACK_YELLOW_BG);
}

void MainMapScene::AddShopChar(Vector2 loc, char ico)
{
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, BLUE_LIGHTBLUE_BG);
	loc.addX(1);
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, BLUE_LIGHTBLUE_BG);
}

void MainMapScene::AddBossChar(Vector2 loc, int col)
{
	m_Map.setCharAtPoint(loc, '.');
	m_Map.setColourAtPoint(loc, col);
	loc.addX(1);
	m_Map.setCharAtPoint(loc, '.');
	m_Map.setColourAtPoint(loc, col);
}

void MainMapScene::AddBlankChar(Vector2 loc, int col)
{
	m_Map.setCharAtPoint(loc, ' ');
	m_Map.setColourAtPoint(loc, col);
	loc.addX(1);
	m_Map.setCharAtPoint(loc, ' ');
	m_Map.setColourAtPoint(loc, col);
}

void MainMapScene::AddFlowerChar(Vector2 loc)
{
	int col = randomFlowerColour();
	m_Map.setCharAtPoint(loc, '*');
	m_Map.setColourAtPoint(loc, col);
	loc.addX(1);
	m_Map.setCharAtPoint(loc, '*');
	m_Map.setColourAtPoint(loc, col);
}

void MainMapScene::AddBuildingChar(Vector2 loc, char ico, std::string data)
{
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, BLACK_LIGHTBLUE_BG);
	//_DockAreas.push_back({ DockArea(loc) });
	loc.addX(1);
	m_Map.setCharAtPoint(loc, ico);
	m_Map.setColourAtPoint(loc, BLACK_LIGHTBLUE_BG);
}

void MainMapScene::RefreshDockChoices()
{
	_DockChoices.clear();
	if (m_IslandBMP == MAP_START_ISLAND)
	{
		_DockChoices.push_back(DockChoice(MAP_KELIN_ISLAND, 100));
		_DockChoices.push_back(DockChoice(MAP_CAPID_ISLE, 150));
		_DockChoices.push_back(DockChoice(MAP_MEOW_COAST, 50));
	}
	if (m_IslandBMP == MAP_KELIN_ISLAND)
	{
		_DockChoices.push_back(DockChoice(MAP_BEACHED_ENTRANCE, 125));
		_DockChoices.push_back(DockChoice(MAP_GREYLOT, 250));
	}
	if (m_IslandBMP == MAP_BEACHED_ENTRANCE)
	{
		_DockChoices.push_back(DockChoice(MAP_BEACHED_BUTTHOLE, 225));
	}
	if (m_IslandBMP == MAP_CAPID_ISLE)
	{
		_DockChoices.push_back(DockChoice(MAP_FLOWERED_FIELDS, 225));
	}
	if (m_IslandBMP == MAP_MEOW_COAST)
	{
		_DockChoices.push_back(DockChoice(MAP_FLOWERED_FIELDS, 275));
		_DockChoices.push_back(DockChoice(MAP_CAPID_COAST, 200));
	}

	_DockOptions = SYDEMenu();
	if (_DockChoices.size() > 0)
	{
		for (int i = 0; i < _DockChoices.size(); i++)
		{
			_DockOptions.AddOption(SYDEButton(_DockChoices[i].NextIsland + " (" + to_string(_DockChoices[i].FerryCost) + ")", Vector2(6, 8 + i), Vector2(30, 1), BLACK, true));
			_DockOptions[i].m_Label = _DockChoices[i].NextIsland;
			_DockOptions[i].setHighLight(RED);
		}
	}
	_DockOptions.AddOption(SYDEButton("Don't Travel Yet", Vector2(6, 8 + _DockChoices.size()), Vector2(20, 1), BLACK, true));
	_DockOptions[_DockChoices.size()].m_Label = "ExitDockMenu";
	_DockOptions[_DockChoices.size()].setHighLight(RED);

	_DockOptions.setPos(Vector2(16, 9));
	_DockOptions.setActive(false);
}

void MainMapScene::DeleteMoveChoices()
{
	for (int i = 0; i < _MoveChoices.size(); i++)
	{
		_MoveChoices[i].Clear();
	}
	_MoveChoices.clear();
}

void MainMapScene::RefreshMoveChoices()
{
	DeleteMoveChoices();
#pragma region MoveChoices
	if (m_IslandsDeep <= 1)
	{
		int MoveSelection = rand() % 3;
		switch (MoveSelection)
		{
		case 0:
			_MoveChoices.push_back(MoveChoice(new Scary_Face(), 500));
			_MoveChoices.push_back(MoveChoice(new Marked(), 1000));
			_MoveChoices.push_back(MoveChoice(new Smoke_Break(), 250));
			break;
		case 1:
			_MoveChoices.push_back(MoveChoice(new Self_Destruct(), 2000));
			_MoveChoices.push_back(MoveChoice(new Sudden_Cold(), 1600));
			_MoveChoices.push_back(MoveChoice(new Sing(), 1250));
			break;
		case 2:
		default:
			_MoveChoices.push_back(MoveChoice(new Waterboard(), 1000));
			_MoveChoices.push_back(MoveChoice(new Skull_Pierce(), 800));
			_MoveChoices.push_back(MoveChoice(new Knights_Sword(), 550));
			break;
		}
	}
	else if (m_IslandsDeep <= 3)
	{
		int MoveSelection = rand() % 3;
		switch (MoveSelection)
		{
		case 0:
			_MoveChoices.push_back(MoveChoice(new Sabotage(), 750));
			_MoveChoices.push_back(MoveChoice(new Marked(), 1000));
			_MoveChoices.push_back(MoveChoice(new Sour_Note(), 250));
			break;
		case 1:
			_MoveChoices.push_back(MoveChoice(new Garden(), 500));
			_MoveChoices.push_back(MoveChoice(new Poison_Flower(), 1000));
			_MoveChoices.push_back(MoveChoice(new Sing(), 1250));
			break;
		case 2:
		default:
			_MoveChoices.push_back(MoveChoice(new Loose_Match(), 200));
			_MoveChoices.push_back(MoveChoice(new Bubble(), 100));
			_MoveChoices.push_back(MoveChoice(new Snowman(), 50));
			break;
		}
	}
#pragma endregion
	_ShopOptions = SYDEMenu();
	if (_MoveChoices.size() > 0)
	{
		for (int i = 0; i < _MoveChoices.size(); i++)
		{
			_ShopOptions.AddOption(SYDEButton(_MoveChoices[i].m_Move->getName() + " (" + to_string(_MoveChoices[i].m_Cost) + ")", Vector2(6, 8 + i), Vector2(20, 1), BLACK, true));
			_ShopOptions[i].setHighLight(RED);
		}
	}
	_ShopOptions.AddOption(SYDEButton("Back", Vector2(6, 8 + _MoveChoices.size()), Vector2(20, 1), BLACK, true));
	_ShopOptions[_MoveChoices.size()].m_Label = "ExitMenu";
	_ShopOptions[_MoveChoices.size()].setHighLight(RED);

	_ShopOptions.setPos(Vector2(16, 9));
	_ShopOptions.setActive(false);
}

void MainMapScene::RefreshPlayerMenuChoices()
{

	_PlayerMenuOptions = SYDEMenu();

	_PlayerMenuOptions.AddOption(SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(0)->getName(), Vector2(2, 3), Vector2(20, 1), BLACK, true));
	_PlayerMenuOptions[0].setHighLight(RED);															   
	_PlayerMenuOptions.AddOption(SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(1)->getName(), Vector2(2, 4), Vector2(20, 1), BLACK, true));
	_PlayerMenuOptions[1].setHighLight(RED);															   
	_PlayerMenuOptions.AddOption(SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(2)->getName(), Vector2(2, 5), Vector2(20, 1), BLACK, true));
	_PlayerMenuOptions[2].setHighLight(RED);															   
	_PlayerMenuOptions.AddOption(SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(3)->getName(), Vector2(2, 6), Vector2(20, 1), BLACK, true));
	_PlayerMenuOptions[3].setHighLight(RED);															   
	_PlayerMenuOptions.AddOption(SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(4)->getName(), Vector2(2, 7), Vector2(20, 1), BLACK, true));
	_PlayerMenuOptions[4].setHighLight(RED);

	_PlayerMenuOptions.setPos(Vector2(2, 3));
	_PlayerMenuOptions.setActive(true);
}

Enemy* MainMapScene::getRandomEnemyFromPool(int pool, int minLvl)
{
	//POOL CAPID ISLE BEES
	if (pool == 0)
	{
		return new Orc(minLvl + (rand() % 4));
	}
	if (pool == 1)
	{
		int i = rand() % 4;
		if (i == 0)
		{
			return new Rabbit(minLvl + (rand() % 4));
		}
		return new Bee(minLvl + (rand() % 5));
	}
	if (pool == 2)
	{
		int i = rand() % 2;
		if (i == 0)
		{
			return new  Orc(minLvl + (rand() % 2));
		}
		return new Blue_Fish(minLvl + (rand() % 3));
	}
	if (pool == 3)
	{
		return new Wolf(minLvl + (rand() % 5));
	}
	if (pool == 4)
	{
		return new Crab(minLvl + (rand() % 5));
	}
	if (pool == 5)
	{
		int i = rand() % 2;
		if (i == 0)
		{
			return new Wolf(minLvl + (rand() % 4));
		}
		return new Rabbit(minLvl + rand() % 7);
	}
	return new Enemy();
}

void MainMapScene::SetEnemyFromTag(Enemy& e)
{
	std::string _str = e.getTag();
	std::vector<std::string> _Values = SYDEMapGame::Split(_str, ';');
	e.SetAnimation(SYDEMapGame::StringToAnimation(_Values[0]));
	e.setAnimationLoop(true);
	std::vector<Move*> _MoveArray = std::vector<Move*>();
	for (int i = 1; i < 6; i++)
	{
		Move* m = SQMoveFunctions::IntToMove(static_cast<_SQMoves>(std::stoi(_Values[i])));
		_MoveArray.push_back(m);
	}
	e.ClearMoves();
	e.SetMoves(_MoveArray);
	_MoveArray.clear();
}

int MainMapScene::CheckWFA(char tempChar)
{
	try
	{
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == 'v')
		{
			if (random_variable == 15 && GameScene::GetSceneTag() == MainMap)
			{
				json j = json::parse(getEnemy(SYDEMapGame::camera_Pos));
				Enemy e;
				e.from_json(j);
				SetEnemyFromTag(e);
				BattleScene::setEnemy(e);
				BattleScene::setPlayer(SYDEMapGame::m_Player);
				BattleScene::SetUpFight();
				GameScene::SetScene(Battle);
				return 1;
				//DestroyScene();
			}
		}
	}
	catch (std::exception exception)
	{
		DestroyScene(true);
		//CRASH, EXIT THE GAME
		exit(NULL);
		return 0;
	}
	return 0;
}


LoadScene::LoadScene()
{
	m_LoadScene = MainMap;
	m_LoadSceneAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\\Animations\\Cutscenes\\LoadingScreen.bmp", AssetsClass(), 100, 100, 20, 20, 0, 25));
}

LoadScene::LoadScene(_SQScene s)
{
	m_LoadScene = s;
	m_LoadSceneAnimation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\\Animations\\Cutscenes\\LoadingScreen.bmp", AssetsClass(), 100, 100, 20, 20, 0, 25));
}

LoadScene::~LoadScene()
{
	delete& m_LoadSceneAnimation;
}

ConsoleWindow LoadScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_LoadSceneAnimation.draw_asset(window, Vector2(0, 0));
	if (m_LoadSceneAnimation.getFrame() == m_LoadSceneAnimation.getFrameSize() - 1)
	{
		GameScene::SetScene(m_LoadScene);
	}
	return window;
}
#pragma region MoveSelection

MoveSelectionScene::MoveSelectionScene()
{
	Configure_EO();
}

MoveSelectionScene::~MoveSelectionScene()
{
}

void MoveSelectionScene::Configure_EO()
{
	_MoveOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(0)->getName(), Vector2(2, 2), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(1)->getName(), Vector2(2, 3), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(2)->getName(), Vector2(2, 4), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(3)->getName(), Vector2(2, 5), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton(SYDEMapGame::m_Player.getMoveAtIndex(4)->getName(), Vector2(2, 6), Vector2(20, 1), BLACK_WHITE_BG, true),
	});
	Configure_UO();
	_MoveOptions.setActive(true);
	_MoveOptions.setPos(Vector2(2, 2));
	UnlockedPage = 0;
	MaxUnlockPages = SYDEMapGame::m_Player.getUnlockedMoves().size() / 10;

	for (int i = 0; i < _MoveOptions.getSize(); i++)
	{
		_MoveOptions[i].setHighLight(RED);
		_MoveOptions[i].m_Label = SYDEMapGame::m_Player.getMoveAtIndex(i)->toStatsJsonString();
	}
	json j = json::parse(_MoveOptions.getSelected().m_Label);
	mvs = MoveStats(j);
}

void MoveSelectionScene::Configure_UO()
{
	_UnlockedOptions = SYDEMenu(vector<SYDEButton> {
			SYDEButton("???", Vector2(2, 2), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 3), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 4), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 5), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 6), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 7), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 8), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 9), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 10), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("???", Vector2(2, 11), Vector2(20, 1), BLACK_WHITE_BG, true),
			SYDEButton("Next", Vector2(2, 12), Vector2(20, 1), BLACK_WHITE_BG, true),
	});
	for (int i = 0; i < _UnlockedOptions.getSize(); i++)
	{
		_UnlockedOptions[i].setHighLight(RED);
	}
	for (int i = (UnlockedPage * 10); i < SYDEMapGame::m_Player.getUnlockedMoves().size() && i < (UnlockedPage * 10) + 10 ; i++)
	{
		Move* m = SQMoveFunctions::IntToMove(SYDEMapGame::m_Player.getUnlockedMoves()[i]);
		_UnlockedOptions[i].setText(m->getName());
		_UnlockedOptions[i].m_Label = m->toStatsJsonString();
		delete[] m;
	}
	_UnlockedOptions[10].m_Label = "NxtPge";
}

ConsoleWindow MoveSelectionScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	switch (mss)
	{
	case EquippedMoves:
		window.setTextAtPoint(Vector2(13, 1), "MOVE SELECTION", BLACK_WHITE_BG);

		window = _MoveOptions.draw_menu(window);
		if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
		{
			_MoveOptions.nextSelect();
			json j = json::parse(_MoveOptions.getSelected().m_Label);
			mvs = MoveStats(j);
		}
		window.setTextAtPoint(Vector2(2, 13), "MOVE STATS:", BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 14), "MOVE: " + mvs.m_Name, BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 15), "TYPE: " + SQFunctions::TypeToString(mvs.m_Type), BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 16), "POWER: " + std::to_string((int)mvs.BasePower), BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 17), "FOR: " + mvs.typesToString(), BLACK_WHITE_BG);
		if (SYDEKeyCode::get_key('I')._CompareState(KEYDOWN))
		{
			GameScene::SetScene(MainMap);
			return window;
		}
		else if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
		{
			mss = UnlockedMoves;
			Configure_UO();
			json j = json::parse(_UnlockedOptions.getSelected().m_Label);
			mvs = MoveStats(j);
			return window;
		}
		break;
	case UnlockedMoves:
		window.setTextAtPoint(Vector2(13, 1), "REPLACE ATTACK", BLACK_WHITE_BG);
		window = _UnlockedOptions.draw_menu(window);
		if (SYDEKeyCode::get_key('I')._CompareState(KEYDOWN))
		{
			GameScene::SetScene(MainMap);
			return window;
		}
		else if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
		{
			_UnlockedOptions.nextSelect();
			if (_UnlockedOptions.getSelected().m_Label != "NxtPge" && _UnlockedOptions.getSelected().m_Label != "")
			{
				json j = json::parse(_UnlockedOptions.getSelected().m_Label);
				mvs = MoveStats(j);
			}
			else
			{
				mvs = MoveStats(0);
			}
		}
		else if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
		{
			if (_UnlockedOptions.getSelected().m_Label == "NxtPge")
			{
				UnlockedPage++;
				if (UnlockedPage > MaxUnlockPages)
				{
					UnlockedPage = 0;
				}
				Configure_UO();
				json j = json::parse(_UnlockedOptions.getSelected().m_Label);
				mvs = MoveStats(j);
				return window;
			}
			else if (_UnlockedOptions.getSelected().m_Label != "")
			{
				//SET MOVE
				Move* m = SQMoveFunctions::IntToMove(SYDEMapGame::m_Player.getUnlockedMoves()[(UnlockedPage * 10) + _UnlockedOptions.getSelectedNumber()]);
				if (m->getIfTeachable(SYDEMapGame::m_Player.getType()))
				{
					SYDEMapGame::m_Player.SetMoveAtIndex(_MoveOptions.getSelectedNumber(), m);
					mss = EquippedMoves;
					Configure_EO();
				}
				else
				{
					//DISPLAY ERROR MESSAGE
				}
				return window;
			}
			return window;
		}
		window.setTextAtPoint(Vector2(2, 13), "MOVE STATS:", BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 14), "MOVE: " + mvs.m_Name, BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 15), "TYPE: " + SQFunctions::TypeToString(mvs.m_Type), BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 16), "POWER: " + std::to_string((int)mvs.BasePower), BLACK_WHITE_BG);
		window.setTextAtPoint(Vector2(2, 17), "FOR: " + mvs.typesToString(), BLACK_WHITE_BG);
		break;
	default:
		GameScene::SetScene(MainMenu);
		return window;
	}
	return window;
}

MoveStats::MoveStats(int null)
{
	this->m_Name = "???";
	this->m_Type = Typeless;
	this->BasePower = 0;
	this->m_TeachAbleTypes = std::vector<_SQType>();
}

MoveStats::MoveStats(json j)
{
	this->m_Name = j.at("name").get<std::string>();
	this->m_Type = static_cast<_SQType>(j.at("type").get<int>());
	this->BasePower = j.at("basepower").get<float>();
	this->m_TeachAbleTypes = j.at("teachable").get<std::vector<_SQType>>();
}

std::string MoveStats::typesToString()
{
	std::string s = "";
	for (int i = 0; i < m_TeachAbleTypes.size(); i++)
	{
		if (i != 0)
		{
			s += "-";
		}
		s += SQFunctions::TypeToString(m_TeachAbleTypes[i]);
	}
	return s;
}

#pragma endregion