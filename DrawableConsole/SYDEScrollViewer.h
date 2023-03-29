#pragma once
#include <string>
#include "ConsoleWindow.h"
#include "Vector2.h"
#include "SYDEUI.h"
#include "SYDEWindowGame.h"
#include "SYDEButton.h"
#include "SYDEKeyCode.h"
#include "SYDEUI.h"
#include "SYDESlider.h"
#include <memory>

class SYDEScrollViewerElement
{
public:
	SYDEScrollViewerElement() { }
	SYDEScrollViewerElement(std::shared_ptr<SYDEUI> ui) { m_UIElement = ui; }

	Vector2 getPos() 
	{
		return m_UIElement->getPos();
	}

	ConsoleWindow draw_ui(ConsoleWindow window)
	{
		return m_UIElement->draw_ui(window);
	}

	void setPos(Vector2 p) 
	{ 
		m_UIElement->setPos(p); 
	}

private:
	std::shared_ptr<SYDEUI> m_UIElement;
};

/// <summary>
/// Not Technically A UI Element, But Instead A Custom Window Filled With UI Elements
/// that's the best i can explain this
/// </summary>
class SYDEScrollViewer : public SYDEUI {
public:
	SYDEScrollViewer() { init(); }
	SYDEScrollViewer(Vector2 a_Pos, Vector2 a_Size, vector<SYDEScrollViewerElement> items, ColourClass backGround) { 
		m_Pos = a_Pos; m_Size = a_Size; 
		m_Items = items; BackgroundColour = backGround; 
		init(); 
	}

	void init();

	/// <summary>
	/// Draw the button onto the window
	/// </summary>
	/// <param name="window"></param>
	/// <returns></returns>
	ConsoleWindow draw_ui(ConsoleWindow window) override;

	void addElement(SYDEScrollViewerElement e) { m_Items.push_back(e); }

protected:
	Vector2 m_Pos;
	Vector2 m_Size;

	SYDEVerticalSlider m_Scrollbar= SYDEVerticalSlider(Vector2(0, 0), 0, WHITE, BRIGHTWHITE_BRIGHTWHITE_BG);
	vector<SYDEScrollViewerElement> m_Items;
	ColourClass BackgroundColour = BLACK;

	int m_ViewStartingLine = 0;

};
