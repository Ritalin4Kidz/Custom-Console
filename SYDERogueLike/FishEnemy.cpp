#include "FishEnemy.h"

void FishEnemy::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new FishSwarmMove()),
	std::shared_ptr<Move>(new BubblerMove()),
	std::shared_ptr<Move>(new WaterPinchMove()),
		}));


	int i = rand() % 5;
	switch (i)
	{
	case 1:
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\GreenFish.bmp", 40, 100, 10, 10, 0, 39));
		addMove(std::shared_ptr<Move>(new EnchantmentMove()));
		break;
	case 2:
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\PurpleFish.bmp", 40, 100, 10, 10, 0, 39));
		addMove(std::shared_ptr<Move>(new EnergyBeamMove()));
		break;
	case 3:
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\RedFish.bmp", 40, 100, 10, 10, 0, 39));
		addMove(std::shared_ptr<Move>(new EmberMove()));
		break;
	case 4:
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BlueFish.bmp", 40, 100, 10, 10, 0, 39));
		addMove(std::shared_ptr<Move>(new WaterboardMove()));
		break;
	default:
		m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\YellowFish.bmp", 40, 100, 10, 10, 0, 39));
		addMove(std::shared_ptr<Move>(new ThunderStormMove()));
		break;
	}
	m_LastEffortMove = std::shared_ptr<Move>(new ScrapMove());
	setAnimationLoop(true);

	this->setLevel(lvl);
	this->setHealth(20); //70
	this->setMaxHealth(20); //70
	this->setAttack(50); //120
	this->setDefence(50); //220
	this->setMagicAttack(50); //290
	this->setMagicDefence(50); //300
	this->setSpeed(50);
	this->setName("Fish");
	this->setType(Water);
	xpGainedFromFight = (200 * lvl) / 5;
	this->setAbility(SYDEQuestAbilites::SQA_None);
	this->setMoney((rand() % (10 * lvl)) + (3 * lvl));
}

std::shared_ptr<Move> FishEnemy::determineMove(Character opponent)
{
	vector<std::shared_ptr<Move>> moves = getUsableMoves();
	if (moves.size() == 0)
	{
		return m_LastEffortMove;
	}
	else
	{
		int index = rand() % moves.size();
		return moves[index];
	}
}
