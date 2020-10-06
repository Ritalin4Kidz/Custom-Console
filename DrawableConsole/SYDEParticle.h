#pragma once

#include "Defaults.h"
#include "ConsoleWindow.h"

#include <vector>

class SYDEParticle {
public:
	SYDEParticle() {}
	SYDEParticle(Vector2 pos, Vector2 vel) { m_Pos = pos; m_Velocity = vel; }
	SYDEParticle(Vector2 pos, Vector2 vel, float lifeSpan) { m_Pos = pos; m_Velocity = vel; m_LifeTime = lifeSpan; }
	SYDEParticle(Vector2 pos, Vector2 vel, float lifeSpan, ColourClass c, std::string _char);
	virtual ~SYDEParticle() {}

	void draw(ConsoleWindow& w);

	bool isDead() { return m_LifeTime < 0; }

private:

	std::string m_character = "*";
	ColourClass m_colour = BRIGHTGREEN;
protected:
	bool m_TRANSPARENT = true;
	float m_LifeTime = 0.5f;
	Vector2 m_Pos = Vector2(0);
	Vector2 m_Velocity = Vector2(0, 0.5f);
};

class SYDEParticleEmitter {
public:
	SYDEParticleEmitter(Vector2 pos, Vector2 minV, Vector2 maxV) { m_Pos = pos; m_VelocityMin = minV; m_VelocityMax = maxV; }
	virtual ~SYDEParticleEmitter() {}

	void draw(ConsoleWindow& w);

	/// <summary>
	/// Start the emitter
	/// </summary>
	void Start() { running = true; }
	/// <summary>
	/// Stop the emitter
	/// </summary>
	void Stop() { running = false; }

	void setLifeSpan(float s) { particleLifeSpan = s; }
	void increaseLifeSpan(float s) { particleLifeSpan += s; }
	void decreaseLifeSpan(float s) { particleLifeSpan -= s; }

	void setMaxParticles(int max) { maxParticles = max; }
	void increaseMaxParticles(int max) { maxParticles += max; }
	void decreaseMaxParticles(int max) { maxParticles -= max; }

	void setColour(ColourClass c) { m_ParticleColour = c; }
	void setCharacter(std::string s) { m_ParticleCharacter = s; }
	void setPos(Vector2 p) { m_Pos = p; }

	void RainbowOn(bool b) { _RandomColour = b; }

private:
	
	std::vector<SYDEParticle> m_Particles = std::vector<SYDEParticle>();
	int maxParticles = 20;
	float TimeToSpawn = 0.0f;
	float spawnTime = 0.25f;
	float particleLifeSpan = 0.5f;
	bool running = true;

	bool _RandomColour = false;

	ColourClass m_ParticleColour = BRIGHTGREEN;
	std::string m_ParticleCharacter = "*";
protected:
	Vector2 m_Pos;
	Vector2 m_VelocityMin;
	Vector2 m_VelocityMax;
};

class SYDEParticleBurst {
public:
	SYDEParticleBurst(Vector2 pos, Vector2 minV, Vector2 maxV) { m_Pos = pos; m_VelocityMin = minV; m_VelocityMax = maxV; }
	virtual ~SYDEParticleBurst() {}

	void draw(ConsoleWindow& w);
	void burst();


	bool isDead() { return m_Particles.size() <= 0; }

	void setLifeSpan(float s) { particleLifeSpan = s; }
	void increaseLifeSpan(float s) { particleLifeSpan += s; }
	void decreaseLifeSpan(float s) { particleLifeSpan -= s; }

	void setMaxParticles(int max) { maxParticles = max; }
	void increaseMaxParticles(int max) { maxParticles += max; }
	void decreaseMaxParticles(int max) { maxParticles -= max; }

	void setColour(ColourClass c) { m_ParticleColour = c; }
	void setCharacter(std::string s) { m_ParticleCharacter = s; }
	void setPos(Vector2 p) { m_Pos = p; }

	void RainbowOn(bool b) { _RandomColour = b; }
	void SolidBurst(bool b) { _solidBurst = b; }

private:

	std::vector<SYDEParticle> m_Particles = std::vector<SYDEParticle>();
	int maxParticles = 20;
	float particleLifeSpan = 0.5f;

	bool _RandomColour = false;
	bool _solidBurst = true;

	ColourClass m_ParticleColour = BRIGHTGREEN;
	std::string m_ParticleCharacter = "*";
protected:
	Vector2 m_Pos;
	Vector2 m_VelocityMin;
	Vector2 m_VelocityMax;
};