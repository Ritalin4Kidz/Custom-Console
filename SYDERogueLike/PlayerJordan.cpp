#include "PlayerJordan.h"

void PlayerJordan::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new RoboticsMove()),
	std::shared_ptr<Move>(new ThunderStormMove()),
	std::shared_ptr<Move>(new ShatteredBulbMove()),
	std::shared_ptr<Move>(new BrightIdeaMove()),
		}));
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\JordanBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(35); //70
	this->setMaxHealth(35); //70
	this->setAttack(95); //120
	this->setDefence(5); //220
	this->setMagicAttack(95); //290
	this->setMagicDefence(5); //300
	this->setName("Jordan");
	this->setSpeed(110);
	this->setType(Electric);
	this->setAbility(Ability_NaturalBoost);
	this->setMoney(30);
	addMovePool();
}

void PlayerJordan::addMovePool()
{
	m_MovePool.push_back(MovePoolItem(std::shared_ptr<Move>(new LightningBoltMove()), 100));
	m_MovePool.push_back(MovePoolItem(std::shared_ptr<Move>(new LightningPunchMove()), 50));
}

void PlayerJordan::levelUpStats()
{
	this->setMaxHealth(this->getMaxHealth() + 3); //70
	this->setHealth(this->getMaxHealth());
	this->setMagicAttack(this->getMagicAttack() + 4); //290
}
