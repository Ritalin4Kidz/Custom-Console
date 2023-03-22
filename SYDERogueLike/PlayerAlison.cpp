#include "PlayerAlison.h"

void PlayerAlison::addMovePool()
{
	m_MovePool.push_back(MovePoolItem(std::shared_ptr<Move>(new SourNoteMove()), 100));
}

void PlayerAlison::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SmokeBreakMove()),
		std::shared_ptr<Move>(new SingMove()),
		std::shared_ptr<Move>(new GustMove()),
		std::shared_ptr<Move>(new BalloonPopMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\AlisonBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(30); //70
	this->setMaxHealth(30); //70
	this->setAttack(120); //120
	this->setDefence(50); //220
	this->setMagicAttack(120); //290
	this->setMagicDefence(30); //300
	this->setName("Alison");
	this->setSpeed(80);
	this->setType(Air);
	this->setMoney(20);
	this->setAbility(SYDEQuestAbilites::SQA_Hasten);
	addMovePool();
}

void PlayerAlison::levelUpStats()
{
	this->setMaxHealth(this->getMaxHealth() + 1); //70
	this->setHealth(this->getHealth() + 1); //70
	this->setAttack(this->getAttack() + 1); //120
	this->setMagicDefence(this->getMagicAttack() + 1); //290
	this->setSpeed(this->getSpeed() + 4);
}
