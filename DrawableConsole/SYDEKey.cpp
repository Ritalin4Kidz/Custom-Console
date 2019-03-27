#include"pch.h"
#include "SYDEKey.h"

bool SYDEKey::GetKey()
{
	return GetAsyncKeyState(keyCode) && 0x8000;
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


SYDEKey & SYDEKey::operator=(char KeyCode)
{
	this->keyCode = KeyCode;
	return *this;
}