#include "pch.h"
#include "SYDEKeyCode.h"

SYDEKey SYDEKeyCode::A = SYDEKey('A');
SYDEKey SYDEKeyCode::B = SYDEKey('B');
SYDEKey SYDEKeyCode::C = SYDEKey('C');
SYDEKey SYDEKeyCode::D = SYDEKey('D');
SYDEKey SYDEKeyCode::E = SYDEKey('E');
SYDEKey SYDEKeyCode::F = SYDEKey('F');
SYDEKey SYDEKeyCode::G = SYDEKey('G');
SYDEKey SYDEKeyCode::H = SYDEKey('H');
SYDEKey SYDEKeyCode::I = SYDEKey('I');
SYDEKey SYDEKeyCode::J = SYDEKey('J');
SYDEKey SYDEKeyCode::K = SYDEKey('K');
SYDEKey SYDEKeyCode::L = SYDEKey('L');
SYDEKey SYDEKeyCode::M = SYDEKey('M');
SYDEKey SYDEKeyCode::N = SYDEKey('N');
SYDEKey SYDEKeyCode::O = SYDEKey('O');
SYDEKey SYDEKeyCode::P = SYDEKey('P');
SYDEKey SYDEKeyCode::Q = SYDEKey('Q');
SYDEKey SYDEKeyCode::R = SYDEKey('R');
SYDEKey SYDEKeyCode::S = SYDEKey('S');
SYDEKey SYDEKeyCode::T = SYDEKey('T');
SYDEKey SYDEKeyCode::U = SYDEKey('U');
SYDEKey SYDEKeyCode::V = SYDEKey('V');
SYDEKey SYDEKeyCode::W = SYDEKey('W');
SYDEKey SYDEKeyCode::X = SYDEKey('X');
SYDEKey SYDEKeyCode::Y = SYDEKey('Y');
SYDEKey SYDEKeyCode::Z = SYDEKey('Z');
//Other Keys
SYDEKey SYDEKeyCode::Return = SYDEKey(VK_RETURN);
SYDEKey SYDEKeyCode::Backspace = SYDEKey(VK_BACK);
SYDEKey SYDEKeyCode::Space = SYDEKey(VK_SPACE);
SYDEKey SYDEKeyCode::ArrowLeft = SYDEKey(VK_LEFT);
SYDEKey SYDEKeyCode::ArrowDown = SYDEKey(VK_DOWN);
SYDEKey SYDEKeyCode::ArrowUp = SYDEKey(VK_UP);
SYDEKey SYDEKeyCode::ArrowRight = SYDEKey(VK_RIGHT);
SYDEKey SYDEKeyCode::LeftShift = SYDEKey(VK_LSHIFT);
SYDEKey SYDEKeyCode::RightShift = SYDEKey(VK_RSHIFT);

std::vector<SYDEKey> SYDEKeyCode::KeyCodes = {
	A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,
	Q,R,S,T,U,V,W,X,Y,Z,Return,Backspace,
	Space, ArrowLeft, ArrowDown, ArrowUp,
	ArrowRight,LeftShift, RightShift
};

std::string SYDEKeyCode::KeysDown()
{
	std::string m_return;
	for (char i = ' '; i <= '`'; i++) {
		if (GetAsyncKeyState(i))
		{
			char addTxt = static_cast<char>(i);;
			m_return += addTxt;
		}
	}
	return m_return;
}

SYDEKey SYDEKeyCode::get(char KeyCode)
{
	for (int i = 0; i < KeyCodes.size(); i++)
	{
		if (KeyCodes[i].getKeyCode() == KeyCode) {
			return KeyCodes[i];
		}
	}
	return KeyCodes[0]; //TODO Create Null KeyCode
}
