#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"

class MainMapScene : public GameScene
{
public:
	MainMapScene() { m_SceneTag = "Main Map Scene"; }
	virtual ~MainMapScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void test();

	void setUpMap();

	void addSpace(Vector2 location, Color pix);

private:
	static std::string m_MapToLoad;

	CustomAsset m_MapBg;
	Vector2 cameraPos;
};