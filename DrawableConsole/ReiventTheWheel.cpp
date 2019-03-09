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
		//CHECK RIGIDBODY IS STABLE
		vector<RigidBody> playerChildren;
		for (int i = 1; i < rbPixelsPlayer; i++)
		{
			playerChildren.push_back(rbArr[i]);
		}
		rbArr[0].gravityChildren(rbArr, playerChildren);
		//THEN CHECK INPUT, FOR GRAVITY LATER (DUE TO MANIPULATION OF SPEED)
		inputVoidsWheelTest(windowWidth, windowHeight);
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
		for (int i = 0; i < rbArr.size(); i++)
		{
			//rbArr[i].gravity(rbArr);
			//rbArr[i].gravity(playerRigidBody);
			if (rbArr[i].getTag() == "Asterix") {
				window.setTextAtPoint(rbArr[i].getPos(), "*", determineColour_RTW(RED, window.getTextColourAtPoint(rbArr[i].getPos())));
			}

			rbArr[i].gravity(rbArr);
		}
		//for (int i = 0; i < rbPixelsPlayer; i++) {
		//	if (rbArr[i].checkArrayForHit(rbArr)) {
		//		rbArr[0].setSpeed(0);
		//	}
		//}
		window = wheel.draw_asset(window, Vector2(rbArr[0].getPos().getX(), rbArr[0].getPos().getY() - heightInt_Test));
		rbArr = rbArrMove(rbArr, rbArr[0].getPos(), 1, rbPixelsPlayer);
		for (int i = 0; i < windowWidth; i++)
		{
			window.setTextAtPoint(Vector2(i, windowHeight - 1), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
		for (int i = 0; i < rbPixelsPlayer; i++) {
			if (showHitbox) {
				window.setTextAtPoint(rbArr[i].getPos(), " ", BRIGHTWHITE_BRIGHTGREEN_BG);
			}
			//playerRigidBody[i].gravity(rbArr);
			//playerRigidBody[i].gravity(playerRigidBody);
		}
		window.setTextAtPoint(Vector2(0, windowHeight - 1), "T:Draw,WAD:Move,H:Hitbox,Speed:" + to_string(rbArr[0].getSpeed()), BLACK_BRIGHTWHITE_BG);
		// TODO: ADD Rigidbody array = all nullcolours
		//		 TEST RIGIDBODYS
	}
	return window;

}

