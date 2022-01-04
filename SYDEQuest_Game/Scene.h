#pragma once
#include "SYDEstdafx.h"
enum _SQScene {
	UnknownScene,
	MainMenu,
	Battle,
	MainMap,
	LoadingScene,
	PlayerSelect,
	MoveSelection,
	TestBuilding
};
class GameScene {
public:
	GameScene() {}
	~GameScene() {}
	virtual ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) { return window; }
	static void SetScene(_SQScene _SceneTag);
	static void SetScenePrev(_SQScene _SceneTag);
	static _SQScene GetSceneTag() { return m_SceneTag; }
	static _SQScene GetSceneTagPrev() { return m_SceneTag_Previous; }
protected:
	static _SQScene m_SceneTag;
	static _SQScene m_SceneTag_Previous;
};

