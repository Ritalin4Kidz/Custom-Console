#pragma once

#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
class Client {
public:
	Client() {}
	virtual ~Client() {}

	int __cdecl main_client(const char* message);

	void SetAddress(std::string _add) { _ADDRESS = _add; }

private:
	PCSTR _PORT = "27015";
	int _BUFLEN = 512;
	std::string _ADDRESS = "127.0.0.1";
};