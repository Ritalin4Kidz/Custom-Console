#pragma once
#include <windows.h>
class SYDEKey {
public:
	SYDEKey(char a_keyCode) { keyCode = a_keyCode; }
	virtual ~SYDEKey() {}

	//Usage of getKey()
	/*
		GetKey() - get if key is down
		GetKeyDown(bool using_GetKeyUp) - check if key is down on frame, set param to true if keyUp is used in same frame
		GetKeyUp(bool using_GetKeyDown) - check if key is up on frame, set param to true if keyDown is used in same frame
	*/
	bool GetKey();
	bool GetKeyDown(bool using_GetKeyUp);
	bool GetKeyUp(bool using_GetKeyDown);

	void Reset();

	SYDEKey& operator=(char KeyCode);

private:
	bool isPressed = false;
	char keyCode;
};