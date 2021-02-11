#pragma once
#include "Vector2.h"
#include <cmath>
class Vector3 {
public:
	Vector3() { x = 0; y = 0; }
	Vector3(float X) { x = X; y = X; z = X; }
	Vector3(float X, float Y) { x = X; y = Y; z = 0; }
	Vector3(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	virtual ~Vector3() {}

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

	void setX(float a_X) { x = a_X; }
	void setY(float a_Y) { y = a_Y; }
	void setZ(float a_Z) { z = a_Z; }

	void addX(float a_X) { x += a_X; }
	void addY(float a_Y) { y += a_Y; }
	void addZ(float a_Z) { z += a_Z; }

	void addXSafe(float a_X, float min, float max);
	void addYSafe(float a_Y, float min, float max);
	void addZSafe(float a_Z, float min, float max);

	Vector3& operator+(Vector3 other);
	Vector3& operator-(Vector3 other);
	Vector3& operator*(float other);
		  
	Vector3& operator=(Vector3 other);
	Vector3& operator-=(Vector3 other);
	Vector3& operator+=(Vector3 other);
	Vector3& operator*=(float other);

	Vector3 offset(float offset);
	bool willHit(Vector3 other, Vector3 gravity);
	bool operator==(Vector3 other);

	float distance(Vector3 other);

private:
	float x;
	float y;
	float z;
};