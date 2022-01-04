#include "pch.h"
#include "SYDESlider.h"

SYDESlider::SYDESlider(Vector2 a_Pos, int size, ColourClass BackClr, ColourClass SliderClr)
{
	m_Pos = a_Pos;
	m_Size = size;
	SliderColour = SliderClr;
	BackColour = BackClr;
}

ConsoleWindow SYDESlider::draw_ui(ConsoleWindow window)
{
	if (isInDraggedState)
	{
		sliderValue = SYDEKeyCode::getMousePosition().getX() - m_Pos.getX();
	}
	if (sliderValue < 0)
	{
		sliderValue = 0;
		//isInDraggedState = false;
		//canClick = true;
	}
	else if (sliderValue >= m_Size)
	{
		sliderValue = m_Size - 1;
		//isInDraggedState = false;
		//canClick = true;
	}
	for (int i = 0; i < m_Size; i++)
	{
		window.setTextAtPoint(Vector2(i + m_Pos.getX(), m_Pos.getY()), "-", window.determineColourAtPoint(Vector2(m_Pos.getX() + i, m_Pos.getY()), BackColour, true));
	}
	window.setTextAtPoint(Vector2(sliderValue + m_Pos.getX(), m_Pos.getY()), " ", SliderColour);
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN))
	{
		if (pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition()))
		{
			sliderValue = SYDEKeyCode::GetLastClickPosition().getX() - m_Pos.getX();
			if (!isHoldClickRequired)
				isInDraggedState = !isInDraggedState;
			else
				isInDraggedState = true;
		}
		else if (isInDraggedState && !isHoldClickRequired)
		{
			isInDraggedState = false;
		}
	}
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP))
	{
		if (isHoldClickRequired)
		{
			isInDraggedState = false;
		}
	}
	return window;
}

bool SYDESlider::pointIsInButtonRange(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() >= m_Pos.getX() && (Point.getX() < m_Pos.getX() + m_Size));
	bool withinHeightBoundaries = (Point.getY() == m_Pos.getY());
	return withinHeightBoundaries && withinLengthBoundaries;
}

SYDEVerticalSlider::SYDEVerticalSlider(Vector2 a_Pos, int size, ColourClass BackClr, ColourClass SliderClr)
{
	m_Pos = a_Pos;
	m_Size = size;
	SliderColour = SliderClr;
	BackColour = BackClr;
}

ConsoleWindow SYDEVerticalSlider::draw_ui(ConsoleWindow window)
{
	if (isInDraggedState)
	{
		sliderValue = SYDEKeyCode::getMousePosition().getY() - m_Pos.getY();
	}
	if (sliderValue < 0)
	{
		sliderValue = 0;
		//isInDraggedState = false;
		//canClick = true;
	}
	else if (sliderValue >= m_Size)
	{
		sliderValue = m_Size - 1;
		//isInDraggedState = false;
		//canClick = true;
	}
	for (int i = 0; i < m_Size; i++)
	{
		window.setTextAtPoint(Vector2(m_Pos.getX(), i + m_Pos.getY()), "|", window.determineColourAtPoint(Vector2(m_Pos.getX(), m_Pos.getY() + i), BackColour, true));
	}
	window.setTextAtPoint(Vector2(m_Pos.getX(), sliderValue + m_Pos.getY()), " ", SliderColour);
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYDOWN))
	{
		if (pointIsInButtonRange(SYDEKeyCode::GetLastClickPosition()))
		{
			sliderValue = SYDEKeyCode::GetLastClickPosition().getY() - m_Pos.getY();
			if (!isHoldClickRequired)
				isInDraggedState = !isInDraggedState;
			else
				isInDraggedState = true;
		}
		else if (isInDraggedState && !isHoldClickRequired)
		{
			isInDraggedState = false;
		}
	}
	if (SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE._CompareState(KEYUP))
	{
		if (isHoldClickRequired)
		{
			isInDraggedState = false;
		}
	}
	return window;
}

bool SYDEVerticalSlider::pointIsInButtonRange(Vector2 Point)
{
	bool withinLengthBoundaries = (Point.getX() == m_Pos.getX());
	bool withinHeightBoundaries = (Point.getY() >= m_Pos.getY() && (Point.getY() < m_Pos.getY() + m_Size));
	return withinHeightBoundaries && withinLengthBoundaries;
}
