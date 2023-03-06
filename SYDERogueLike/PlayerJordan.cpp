#include "PlayerJordan.h"

void PlayerJordan::init_Char(int lvl)
{
	SetMoves(vector<std::shared_ptr<Move>>({
	std::shared_ptr<Move>(new LightningBoltMove()),
	std::shared_ptr<Move>(new LightningPunchMove()),
	std::shared_ptr<Move>(new SlashMove()),
	std::shared_ptr<Move>(new TypeSwapMove()),
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
}
