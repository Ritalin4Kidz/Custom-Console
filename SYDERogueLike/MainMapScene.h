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
	MMS_UIAnimation = 1
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
	virtual ~MainMapScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void destroyScene() override;

	void test();

	void setUpMap();

	void sortSpaces();

	void addSpace(Vector2 location, Color pix);

	void loadBasicBattleScene();

	bool addSpaceToExistingPath(int path, int space, Vector2 pos, std::string data, int pathType);

	MapSpace getSpace(int path, int space);

	MapSpaceTypes getPixRedToType(int red);

	static void triggerMove() { moveCall = true; }
	static void triggerChoice() { choiceCall = true; }

	ArrowDisplay returnArrowForPath(Vector2 nextPathPos, Vector2 currentPos, void(*f)(), string a_Tag, int middleWidth, int middleHeight);

	static void setSpaceMoveTo(Vector2 v) { m_SpaceMoveTo = v; }

private:
	static std::string m_MapToLoad;
	static Vector2 m_SpaceMoveTo;
	static bool moveCall;
	static bool choiceCall;

	bool showRouteOptions = false;

	std::vector<MapPath> m_MapPaths = std::vector<MapPath>();
	MapConfigObject m_CfgObj;
	CustomAsset m_MapBg;
	Vector2 cameraPos; 
	Vector2 m_Space = Vector2(0, 0);

	vector<SYDEUI*> m_UIControl = vector<SYDEUI*>();

	CustomAsset_Clickable m_SwapPathBtn;
	Vector2 swapBtnPos;
	CustomAsset_Clickable m_ContinuePathBtn;
	Vector2 contBtnPos;

	CustomAnimationAsset m_UIAnimation;
	std::string sceneLoad;

	MainMapScene_States m_SceneState = MMS_Normal;
};