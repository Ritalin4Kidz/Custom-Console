#include "PlayerFuego.h"

void PlayerFuego::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
		std::shared_ptr<Move>(new SlashMove()),
		std::shared_ptr<Move>(new EnchantmentMove()),
		std::shared_ptr<Move>(new SabotageMove()),
		std::shared_ptr<Move>(new TypeSwapMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new FuegoSwordMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\FuegoBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(30); //70
	this->setMaxHealth(30); //70
	this->setAttack(80); //120
	this->setDefence(75); //220
	this->setMagicAttack(75); //290
	this->setMagicDefence(75); //300
	this->setName("Fuego");
	this->setSpeed(60);
	this->setType(Metal);
	this->setAbility(SYDEQuestAbilites::SQA_ConstantStruggle);
	this->setMoney(250);

	addMovePool();
	addStats(lvl);
}

void PlayerFuego::levelUpStats()
{
	this->setMaxHealth(this->getMaxHealth() + 2); //70
	this->setAttack(this->getAttack() + 3); //120
	this->setMagicDefence(this->getMagicAttack() + 3); //290
	this->setSpeed(this->getSpeed() + 2);
}

void PlayerFuego::addMovePool()
{
	m_MovePool.push_back(MovePoolItem(std::shared_ptr<Move>(new SkullPiercerMove()), 90));
}
