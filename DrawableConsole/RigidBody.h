#pragma once
#include <vector>
#include <string>
#include "Vector2.h"
using namespace std;
class RigidBody {
public:
	RigidBody() {}
	RigidBody(Vector2 pos, float Weight, bool kinemat) { m_pos = pos; m_Weight = Weight; m_Kinematic = kinemat; }
	virtual ~RigidBody() {}

	void gravity(vector<RigidBody> rigidbodyArray);

	bool operator==(RigidBody rb);
	bool operator!=(RigidBody rb);

	void setKinematic(bool a_val) { m_Kinematic = a_val; }
	void setWeight(float a_val) { m_Weight = a_val; }
	void setPosition(Vector2 a_val) { m_pos = a_val; }
	void setID(string a_ID) { id = a_ID; }

	float getSpeed() { return m_Speed; }
	void setSpeed(float a_speed) { m_Speed = a_speed; }

	void setTrap(bool a_Val) { m_isTrap = a_Val; }
	void setTrigger(bool a_Val, string m_triggerVal) { m_isTrigger = a_Val; levelTrigger = m_triggerVal; }
	void setSolidity(bool a_Val) { m_solidBottom = a_Val; }

	bool getIsTrap() { return m_isTrap; }
	bool getIsTrigger() { return m_isTrigger; }
	bool getSolidity() { return m_solidBottom; }
	string getTriggerLevel() { return levelTrigger; }
	Vector2 getPos() { return m_pos; }
private:

	bool m_Kinematic = false;
	float m_Weight = 1.0f;
	bool m_isTrap = false;
	bool m_isTrigger = false;
	string levelTrigger = "";
	bool m_solidBottom = false;
	float m_Speed = 0.0f;
	string id = "";
	Vector2 m_pos;
};