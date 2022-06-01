#pragma once

#include "SYDEstdafx.h"
#include <string>
class GameScene {
public:
	GameScene() {}
	~GameScene() {}
	virtual ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) { return window; }
	std::string GetSceneTag() { return m_SceneTag; }

	virtual void destroyScene() {}

	virtual void onNewScene() {}
protected:
	std::string m_SceneTag;
};