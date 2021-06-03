#include "SRLPlayer.h"

SRLPlayer::SRLPlayer()
{
}

SRLPlayer::SRLPlayer(string name, int speed, int attack, int defence)
{
	m_PlayerName = name;
	m_BaseSpeed = speed;
	m_BaseAttack = attack;
	m_BaseDefence = defence;
}

SRLPlayer::~SRLPlayer()
{
}
