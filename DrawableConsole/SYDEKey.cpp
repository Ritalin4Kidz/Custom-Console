#include"pch.h"
#include "SYDEKey.h"

bool SYDEKey::GetKey()
{
	return GetAsyncKeyState(keyCode) && 0x8000;
}

bool SYDEKey::GetKey_Safe()
{
	return GetAsyncKeyState(keyCode) && 0x8000 && GetForegroundWindow() == GetConsoleWindow();
}

void SYDEKey::GetKeyDown()
{
	if (GetKey() && !isPressed)
	{
		isPressed = true;
		_STATE = KEYDOWN;
		return;
	}
	else if (GetKey()) {
		_STATE = KEY;
	}
}

void SYDEKey::GetKeyDown_Safe(HWND hWnd)
{
	if (GetForegroundWindow() != hWnd) { return; }
	if (GetKey() && !isPressed)
	{
		isPressed = true;
		_STATE = KEYDOWN;
		return;
	}
	else if (GetKey()) {
		_STATE = KEY;
	}
}

void SYDEKey::GetKeyUp()
{
	if (!GetKey() && isPressed)
	{
		isPressed = false;
		_STATE = KEYUP;
		return;
	}
	else if (!GetKey()) {
		_STATE = NONE;
	}
}

void SYDEKey::GetKeyUp_Safe(HWND hWnd)
{
	if (GetForegroundWindow() != hWnd) { return; }
	if (!GetKey() && isPressed)
	{
		isPressed = false;
		_STATE = KEYUP;
		return;
	}
	else if (!GetKey()) {
		_STATE = NONE;
	}
}

bool SYDEKey::_CompareState(SYDEKeyState m_State)
{
	if (m_State == KEY && _STATE == KEYDOWN)
	{
		return true;
	}
	return m_State == _STATE;
}

void SYDEKey::Reset()
{
	isPressed = false;
}

void SYDEKey::ForceKeyDown()
{
	if (_STATE == KEY) return;
	if (_STATE == KEYDOWN)
	{
		_STATE = KEY;
		return;
	}
	_STATE = KEYDOWN;
}

void SYDEKey::ForceKeyDownIfHeld()
{
	if (_STATE == KEYDOWN)
	{
		_STATE = KEY;
		return;
	}
}

void SYDEKey::ForceKeyUp()
{
	_STATE = KEYUP;
}


SYDEKey & SYDEKey::operator=(char KeyCode)
{
	this->keyCode = KeyCode;
	return *this;
}