#pragma once
#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include <vector>

class SYDEShape {
public:
	SYDEShape() {}
	virtual ~SYDEShape() {}

	virtual ConsoleWindow draw(ConsoleWindow window) { return window; }

	Vector2 getSize() { return m_Size; }
	ColourClass getColour() { return m_Colour; }
	Vector2 getPos() { return m_Pos; }

	void setPos(Vector2 p) { m_Pos = p; }
	void setColour(ColourClass c) { m_Colour = c; }

protected:
	Vector2 m_Size;
	ColourClass m_Colour;
	Vector2 m_Pos;
};

class SYDESquare : public SYDEShape {
public:
	SYDESquare();
	SYDESquare(int a_Size) { m_Size = Vector2(a_Size); m_Pos = Vector2(0); m_Colour = WHITE_WHITE_BG; }
	SYDESquare(int a_Size, ColourClass a_Colour) { m_Size = Vector2(a_Size); m_Pos = Vector2(0); m_Colour = a_Colour; }
	SYDESquare(int a_Size, ColourClass a_Colour, Vector2 a_Pos) { m_Size = Vector2(a_Size); m_Pos = a_Pos; m_Colour = a_Colour;}
	SYDESquare(int a_Size, Vector2 a_Pos) { m_Size = Vector2(a_Size); m_Pos = a_Pos; m_Colour = m_Colour = WHITE_WHITE_BG;}
	SYDESquare(Vector2 a_Pos) { m_Size = Vector2(1); m_Pos = a_Pos; m_Colour = WHITE_WHITE_BG; }
	virtual ~SYDESquare();

	void setSize(int s) { m_Size = Vector2(s); }

	ConsoleWindow draw(ConsoleWindow window) override;

protected:
private:
	
};

class SYDERect : public SYDEShape {
public:
	SYDERect() {}
	SYDERect(Vector2 a_Size) { m_Size = a_Size; m_Pos = Vector2(0); m_Colour = WHITE_WHITE_BG; }
	SYDERect(Vector2 a_Size, ColourClass a_Colour) { m_Size = a_Size; m_Pos = Vector2(0); m_Colour = a_Colour; }
	SYDERect(Vector2 a_Size, ColourClass a_Colour, Vector2 a_Pos) { m_Size = a_Size; m_Pos = a_Pos; m_Colour = a_Colour; }
	SYDERect(Vector2 a_Size, Vector2 a_Pos) { m_Size = a_Size; m_Pos = a_Pos; m_Colour = m_Colour = WHITE_WHITE_BG; }

	void setSize(Vector2 s) { m_Size = s; }
	virtual ~SYDERect() {}

	ConsoleWindow draw(ConsoleWindow window) override;
protected:
private:

};