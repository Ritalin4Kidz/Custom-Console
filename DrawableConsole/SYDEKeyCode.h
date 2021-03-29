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
	static SYDEKey SYDEKeyCode_A;
	//B Key
	static SYDEKey SYDEKeyCode_B;
	//C Key
	static SYDEKey SYDEKeyCode_C;
	//D Key
	static SYDEKey SYDEKeyCode_D;
	//E Key
	static SYDEKey SYDEKeyCode_E;
	//F Key
	static SYDEKey SYDEKeyCode_F;
	//G Key
	static SYDEKey SYDEKeyCode_G;
	//H Key
	static SYDEKey SYDEKeyCode_H;
	//I Key
	static SYDEKey SYDEKeyCode_I;
	//J Key
	static SYDEKey SYDEKeyCode_J;
	//K Key
	static SYDEKey SYDEKeyCode_K;
	//L Key
	static SYDEKey SYDEKeyCode_L;
	//M Key
	static SYDEKey SYDEKeyCode_M;
	//N Key
	static SYDEKey SYDEKeyCode_N;
	//O Key
	static SYDEKey SYDEKeyCode_O;
	//P Key
	static SYDEKey SYDEKeyCode_P;
	//Q Key
	static SYDEKey SYDEKeyCode_Q;
	//R Key
	static SYDEKey SYDEKeyCode_R;
	//S Key
	static SYDEKey SYDEKeyCode_S;
	//T Key
	static SYDEKey SYDEKeyCode_T;
	//U Key
	static SYDEKey SYDEKeyCode_U;
	//V Key
	static SYDEKey SYDEKeyCode_V;
	//W Key
	static SYDEKey SYDEKeyCode_W;
	//X Key
	static SYDEKey SYDEKeyCode_X;
	//Y Key
	static SYDEKey SYDEKeyCode_Y;
	//Z Key
	static SYDEKey SYDEKeyCode_Z;
	//Other Keys
	//Return Key
	static SYDEKey SYDEKeyCode_Return;
	//Backspace Key
	static SYDEKey SYDEKeyCode_Backspace;
	//Space Key
	static SYDEKey SYDEKeyCode_Space;
	//Left Arrow Key
	static SYDEKey SYDEKeyCode_ArrowLeft;
	//Right Arrow Key
	static SYDEKey SYDEKeyCode_ArrowRight;
	//Up Arrow Key
	static SYDEKey SYDEKeyCode_ArrowUp;
	//Down Arrow Key
	static SYDEKey SYDEKeyCode_ArrowDown;
	//Left Shift Key
	static SYDEKey SYDEKeyCode_LeftShift;
	//Right Shift Key
	static SYDEKey SYDEKeyCode_RightShift;
	//Left Tab Key
	static SYDEKey SYDEKeyCode_LeftTab;

	//MOUSE KEYS, OPTIONAL, ONLY IF CLICKING ENABLED
	//Mouse Left Click
	static SYDEKey SYDEKeyCode_LEFT_CLICK_MOUSE;
	//Mouse Right Click
	static SYDEKey SYDEKeyCode_RIGHT_CLICK_MOUSE;

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