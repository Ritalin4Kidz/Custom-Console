#pragma once

class Vector2 {
public:
	Vector2() { x = 0; y = 0; }
	Vector2(float X) { x = X; y = X; }
	Vector2(float X, float Y) { x = X; y = Y; }
	virtual ~Vector2() {}

	float getX() { return x; }
	float getY() { return y; }

	void setX(float a_X) { x = a_X; }
	void setY(float a_Y) { y = a_Y; }

	Vector2& operator+(Vector2 other);
	Vector2& operator-(Vector2 other);
	Vector2& operator*(float other);

	Vector2& operator=(Vector2 other);
	Vector2& operator-=(Vector2 other);
	Vector2& operator+=(Vector2 other);
	Vector2& operator*=(float other);

	Vector2 offset(float offset);
	bool willHit(Vector2 other, Vector2 gravity);
	bool operator==(Vector2 other);

	float distance(Vector2 other);

private:
	float x;
	float y;
};