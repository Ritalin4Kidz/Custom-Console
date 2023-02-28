#include "GameScene.h"

vector<std::shared_ptr<SYDEUI>> GameScene::m_UIControl = vector<std::shared_ptr<SYDEUI>>();
bool GameScene::showUI = true;
ConsoleWindow GameScene::drawUI(ConsoleWindow window)
{
	if (!showUI)
	{
		return window;
	}
	for (int i = 0; i < getUISize(); i++)
	{
		window = m_UIControl[i]->draw_ui(window);
	}
	return window;
}

void GameScene::setUIEnabled(bool enabled, int index)
{
	m_UIControl[index]->setEnabled(enabled);
}

size_t GameScene::findLabelInUI(std::string a_Lbl, int index)
{
	return m_UIControl[index]->m_Label.find(a_Lbl);
}

void GameScene::clearUI()
{
	for (int i = 0; i < m_UIControl.size(); i++)
	{
		m_UIControl[i]->deleteFunction();
	}
	m_UIControl.clear();
}
