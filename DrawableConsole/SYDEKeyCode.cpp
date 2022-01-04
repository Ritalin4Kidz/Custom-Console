#include "pch.h"
#include "SYDEKeyCode.h"

SYDEKey SYDEKeyCode::SYDEKeyCode_A = SYDEKey('A');
SYDEKey SYDEKeyCode::SYDEKeyCode_B = SYDEKey('B');
SYDEKey SYDEKeyCode::SYDEKeyCode_C = SYDEKey('C');
SYDEKey SYDEKeyCode::SYDEKeyCode_D = SYDEKey('D');
SYDEKey SYDEKeyCode::SYDEKeyCode_E = SYDEKey('E');
SYDEKey SYDEKeyCode::SYDEKeyCode_F = SYDEKey('F');
SYDEKey SYDEKeyCode::SYDEKeyCode_G = SYDEKey('G');
SYDEKey SYDEKeyCode::SYDEKeyCode_H = SYDEKey('H');
SYDEKey SYDEKeyCode::SYDEKeyCode_I = SYDEKey('I');
SYDEKey SYDEKeyCode::SYDEKeyCode_J = SYDEKey('J');
SYDEKey SYDEKeyCode::SYDEKeyCode_K = SYDEKey('K');
SYDEKey SYDEKeyCode::SYDEKeyCode_L = SYDEKey('L');
SYDEKey SYDEKeyCode::SYDEKeyCode_M = SYDEKey('M');
SYDEKey SYDEKeyCode::SYDEKeyCode_N = SYDEKey('N');
SYDEKey SYDEKeyCode::SYDEKeyCode_O = SYDEKey('O');
SYDEKey SYDEKeyCode::SYDEKeyCode_P = SYDEKey('P');
SYDEKey SYDEKeyCode::SYDEKeyCode_Q = SYDEKey('Q');
SYDEKey SYDEKeyCode::SYDEKeyCode_R = SYDEKey('R');
SYDEKey SYDEKeyCode::SYDEKeyCode_S = SYDEKey('S');
SYDEKey SYDEKeyCode::SYDEKeyCode_T = SYDEKey('T');
SYDEKey SYDEKeyCode::SYDEKeyCode_U = SYDEKey('U');
SYDEKey SYDEKeyCode::SYDEKeyCode_V = SYDEKey('V');
SYDEKey SYDEKeyCode::SYDEKeyCode_W = SYDEKey('W');
SYDEKey SYDEKeyCode::SYDEKeyCode_X = SYDEKey('X');
SYDEKey SYDEKeyCode::SYDEKeyCode_Y = SYDEKey('Y');
SYDEKey SYDEKeyCode::SYDEKeyCode_Z = SYDEKey('Z');
//Other Keys
SYDEKey SYDEKeyCode::SYDEKeyCode_Return = SYDEKey(VK_RETURN);
SYDEKey SYDEKeyCode::SYDEKeyCode_Backspace = SYDEKey(VK_BACK);
SYDEKey SYDEKeyCode::SYDEKeyCode_Space = SYDEKey(VK_SPACE);
SYDEKey SYDEKeyCode::SYDEKeyCode_ArrowLeft = SYDEKey(VK_LEFT);
SYDEKey SYDEKeyCode::SYDEKeyCode_ArrowDown = SYDEKey(VK_DOWN);
SYDEKey SYDEKeyCode::SYDEKeyCode_ArrowUp = SYDEKey(VK_UP);
SYDEKey SYDEKeyCode::SYDEKeyCode_ArrowRight = SYDEKey(VK_RIGHT);
SYDEKey SYDEKeyCode::SYDEKeyCode_LeftShift = SYDEKey(VK_LSHIFT);
SYDEKey SYDEKeyCode::SYDEKeyCode_RightShift = SYDEKey(VK_RSHIFT);
SYDEKey SYDEKeyCode::SYDEKeyCode_LeftTab = SYDEKey(VK_TAB);
//MOUSE CLICK
SYDEKey SYDEKeyCode::SYDEKeyCode_LEFT_CLICK_MOUSE = SYDEKey(MOUSE_EVENT);
SYDEKey SYDEKeyCode::SYDEKeyCode_RIGHT_CLICK_MOUSE = SYDEKey(MOUSE_EVENT);
Vector2 SYDEKeyCode::lastMousePosition = Vector2(0);
Vector2 SYDEKeyCode::lastClickPosition = Vector2(0);
Vector2 SYDEKeyCode::offset = Vector2(0);
INPUT_RECORD SYDEKeyCode::InputRecord;
DWORD SYDEKeyCode::Events;
HANDLE SYDEKeyCode::hin;
std::vector<tempKey> SYDEKeyCode::KeysDownSafeVector = std::vector<tempKey>();

