#pragma once
#include "SYDEKey.h"
#include <vector>
#include <string>
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
};