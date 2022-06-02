#include "CharacterSelectScene.h"

ConsoleWindow CharacterSelectScene::window_draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", BLACK);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		for (int ii = 0; ii < windowHeight; ii++)
		{
			window.setTextAtPoint(Vector2(i, ii), " ", LIGHTGREY_LIGHTGREY_BG);
		}
	}

	window = m_PlayersVec[m_SelectedPlayer].getImg().draw_asset(window, Vector2(40,12));

	return window;
}

void CharacterSelectScene::onNewScene()
{
	m_PlayersVec = std::vector<PlayerSelectObject>(
		{
			PlayerSelectObject(2, "Furi", L"EngineFiles\\CharacterBMPS\\Furi.bmp"),
			PlayerSelectObject(2, "Alison",L"EngineFiles\\CharacterBMPS\\Alison.bmp"),
			PlayerSelectObject(2, "Bruce", L"EngineFiles\\CharacterBMPS\\Bruce.bmp")
		});
}

void CharacterSelectScene::destroyScene()
{
	m_PlayersVec.clear();
}
