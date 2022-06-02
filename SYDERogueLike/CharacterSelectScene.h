#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include <string>
#include "SYDEEngineMath.h"
#include "SYDEEngineUI.h"
#include "SYDEEngineAssets.h"
#include "PlayerIncludeHeader.h"
#include "TagToPlayer.hpp"
#include <vector>

class CharacterSelectScene : public GameScene
{
public:
	CharacterSelectScene() { m_SceneTag = "Character Select Scene"; }
	virtual ~CharacterSelectScene() {}

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;

	void destroyScene() override;
private:

	std::vector<PlayerSelectObject> m_PlayersVec;
	int m_SelectedPlayer = 0;

};