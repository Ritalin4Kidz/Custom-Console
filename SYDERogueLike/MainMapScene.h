#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "MapPath.h"
#include "MapConfig.h"
#include "SYDEEngineUI.h"
#include "SYDEEngineAssets.h"

enum MainMapScene_States
{
	MMS_Normal = 0,
	MMS_UIAnimation = 1,
	MMS_Options = 2,
	MMS_END_UIAnimation = 3,
	MMS_END = 4
};


enum MovementStates
{
	MoveState_STANDING = 0,
	MoveState_ROLLING = 1,
	MoveState_MOVEMENT = 2,
	MoveState_CHECKING = 3,
	MoveState_END = 4
};


struct ArrowDisplay
{
	ArrowDisplay(CustomAsset_Clickable a, Vector2 v) { click = a; vec = v; }
	CustomAsset_Clickable click;
	Vector2 vec;
};

class MainMapScene : public GameScene
{
public:
	MainMapScene() { m_SceneTag = "Main Map Scene"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void destroyScene() override;

	void test();

	void setUpMap();

	void sortSpaces();

	void nukeMap();

	void addSpace(Vector2 location, Color pix);

	void loadBasicBattleScene();

	void loadShopScene();

	void rollDice();

	bool addSpaceToExistingPath(int path, int space, Vector2 pos, std::string data, int pathType);

	void setUpEndMapUI();

	MapSpace getSpace(int path, int space);
	bool isLastSpace(int path, int space);


	MapSpaceTypes getPixRedToType(int red);

	static void triggerMove() { moveCall = true; }
	static void triggerChoice() { choiceCall = true; }
	static void triggerOptions() { optionsCall = true; }
	static void triggerNuke() { nukeCall = true; }
	static void triggerTick() { tickCall = true; }

	ArrowDisplay returnArrowForPath(Vector2 nextPathPos, Vector2 currentPos, void(*f)(), string a_Tag, int middleWidth, int middleHeight);

	static void setSpaceMoveTo(Vector2 v) { m_SpaceMoveTo = v; }


protected:
	std::string m_MapToLoad;
	static Vector2 m_SpaceMoveTo;
	static bool moveCall;
	static bool choiceCall;
	static bool optionsCall;
	static bool tickCall;

	static bool nukeCall;

	int spacesToMove = 0;

	int maxSpacesToMoveRange = 6;

	MovementStates m_MovementState = MoveState_STANDING;
	bool showRouteOptions = false;

	std::vector<MapPath> m_MapPaths = std::vector<MapPath>();
	MapConfigObject m_CfgObj;
	CustomAsset m_MapBg;
	Vector2 cameraPos; 
	Vector2 m_Space = Vector2(0, 0);

	SYDEParticleBurst m_GameOverFireworks = SYDEParticleBurst(Vector2(0, 0), Vector2(-1.5, -1.5), Vector2(1.5, 1.5));;
	SYDEClock_Timer m_FireworksTimer = SYDEClock_Timer(0.75f);;

	CustomAsset_Clickable m_SwapPathBtn;
	Vector2 swapBtnPos;
	CustomAsset_Clickable m_ContinuePathBtn;
	Vector2 contBtnPos;

	CustomAnimationAsset m_UIAnimation;
	std::string sceneLoad;

	MainMapScene_States m_SceneState = MMS_Normal;

	vector<std::shared_ptr<SYDEClickableButton>> m_OptionsMenu;

	virtual void doBossAction(MapSpace currentSpace);
	virtual void doBossDefeatedAction();
	virtual void generateEnemy();
};