ColourClass GAME_RTW::determineColour_RTW(ColourClass main, ColourClass bg)
{
	if (bg >= BLACK_BLUE_BG && bg < BLACK_GREEN_BG)
	{
		return (ColourClass)(main + BLACK_BLUE_BG);
	}

	if (bg >= BLACK_GREEN_BG && bg < BLACK_AQUA_BG)
	{
		return (ColourClass)(main + BLACK_GREEN_BG);
	}

	if (bg >= BLACK_AQUA_BG && bg < BLACK_RED_BG)
	{
		return (ColourClass)(main + BLACK_AQUA_BG);
	}

	if (bg >= BLACK_RED_BG && bg < BLACK_PURPLE_BG)
	{
		return (ColourClass)(main + BLACK_RED_BG);
	}

	if (bg >= BLACK_PURPLE_BG && bg < BLACK_YELLOW_BG)
	{
		return (ColourClass)(main + BLACK_PURPLE_BG);
	}

	if (bg >= BLACK_YELLOW_BG && bg < BLACK_WHITE_BG)
	{
		return (ColourClass)(main + BLACK_YELLOW_BG);
	}

	if (bg >= BLACK_WHITE_BG && bg < BLACK_LIGHTGREY_BG)
	{
		return (ColourClass)(main + BLACK_WHITE_BG);
	}

	if (bg >= BLACK_LIGHTGREY_BG && bg < BLACK_DARKBLUE_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTGREY_BG);
	}

	if (bg >= BLACK_DARKBLUE_BG && bg < BLACK_BRIGHTGREEN_BG)
	{
		return (ColourClass)(main + BLACK_DARKBLUE_BG);
	}

	if (bg >= BLACK_BRIGHTGREEN_BG && bg < BLACK_LIGHTBLUE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTGREEN_BG);
	}

	if (bg >= BLACK_LIGHTBLUE_BG && bg < BLACK_BRIGHTRED_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTBLUE_BG);
	}

	if (bg >= BLACK_BRIGHTRED_BG && bg < BLACK_LIGHTPURPLE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTRED_BG);
	}

	if (bg >= BLACK_LIGHTPURPLE_BG && bg < BLACK_BRIGHTYELLOW_BG)
	{
		return (ColourClass)(main + BLACK_LIGHTPURPLE_BG);
	}

	if (bg >= BLACK_BRIGHTYELLOW_BG && bg < BLACK_BRIGHTWHITE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTYELLOW_BG);
	}

	if (bg >= BLACK_BRIGHTWHITE_BG && bg <= BRIGHTWHITE_BRIGHTWHITE_BG)
	{
		return (ColourClass)(main + BLACK_BRIGHTWHITE_BG);
	}
	return main;
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
	if (GetKey('O')) {
		nextChar();
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
	if (GetKey('A')) {
		rbArr[0].setPosition(rbArr[0].getPos() + Vector2(-1,0));
	}
	if (GetKey('D')) {
		rbArr[0].setPosition(rbArr[0].getPos() + Vector2(1, 0));
	}
	if (GetKey('H')) {
		showHitbox = !showHitbox;
	}
	if (GetKey(KeyCode_T)) {
		if (!KeyCode_T.getIsPressed()) {
			m_scene = "Draw_Wheel";
			KeyCode_T.setPressed(true);
		}
	}
	else {
		KeyCode_T.setPressed(false);
	}
	if (GetKey(KeyCode_W))
	{
		if (!KeyCode_W.getIsPressed()) {
			if (rbArr[0].getSpeed() == 0)
			{
				rbArr[0].setSpeed(-3);
			}
			KeyCode_T.setPressed(true);
		}
	}
	else {
		KeyCode_W.setPressed(false);
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

void GAME_RTW::nextChar()
{
	charcode++;
	if (charcode >= m_details.size()) {
		charcode = 0;
	}
}

void GAME_RTW::setUpTest(int windowWidth, int windowHeight)
{
	m_scene = "Test_Wheel";
	rbArr = vector<RigidBody>();
	
	minX_Test = windowWidth;
	maxX_Test = 0;
	minY_Test = windowHeight;
	maxY_Test = 0;
	playerRigidBody = vector<RigidBody>();
	rbPixelsPlayer = 0;
	//TODO, FIX HITBOX ALIGNMENT ON BIGGER DRAWINGS
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
				//playerRigidBody.push_back(PhysicsObject("playerRB", Vector2(q, m), false, 0));
				//rbArr.push_back(PhysicsObject("playerRB" + to_string(q) + "," + to_string(m), m_WheelPoint, false, 0));
				rbArr.push_back(PhysicsObject("playerRB", Vector2(q, m), false, 0));
				if (rbPixelsPlayer != 0) {
					rbArr[rbArr.size() - 1].setParentPos(rbArr[0].getPos());
					rbArr[rbArr.size() - 1].setConstantSpeed(true, 0.0f);
					rbArr[rbArr.size() - 1].setKinematic(true);
				}
				rbPixelsPlayer++;
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
	//rbArr.push_back(PhysicsObject("playerRB", m_WheelPoint, false, 0));
	for (int k = 0; k < windowWidth; k++)
	{
		rbArr.push_back(PhysicsObject("LowerGround" + to_string(k), Vector2(k, windowHeight - 5), true, 0));
	}
	PhysicsObject testRb("Test_RigidBody", Vector2(26, windowHeight - 7), true, 0);
	testRb.setTag("Asterix");
	rbArr.push_back(testRb);
	//RIGIDBOIES ON PLAYER ARE FUCKED YO
}

bool GAME_RTW::GetKey(char KeyCode)
{
	return GetAsyncKeyState(KeyCode) && 0x8000;
}
bool GAME_RTW::GetKey(GAME_RTW_KEYCODE key)
{
	return GetAsyncKeyState(key.getKeyCode()) && 0x8000;
}


vector<RigidBody> GAME_RTW::rbArrMove(vector<RigidBody> rbArr, Vector2 parent, int start, int end)
{
	for (int i = start; i < end; i++) {
		rbArr[i].setPosition(Vector2(parent.getX() - rbArr[i].getDifference().getX(), (parent.getY() - rbArr[i].getDifference().getY()) - heightInt_Test));
	}
	return rbArr;
}

void GAME_RTW::moveWheel(Vector2 direction)
{
	for (int i = 0; i < rbPixelsPlayer; i++) {
		rbArr[i].setPosition(rbArr[i].getPos() + direction);
	}
}

void GAME_RTW::jumpWheel()
{
	for (int i = 0; i < rbPixelsPlayer; i++) {
		if (rbArr[i].getSpeed() == 0)
		{
			rbArr[i].setSpeed(-3);
		}
	}
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
