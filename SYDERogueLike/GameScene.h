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

	bool getIsTransient() { return m_isTransient; }

	static ConsoleWindow drawUI(ConsoleWindow window);


	static void addToUIControl(SYDEUI* item) { m_UIControl.push_back(item); }
	static void setUIEnabled(bool enabled, int index);
	static size_t findLabelInUI(std::string a_Lbl, int index);
	static std::string getLabelInUI(int index) { return m_UIControl[index]->m_Label; }
	static int getUISize() { return m_UIControl.size(); }
	static void setUIText(std::string newText, int index) { m_UIControl[index]->m_Text = newText; }

	static void clearUI();

protected:
	std::string m_SceneTag;
	bool m_isTransient = false;

private:
	static vector<SYDEUI*> m_UIControl;
};