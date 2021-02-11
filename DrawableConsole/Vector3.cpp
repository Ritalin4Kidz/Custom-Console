#include "Vector3.h"

void Vector3::addXSafe(float a_X, float min, float max)
{
	x += a_X;
	if (x > max)
	{
		x = max;
	}
	else if (x < min) {
		x = min;
	}
}

void Vector3::addYSafe(float a_Y, float min, float max)
{
	y += a_Y;
	if (y > max)
	{
		y = max;
	}
	else if (y < min) {
		y = min;
	}
}

void Vector3::addZSafe(float a_Z, float min, float max)
{
	z += a_Z;
	if (z > max)
	{
		z = max;
	}
	else if (z < min) {
		z = min;
	}
}

Vector3& Vector3::operator+(Vector3 other)
{
	Vector3* temp = &Vector3(this->x + other.getX(), this->y + other.getY(), this->z + other.getZ());
	return *temp;
}

Vector3& Vector3::operator-(Vector3 other)
{
	Vector3* temp = &Vector3(this->x - other.getX(), this->y - other.getY(), this->z - other.getZ());
	return *temp;
}  

Vector3& Vector3::operator*(float other)
{
	Vector3* temp = &Vector3(this->x * other, this->y * other, this->z * other);
	return *temp;
}

Vector3& Vector3::operator=(Vector3 other)
{
	this->x = other.x;
	this->y = other.y;
	this->y = other.z;
	return *this;
}

Vector3& Vector3::operator-=(Vector3 other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->y -= other.z;
	return *this;
}

Vector3& Vector3::operator+=(Vector3 other)
{
	this->x += other.x;
	this->y += other.y;
	this->y += other.z;
	return *this;
}

Vector3& Vector3::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
	this->y *= other;
	return *this;
}

Vector3 Vector3::offset(float offset)
{
	return Vector3(this->getX() + offset, this->getY() + offset, this->getZ() + offset);
}

bool Vector3::willHit(Vector3 other, Vector3 gravity)
{
	//not implemented
	return false;
}

bool Vector3::operator==(Vector3 other)
{
	return (x == other.x && y == other.y && z == other.z);
}

float Vector3::distance(Vector3 other)
{
	float xVar = powf(other.getX() - this->x, 2);
	float yVar = powf(other.getY() - this->y, 2);
	float zVar = powf(other.getY() - this->z, 2);
	return sqrtf(xVar + yVar + zVar);
}
