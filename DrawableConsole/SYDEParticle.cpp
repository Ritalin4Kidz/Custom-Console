#include "pch.h"
#include "SYDEParticle.h"

SYDEParticle::SYDEParticle(Vector2 pos, Vector2 vel, float lifeSpan, ColourClass c, std::string _char)
{
	m_Pos = pos; m_Velocity = vel; m_LifeTime = lifeSpan; m_colour = c; m_character = _char;
}

void SYDEParticle::draw(ConsoleWindow& w)
{
	if (!isDead())
	{
		ColourClass c = m_colour;
		if (m_TRANSPARENT)
		{
			c = w.determineColourAtPoint(m_Pos, m_colour, true);
		}
		w.setTextAtPoint(m_Pos, m_character, c);
		m_Pos += m_Velocity;
		m_LifeTime -= SYDEDefaults::getDeltaTime();
	}

}

void SYDEParticleEmitter::draw(ConsoleWindow& w)
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		m_Particles[i].draw(w);
		if (m_Particles[i].isDead())
		{
			m_Particles.erase(m_Particles.begin() + i);
			i--;
		}
	}
	if ((m_Particles.size() < maxParticles) && running)
	{
		TimeToSpawn += SYDEDefaults::getDeltaTime();
		if (TimeToSpawn >= spawnTime)
		{
			if (_RandomColour)
			{
				int r = rand() % 255;
				m_ParticleColour = static_cast<ColourClass>(r);
			}
			float _x = m_VelocityMin.getX() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_VelocityMax.getX() - m_VelocityMin.getX())));
			float _y = m_VelocityMin.getY() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_VelocityMax.getY() - m_VelocityMin.getY())));
			m_Particles.push_back(SYDEParticle(m_Pos, Vector2(_x,_y), particleLifeSpan,m_ParticleColour,m_ParticleCharacter));
		}
	}
}

void SYDEParticleBurst::draw(ConsoleWindow& w)
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		m_Particles[i].draw(w);
		if (m_Particles[i].isDead())
		{
			m_Particles.erase(m_Particles.begin() + i);
			i--;
		}
	}
}

void SYDEParticleBurst::burst()
{
	for (int i = 0; i < maxParticles; i++)
	{
		if (_RandomColour)
		{
			int r = rand() % 255;
			m_ParticleColour = static_cast<ColourClass>(r);
		}
		float _x = m_VelocityMin.getX() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_VelocityMax.getX() - m_VelocityMin.getX())));
		float _y = m_VelocityMin.getY() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_VelocityMax.getY() - m_VelocityMin.getY())));
		m_Particles.push_back(SYDEParticle(m_Pos, Vector2(_x, _y), particleLifeSpan, m_ParticleColour, m_ParticleCharacter));
	}
}
