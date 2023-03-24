#include "PlayerBruce.h"

void PlayerBruce::init_Char(int lvl)
{	
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new BoneClubMove()),
		std::shared_ptr<Move>(new SabotageMove()),
		std::shared_ptr<Move>(new TypeSwapMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\BruceBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(50); //70
	this->setMaxHealth(50); //70
	this->setAttack(130); //120
	this->setDefence(90); //220
	this->setMagicAttack(20); //290
	this->setMagicDefence(20); //300
	this->setName("Bruce");
	this->setSpeed(40);
	this->setType(Melee);
	this->setAbility(SYDEQuestAbilites::SQA_None);
	this->setMoney(100);
	addMovePool();
}

void PlayerBruce::addMovePool()
{
	m_MovePool.push_back(MovePoolItem(std::shared_ptr<Move>(new BloodPactMove()), 50));
}

void PlayerBruce::levelUpStats()
{
	this->setMaxHealth(this->getMaxHealth() + 2);
	this->setAttack(this->getAttack() + 4);
	this->setDefence(this->getDefence() + 4);
}
