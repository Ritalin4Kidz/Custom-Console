#pragma once
#include "MainMapScene.h"
#include "OrcEnemy.h"
#include "PlayerIncludeHeader.h"
#include "ItemsHeader.h"
#include "SharkBoss.h"
class ChallengeMapLevel : public MainMapScene
{
public:
	ChallengeMapLevel() {}
	void doBossAction(MapSpace currentSpace) override;
	void doBossDefeatedAction() override;
	int generateDiceRollAmount() override;
private:
	int m_BossTag = 0;
	int m_DiceRollMin = 1;
	int m_DiceRollSize = 1;
};


class ChallengeMap001 : public ChallengeMapLevel
{
public:
	ChallengeMap001() {
		m_SceneTag = "Challenge Map 001 Scene"; m_MapToLoad = "ChallengeMap001";
	}
	void doChallengeCustoms() override
	{

		std::shared_ptr<Player> player = std::shared_ptr<Player>(new PlayerFuri(50));
	
		for (int i = 0; i < 2; i++)
		{
			player->AddInventory(std::shared_ptr<ItemClass>(new PotionItem()));
			player->AddInventory(std::shared_ptr<ItemClass>(new RockItem()));
		}
		player->AddInventory(shared_ptr<ItemClass>(new MoveItemClass(std::shared_ptr<Move>(new FireballMove()),
			16, 8, AssetsClass::get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\ItemIcons\\FireTM.bmp", 8, 8),
			"TM_001")));

		SydeRogueLikeStatics::setPlayer(player);


	}
	void generateEnemy(MapSpace currentSpace) override;
	MapSpaceTypes generateFromPool() override;
private:
};

class ChallengeMap002 : public ChallengeMapLevel
{
public:
	ChallengeMap002() {
		m_SceneTag = "Challenge Map 002 Scene"; m_MapToLoad = "ChallengeMap001";
	}
	void doChallengeCustoms() override
	{

		std::shared_ptr<Player> player = std::shared_ptr<Player>(new PlayerJordan(50));

		player->setMoney(100000);

		SydeRogueLikeStatics::setPlayer(player);


	}
	void generateEnemy(MapSpace currentSpace) override;
	void doEndSpaceMethod(MapSpace currentSpace) override;
	MapSpaceTypes generateFromPool() override;
private:
};