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
	this->setAttack(100); //120
	this->setDefence(100); //220
	this->setMagicAttack(20); //290
	this->setMagicDefence(10); //300
	this->setName("Bruce");
	this->setSpeed(50);
	this->setType(Melee);
	this->setMoney(100);
}
