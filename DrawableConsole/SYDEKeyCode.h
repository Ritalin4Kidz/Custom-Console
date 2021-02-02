#pragma once
#include "SYDEKey.h"
#include <vector>
#include <string>
#include "Vector2.h"
#include "Defaults.h"
class SYDEKeyCode {
public:
	/// <summary>
	/// check through the key array for key states
	/// </summary>
	/// <returns></returns>
	static std::string KeysDown();
	/// <summary>
	/// check through the key array for key states
	/// </summary>
	/// <returns></returns>
	static std::string KeysDownSafe();
	//All Keycodes recognised in SYDEKeyCode
	static std::vector<SYDEKey> KeyCodes;
	//Custom Keycode List, must enter all keys manually
	static std::vector<SYDEKey> KeyCodes_Optimized;
	/// <summary>
	/// Return the pressed key
	/// </summary>
	/// <param name="KeyCode"></param>
	/// <returns></returns>
	static SYDEKey get(char KeyCode);
	/// <summary>
	/// return the pressed key
	/// </summary>
	/// <param name="KeyCode"></param>
	/// <returns></returns>
	static SYDEKey get_key(char KeyCode);

	/// <summary>
	/// Get the current position of the mouse relative to the window
	/// </summary>
	/// <returns></returns>
	static Vector2 getMousePosition();

	//A Key
	static SYDEKey A;
	//B Key
	static SYDEKey B;
	//C Key
	static SYDEKey C;
	//D Key
	static SYDEKey D;
	//E Key
	static SYDEKey E;
	//F Key
	static SYDEKey F;
	//G Key
	static SYDEKey G;
	//H Key
	static SYDEKey H;
	//I Key
	static SYDEKey I;
	//J Key
	static SYDEKey J;
	//K Key
	static SYDEKey K;
	//L Key
	static SYDEKey L;
	//M Key
	static SYDEKey M;
	//N Key
	static SYDEKey N;
	//O Key
	static SYDEKey O;
	//P Key
	static SYDEKey P;
	//Q Key
	static SYDEKey Q;
	//R Key
	static SYDEKey R;
	//S Key
	static SYDEKey S;
	//T Key
	static SYDEKey T;
	//U Key
	static SYDEKey U;\
	//V Key
	static SYDEKey V;
	//W Key
	static SYDEKey W;
	//X Key
	static SYDEKey X;
	//Y Key
	static SYDEKey Y;
	//Z Key
	static SYDEKey Z;
	//Other Keys
	//Return Key
	static SYDEKey Return;
	//Backspace Key
	static SYDEKey Backspace;
	//Space Key
	static SYDEKey Space;
	//Left Arrow Key
	static SYDEKey ArrowLeft;
	//Right Arrow Key
	static SYDEKey ArrowRight;
	//Up Arrow Key
	static SYDEKey ArrowUp;
	//Down Arrow Key
	static SYDEKey ArrowDown;
	//Left Shift Key
	static SYDEKey LeftShift;
	//Right Shift Key
	static SYDEKey RightShift;
	//Left Tab Key
	static SYDEKey LeftTab;

	//MOUSE KEYS, OPTIONAL, ONLY IF CLICKING ENABLED
	//Mouse Left Click
	static SYDEKey LEFT_CLICK_MOUSE;
	//Mouse Right Click
	static SYDEKey RIGHT_CLICK_MOUSE;

	/// <summary>
	/// Initiate neccesary values for mouse movement, called in SYDEGamePlay during enableClicking function
	/// </summary>
	/// <param name="_offset"></param>
	/// <param name="_input"></param>
	/// <param name="_events"></param>
	/// <param name="_hin"></param>
	static void initMouseMovementVars(Vector2 _offset, INPUT_RECORD _input, DWORD _events, HANDLE _hin) { offset = _offset; InputRecord = _input; Events = _events; hin = _hin; }


	static void SetLastClickPosition(Vector2 v) { lastClickPosition = v; }
	static Vector2 GetLastClickPosition() { return lastClickPosition; }
private:
	static Vector2 lastMousePosition;
	static Vector2 lastClickPosition;
	static Vector2 offset;
	static INPUT_RECORD InputRecord;
	static DWORD Events;
	static HANDLE hin;
};