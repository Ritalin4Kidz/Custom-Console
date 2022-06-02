#include "PlayerAlison.h"

void PlayerAlison::init_Char(int lvl)
{
	SetMoves(vector<Move*>({
	new SmokeBreakMove(),
	new BoneClubMove(),
	new SmokeBreakMove(),
	new SmokeBreakMove(),
		}));
	m_LastEffortMove = new ScrapMove();
	m_Animation.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\PlayerAnimations\\AlisonBehindAnim.bmp", 50, 20, 10, 10, 0, 10));
	setAnimationLoop(true);
	this->setLevel(lvl);
	this->setHealth(50); //70
	this->setMaxHealth(50); //70
	this->setAttack(100); //120
	this->setDefence(100); //220
	this->setMagicAttack(20); //290
	this->setMagicDefence(10); //300
	this->setName("Alison");
	this->setSpeed(50);
	this->setType(Air);
}
