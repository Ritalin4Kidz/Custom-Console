#pragma once
#include "MainMapScene.h"
#include "OrcEnemy.h"
#include "PlayerIncludeHeader.h"
#include "ItemsHeader.h"
class ChallengeMapLevel : public MainMapScene
{
public:
	ChallengeMapLevel() {}

	void doBossAction(MapSpace currentSpace) override;
	void doBossDefeatedAction() override;

private:
	int m_BossTag = 0;
};


class ChallengeMap001 : public ChallengeMapLevel
{
public:
	ChallengeMap001()
	{
		m_SceneTag = "Challenge Map 001 Scene"; m_MapToLoad = "ChallengeMap001";

		std::shared_ptr<Player> player = std::shared_ptr<Player>(new PlayerFuri(50));
	
		for (int i = 0; i < 5; i++)
		{
			player->AddInventory(std::shared_ptr<ItemClass>(new PotionItem()));
		}

		SydeRogueLikeStatics::setPlayer(player);


	}
	int generateDiceRollAmount() override;
	void generateEnemy(MapSpace currentSpace) override;
	MapSpaceTypes generateFromPool() override;
private:
	int m_BossTag = 0;
	int m_DiceRollMin = 1;
	int m_DiceRollSize = 1;
};