std::vector<SYDEKey> SYDEKeyCode::KeyCodes = {
	SYDEKeyCode_A,SYDEKeyCode_B,SYDEKeyCode_C,SYDEKeyCode_D,SYDEKeyCode_E,SYDEKeyCode_F,SYDEKeyCode_G,
	SYDEKeyCode_H,SYDEKeyCode_I,SYDEKeyCode_J,SYDEKeyCode_K,SYDEKeyCode_L,SYDEKeyCode_M,SYDEKeyCode_N,
	SYDEKeyCode_O,SYDEKeyCode_P,SYDEKeyCode_Q,SYDEKeyCode_R,SYDEKeyCode_S,SYDEKeyCode_T,SYDEKeyCode_U,
	SYDEKeyCode_V,SYDEKeyCode_W,SYDEKeyCode_X,SYDEKeyCode_Y,SYDEKeyCode_Z,
	SYDEKeyCode_Return,SYDEKeyCode_Backspace, SYDEKeyCode_Space, SYDEKeyCode_ArrowLeft, SYDEKeyCode_ArrowDown,
	SYDEKeyCode_ArrowUp, SYDEKeyCode_ArrowRight,SYDEKeyCode_LeftShift, SYDEKeyCode_RightShift, SYDEKeyCode_LeftTab
};

std::vector<SYDEKey> SYDEKeyCode::KeyCodes_Optimized = {};

std::string SYDEKeyCode::KeysDown()
{
	std::string m_return;
	for (char i = ' '; i <= '`'; i++) {
		if (GetAsyncKeyState(i) && 0x8000)
		{
			char addTxt = static_cast<char>(i);;
			m_return += addTxt;
		}
	}
	return m_return;
}

std::string SYDEKeyCode::KeysDownSafe()
{
	//NONE PRESSED
	for (int i = 0; i < KeysDownSafeVector.size(); i++)
	{
		KeysDownSafeVector[i].pressed = false;
	}
	HWND hWnd = GetConsoleWindow();
	bool inForeground = GetForegroundWindow() == hWnd;
	std::string m_return;
	if (!inForeground) { return ""; }
	for (char i = ' '; i <= '`'; i++) {
		if (GetAsyncKeyState(i))
		{
			bool canAdd = true;
			for (int ii = 0; ii < KeysDownSafeVector.size(); ii++)
			{
				if (KeysDownSafeVector[ii].key == i)
				{
					KeysDownSafeVector[ii].pressed = true;
					canAdd = false;
				}
			}
			if (canAdd)
			{
				bool b_Shift = ((GetAsyncKeyState(VK_LSHIFT) & -32768) || (GetAsyncKeyState(VK_RSHIFT))) ? true : false;
				bool b_Capital = (GetAsyncKeyState(VK_CAPITAL) & 1) ? true : false;
				bool b_should_upper = (b_Capital && !b_Shift) || (!b_Capital && b_Shift);
				char addTxt = static_cast<char>(i);
				KeysDownSafeVector.push_back(tempKey(addTxt, true));
				if (!b_should_upper)
				{
					addTxt = tolower(addTxt);
				}
				m_return += addTxt;
			}
		}
	}
	//REMOVE NOT PRESSED
	for (int i = 0; i < KeysDownSafeVector.size(); i++)
	{
		if (KeysDownSafeVector[i].pressed == false)
		{
			KeysDownSafeVector.erase(KeysDownSafeVector.begin() + i);
			i--;
		}
	}
	return m_return;
}

bool SYDEKeyCode::getBackSpaceSafe()
{
	HWND hWnd = GetConsoleWindow();
	bool inForeground = GetForegroundWindow() == hWnd;
	std::string m_return;
	if (!inForeground) { return false; }
	if (GetAsyncKeyState(VK_BACK))
	{
		return true;
	}
	return false;
}

SYDEKey SYDEKeyCode::get(char KeyCode)
{
	for (int i = 0; i < KeyCodes.size(); i++)
	{
		if (KeyCodes[i].getKeyCode() == KeyCode) {
			return KeyCodes[i];
		}
	}
	KeyCodes.push_back(
		SYDEKey(KeyCode) //KEY DOESN'T EXIST, HOW ABOUT WE ADD IT
	);
	return KeyCodes[KeyCodes.size() - 1];
}

SYDEKey SYDEKeyCode::get_key(char KeyCode)
{
	for (int i = 0; i < KeyCodes_Optimized.size(); i++)
	{
		if (KeyCodes_Optimized[i].getKeyCode() == KeyCode) {
			return KeyCodes_Optimized[i];
		}
	}
	return SYDEKey('~');
}

Vector2 SYDEKeyCode::getMousePosition()
{
	if (WaitForSingleObject(hin, SYDEDefaults::mouseInputWaitTime) == WAIT_OBJECT_0)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);
		lastMousePosition = Vector2(InputRecord.Event.MouseEvent.dwMousePosition.X - offset.getX(), InputRecord.Event.MouseEvent.dwMousePosition.Y - offset.getY());
	}
	return lastMousePosition;
}
