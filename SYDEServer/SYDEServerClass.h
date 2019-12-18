#pragma once

#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string>

// Need to link with Ws2_32.lib


class Server {
public:
	Server() {}
	virtual ~Server() {}

	int __cdecl main_server(void);

	std::string _GetMessage() { return Message; }

private:
	PCSTR _PORT = "27015";
	const int _BUFLEN = 512;
	std::string Message = "";
};
