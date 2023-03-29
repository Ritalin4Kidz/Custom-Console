#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include "SYDEFileDefaults.h"
#include "SYDEEngineUI.h"

#include "SYDEScrollViewer.h"

struct ChallengeSelectObject
{
public:
	ChallengeSelectObject(string s, string desc, string d) { m_SceneTag = s; m_Desc = desc; m_DisplayTag = d; }
	string m_SceneTag;
	string m_Desc;
	string m_DisplayTag;
};

class ChallengeSelectScene : public GameScene
{
public:
	ChallengeSelectScene() { m_SceneTag = "Challenge Select Scene"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	static void setSelectedChallengeInt(int index) { selectedChallenge = index; }

private:
	static AssetsClass astVars;

	static int selectedChallenge;
	std::vector<ChallengeSelectObject> m_LevelList = std::vector<ChallengeSelectObject>({
		ChallengeSelectObject("Challenge Map 001 Scene", "SydeCoast", "Furi Of The Orcs"),
		ChallengeSelectObject("Challenge Map 001 Scene", "MeowCoast", "Shopping Spree")
		});

};