#include "pch.h"
#include "ReiventTheWheel.h"

void GAME_RTW::generalConstructor()
{
	m_CursorPoint = Vector2(10,5);
	m_scene = "Draw_Wheel";
}

void GAME_RTW::setUpPaintArray(int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			m_PaintingArray.push_back(GAME_RTW_PIXEL(Vector2(l,m)));
		}
	}
}

void GAME_RTW::setPaintArrayAtPoint(Vector2 aPoint, ColourClass colour)
{
	for (int i = 0; i < m_PaintingArray.size(); i++)
	{
		if (m_PaintingArray[i].getPoint() == aPoint) {
			m_PaintingArray[i].setColour(colour);
			return;
		}
	}
}

ColourClass GAME_RTW::getColourArrayAtPoint(Vector2 aPoint)
{
	for (int i = 0; i < m_PaintingArray.size(); i++)
	{
		if (m_PaintingArray[i].getPoint() == aPoint) {
			return m_PaintingArray[i].getColour();
		}
	}
	return NULLCOLOUR;
}

ConsoleWindow GAME_RTW::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (m_scene == "Draw_Wheel")
	{
		inputVoids(windowWidth, windowHeight);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
			}
		}
		for (int i = 0; i < m_PaintingArray.size(); i++)
		{
			window.setTextAtPoint(m_PaintingArray[i].getPoint(), " ", m_PaintingArray[i].getColour());
		}
		// CURSOR
		window.setTextAtPoint(m_CursorPoint, " ", DARKBLUE_DARKBLUE_BG);
		window.setTextAtPoint(Vector2(m_CursorPoint.getX() + 1, m_CursorPoint.getY()), " ", DARKBLUE_DARKBLUE_BG);
		// UI
		for (int i = 0; i < windowWidth; i++)
		{
			window.setTextAtPoint(Vector2(i, windowHeight - 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
		if (m_PaintColour == NULLCOLOUR)
		{
			window.setTextAtPoint(Vector2(0, windowHeight - 1), "-", BLACK_BRIGHTWHITE_BG);
			window.setTextAtPoint(Vector2(1, windowHeight - 1), "-", BLACK_BRIGHTWHITE_BG);
		}
		else {
			window.setTextAtPoint(Vector2(0, windowHeight - 1), " ", m_PaintColour);
			window.setTextAtPoint(Vector2(1, windowHeight - 1), " ", m_PaintColour);
		}
		window.setTextAtPoint(Vector2(2, windowHeight - 1), "P:Paint,C:Colour,WASD:Move,T:Test", BLACK_BRIGHTWHITE_BG);
	}
	else if (m_scene == "Test_Wheel")
	{
		inputVoidsWheelTest(windowWidth, windowHeight);
		for (int i = 0; i < rbArr.size(); i++)
		{
			rbArr[i].gravity(rbArr);
		}
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE_LIGHTBLUE_BG);
			}
		}
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = windowHeight - 4; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", WHITE_GREEN_BG);
			}
		}
		window = wheel.draw_asset(window, Vector2(rbArr[0].getPos().getX(), rbArr[0].getPos().getY() - heightInt_Test));
		for (int i = 0; i < windowWidth; i++)
		{
			window.setTextAtPoint(Vector2(i, windowHeight - 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
		window.setTextAtPoint(Vector2(0, windowHeight - 1), "T:Draw", BLACK_BRIGHTWHITE_BG);
		// TODO: ADD Rigidbody array = all nullcolours
		//		 TEST RIGIDBODYS
	}
	return window;

}

void GAME_RTW::inputVoids(int windowWidth, int windowHeight)
{
	if (GetKey('W')) {
		m_CursorPoint.addYSafe(-1,1, windowHeight - 2);
	}
	if (GetKey('A')) {
		m_CursorPoint.addXSafe(-2,0, windowWidth - 2);
	}
	if (GetKey('S')) {
		m_CursorPoint.addYSafe(1,1, windowHeight - 2);
	}
	if (GetKey('D')) {
		m_CursorPoint.addXSafe(2,0, windowWidth - 2);
	}
	if (GetKey('P')) {
		setPaintArrayAtPoint(m_CursorPoint,m_PaintColour);
		setPaintArrayAtPoint(Vector2(m_CursorPoint.getX() + 1, m_CursorPoint.getY()), m_PaintColour);
	}
	if (GetKey('C')) {
		nextColour();
	}
	if (GetKey(KeyCode_T)) {
		if (!KeyCode_T.getIsPressed()) {
			setUpTest(windowWidth, windowHeight);
			KeyCode_T.setPressed(true);
		}
	}
	else {
		KeyCode_T.setPressed(false);
	}
}

void GAME_RTW::inputVoidsWheelTest(int windowWidth, int windowHeight)
{
	if (GetKey(KeyCode_T)) {
		if (!KeyCode_T.getIsPressed()) {
			m_scene = "Draw_Wheel";
			KeyCode_T.setPressed(true);
		}
	}
	else {
		KeyCode_T.setPressed(false);
	}
}

void GAME_RTW::nextColour()
{
	colourcode++;
	if (colourcode >= m_paintColours.size()) {
		colourcode = 0;
	}
	m_PaintColour = m_paintColours[colourcode];
}

void GAME_RTW::setUpTest(int windowWidth, int windowHeight)
{
	m_scene = "Test_Wheel";
	rbArr = vector<RigidBody>();
	
	minX_Test = windowWidth;
	maxX_Test = 0;
	minY_Test = windowHeight;
	maxY_Test = 0;

	for (int q = 0; q < windowWidth; q++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			if (getColourArrayAtPoint(Vector2(q, m)) != NULLCOLOUR)
			{
				if (m < minY_Test) { 
					minY_Test = m; 
				}
				if (m > maxY_Test) { 
					maxY_Test = m; 
				}
				if (q < minX_Test) { 
					minX_Test = q; 
				}
				if (q > maxX_Test) {
					maxX_Test = q;
				}
			}
		}
	}
	vector<ColourClass> wheelArray = vector<ColourClass>();
	for (int z = minX_Test; z <= maxX_Test; z++)
	{
		for (int m = minY_Test; m <= maxY_Test; m++)
		{
			wheelArray.push_back(getColourArrayAtPoint(Vector2(z, m)));
		}
	}
	vector<vector<TextItem>> temp_temp;
	for (int i = minY_Test; i < maxY_Test + 1; i++)
	{
		vector<TextItem> temp;
		for (int ii = minX_Test; ii < maxX_Test + 2; ii++)
		{
			temp.push_back(TextItem(' ', getColourArrayAtPoint(Vector2(ii, i))));
		}
		temp_temp.push_back(temp);
	}
	widthInt_Test = (maxX_Test - minX_Test);
	heightInt_Test = (maxY_Test - minY_Test);
	//wheel.setAsset(widthInt_Test + 1, heightInt_Test + 1, wheelArray);
	//wheel.setAsset((maxX_Test - minX_Test) + 1, (maxY_Test - minY_Test) + 1, wheelArray);
	wheel.setAsset(temp_temp);
	m_WheelPoint = Vector2(10, 5);
	rbArr.push_back(PhysicsObject("player_001", m_WheelPoint, false, 0));
	for (int k = 0; k < windowWidth; k++)
	{
		rbArr.push_back(PhysicsObject("LowerGround" + to_string(k), Vector2(k, windowHeight - 5), true, 0));
	}

}

bool GAME_RTW::GetKey(char KeyCode)
{
	return GetAsyncKeyState(KeyCode) && 0x8000;
}
bool GAME_RTW::GetKey(GAME_RTW_KEYCODE key)
{
	return GetAsyncKeyState(key.getKeyCode()) && 0x8000;
}

GAME_RTW_PIXEL::GAME_RTW_PIXEL()
{
	m_color = NULLCOLOUR;
	m_point = Vector2(0, 0);
}

GAME_RTW_PIXEL::GAME_RTW_PIXEL(Vector2 a_Point)
{
	m_color = NULLCOLOUR;
	m_point = a_Point;
}
