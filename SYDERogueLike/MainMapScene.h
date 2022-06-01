#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "MapPath.h"
#include "MapConfig.h"
#include "SYDEEngineUI.h"
class MainMapScene : public GameScene
{
public:
	MainMapScene() { m_SceneTag = "Main Map Scene"; }
	virtual ~MainMapScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void test();

	void setUpMap();

	void sortSpaces();

	void addSpace(Vector2 location, Color pix);

	bool addSpaceToExistingPath(int path, int space, Vector2 pos, std::string data, int pathType);

	MapSpace getSpace(int path, int space);

	MapSpaceTypes getPixRedToType(int red);

	static void triggerMove() { moveCall = true; }

private:
	static std::string m_MapToLoad;

	static bool moveCall;

	bool showRouteOptions = false;

	std::vector<MapPath> m_MapPaths = std::vector<MapPath>();
	MapConfigObject m_CfgObj;
	CustomAsset m_MapBg;
	Vector2 cameraPos; 
	Vector2 m_Space = Vector2(0, 0);

	vector<SYDEUI*> m_UIControl = vector<SYDEUI*>();
};