#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "MapPath.h"
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

	bool addSpaceToExistingPath(int path, int space, Vector2 pos, std::string data);

	MapSpace getSpace(int path, int space);

private:
	static std::string m_MapToLoad;
	std::vector<MapPath> m_MapPaths = std::vector<MapPath>();
	CustomAsset m_MapBg;
	Vector2 cameraPos;
};