#include "pch.h"
#include "RigidBody.h"
#include <math.h>
void RigidBody::gravity(vector<RigidBody> rigidbodyArray)
{
	float distanceAtStart = m_Speed;
	float distance = distanceAtStart;
	if (!m_Kinematic)
	{
		bool hasHit = false;
		for (int i = 0; i < rigidbodyArray.size(); i++)
		{
			if (rigidbodyArray[i] != *this)
			{
				//if (rigidbodyArray[i].m_pos.getY() > this->m_pos.getY())
				//{
				//	if (distance + m_pos.getY() >= rigidbodyArray[i].m_pos.getY())
				//	{
				//		distance = abs(this->m_pos.getY() - rigidbodyArray[i].m_pos.getY());
				//		m_Speed = 0;
				//		hasHit = true;
				//		//m_Kinematic = true;
				//	}
				//}
				if (this->getPos().willHit(rigidbodyArray[i].getPos(), Vector2(0, m_Speed)))
				{
					if (distance + m_pos.getY() >= rigidbodyArray[i].m_pos.getY())
					{
						distance = abs(this->m_pos.getY() - rigidbodyArray[i].m_pos.getY());
						m_Speed = 0;
						hasHit = true;
						//m_Kinematic = true;
					}
				}
			}
		}
		this->m_pos = Vector2(m_pos.getX(), m_pos.getY() + distance);
		if (!hasHit || distance != 0)
		{
			m_Speed++;
		}
		else
		{
			m_Speed = 0;
		}
		if (constantspeed) {
			m_Speed = constantSpeedFloat;
		}
	}
}

bool RigidBody::checkArrayForHit(vector<RigidBody> rbArr)
{
	float distanceAtStart = m_Speed;
	float distance = distanceAtStart;
	if (!m_Kinematic)
	{
		bool hasHit = false;
		for (int i = 0; i < rbArr.size(); i++)
		{
			if (rbArr[i] != *this)
			{
				//if (rigidbodyArray[i].m_pos.getY() > this->m_pos.getY())
				//{
				//	if (distance + m_pos.getY() >= rigidbodyArray[i].m_pos.getY())
				//	{
				//		distance = abs(this->m_pos.getY() - rigidbodyArray[i].m_pos.getY());
				//		m_Speed = 0;
				//		hasHit = true;
				//		//m_Kinematic = true;
				//	}
				//}
				if (this->getPos().willHit(rbArr[i].getPos(), Vector2(0, m_Speed)))
				{
					if (distance + m_pos.getY() >= rbArr[i].m_pos.getY())
					{
						return true;
						//m_Kinematic = true;
					}
				}
			}
		}
	}
	return false;
}

bool RigidBody::operator==(RigidBody rb)
{
	return this->id == rb.id;
}

bool RigidBody::operator!=(RigidBody rb)
{
	return this->id != rb.id;
}
