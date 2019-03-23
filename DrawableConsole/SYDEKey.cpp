#include"pch.h"
#include "SYDEKey.h"

bool SYDEKey::GetKey()
{
	return GetAsyncKeyState(keyCode) && 0x8000;
}

bool SYDEKey::GetKeyDown(bool using_GetKeyUp)
{
	if (GetKey() && !isPressed)
	{
		isPressed = true;
		return true;
	}
	if (!using_GetKeyUp)
	{
		if (!GetKey()) {
			isPressed = false;
		}
	}
	return false;
}

bool SYDEKey::GetKeyUp(bool using_GetKeyDown)
{
	if (!GetKey() && isPressed)
	{
		isPressed = false;
		return true;
	}
	if (!using_GetKeyDown)
	{
		if (GetKey()) {
			isPressed = true;
		}
	}
	return false;
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