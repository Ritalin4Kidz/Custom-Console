#pragma once
#include <cmath>
/// <summary>
/// Point consisting of a x & y value
/// </summary>
class Vector2 {
public:
	Vector2() { x = 0; y = 0; }
	Vector2(float X) { x = X; y = X; }
	Vector2(float X, float Y) { x = X; y = Y; }

	float getX() { return x; }
	float getY() { return y; }

	void setX(float a_X) { x = a_X; }
	void setY(float a_Y) { y = a_Y; }

	void addX(float a_X) { x += a_X; }
	void addY(float a_Y) { y += a_Y; }

	void addXSafe(float a_X, float min, float max);
	void addYSafe(float a_Y, float min, float max);

	Vector2& operator+(Vector2 other);
	Vector2& operator-(Vector2 other);
	Vector2& operator*(float other);

	Vector2& operator=(Vector2 other);
	Vector2& operator-=(Vector2 other);
	Vector2& operator+=(Vector2 other);
	Vector2& operator*=(float other);

	/// <summary>
	/// Add a float to the values of the vector2
	/// </summary>
	/// <param name="offset"></param>
	/// <returns></returns>
	Vector2 offset(float offset);
	bool willHit(Vector2 other, Vector2 gravity);
	bool operator==(Vector2 other);

	/// <summary>
	/// return the distance between two points
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	float distance(Vector2 other);

private:
	float x;
	float y;
};