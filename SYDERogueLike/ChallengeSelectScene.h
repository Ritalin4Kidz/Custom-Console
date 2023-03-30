#pragma once
#include "GameScene.h"
#include "SydeRogueLikeStatics.h"
#include "SYDEFileDefaults.h"
#include "SYDEEngineUI.h"

#include "SYDEScrollViewer.h"

enum ChallengeSelectSceneStates
{
	m_CSS_Normal = 0,
	m_CSS_Details = 1,
};

struct ChallengeSelectObject
{
public:
	ChallengeSelectObject(string s, std::vector<std::string> desc, string d) { m_SceneTag = s; m_Desc = desc; m_DisplayTag = d; }
	string m_SceneTag;
	std::vector<std::string> m_Desc;
	string m_DisplayTag;
};

class ChallengeSelectScene : public GameScene
{
public:
	ChallengeSelectScene() { m_SceneTag = "Challenge Select Scene"; }

	ConsoleWindow window_draw(ConsoleWindow window, int windowWidth, int windowHeight) override;
	void onNewScene() override;
	static void setSelectedChallengeInt(int index) { selectedChallenge = index; }

	static ChallengeSelectSceneStates m_SceneState;

	static void initChallengeCall() { startChallengeCall = true; }

private:
	static AssetsClass astVars;

	static bool startChallengeCall;

	static int selectedChallenge;
	std::vector<ChallengeSelectObject> m_LevelList = std::vector<ChallengeSelectObject>();


	SYDEClickableButton m_BackDtlsBtn;
	SYDEClickableButton m_StartGameDtlsBtn;
};

class ChallengeDescStatics
{
public:
	static std::vector<std::string> generateBaseDesc();
};