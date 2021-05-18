#include "pch.h"
#include "Vector2.h"
void Vector2::addXSafe(float a_X,float min, float max)
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
void Vector2::addYSafe(float a_Y,float min, float max)
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
Vector2 & Vector2::operator+(Vector2 other)
{
	//insert return statement here
	Vector2* temp = &Vector2(this->x + other.getX(), this->y + other.getY());
	return *temp;
}
Vector2 & Vector2::operator-(Vector2 other)
{
	Vector2* temp = &Vector2(this->x - other.getX(), this->y - other.getY());
	return *temp;
}
Vector2 & Vector2::operator*(float other)
{
	Vector2* temp = &Vector2(this->x * other, this->y * other);
	return *temp;
}
Vector2 & Vector2::operator=(Vector2 other)
{
	this->x = other.getX();
	this->y = other.getY();
	return *this;
}


Vector2 & Vector2::operator-=(Vector2 other)
{
	this->x -= other.getX();
	this->y -= other.getY();
	return *this;
}

Vector2 & Vector2::operator+=(Vector2 other)
{
	this->x += other.getX();
	this->y += other.getY();
	return *this;
}

Vector2 & Vector2::operator*=(float other)
{
	this->x *= other;
	this->y *= other;
	return *this;
}

Vector2 Vector2::offset(float offset)
{
	return Vector2(this->getX() + offset, this->getY() + offset);
}

bool Vector2::willHit(Vector2 other, Vector2 gravity)
{
	if (*this == other)
	{
		return true;
	}
	if (this->getY() > other.getY())
	{
		return false;
	}
	if (this->getY() + gravity.getY() > other.getY() && this->getX() == other.getX() + gravity.getX())
	{
		return true;
	}
	return false;
}

bool Vector2::operator==(Vector2 other)
{
	return (x == other.x && y == other.y);
}

float Vector2::distance(Vector2 other)
{
	float xVar = powf(other.getX() - this->x, 2);
	float yVar = powf(other.getY() -this->y, 2);
	return sqrtf(xVar + yVar);
}
