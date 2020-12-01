#pragma once
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#pragma comment(lib,"ws2_32")

class SYDEDataSend {
public:
	SYDEDataSend() { client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); Connect("127.0.0.1", 2011); }
	SYDEDataSend(SOCKET s) { client_socket = s; Connect("127.0.0.1", 2011);}
	virtual ~SYDEDataSend() {}

	/// <summary>
	/// Send all the data stored
	/// </summary>
	void SYDE_Send();

	void AddData(int i) { m_data += std::to_string(i); }
	void AddData(char c) { m_data += c; }
	void AddData(std::string s) { m_data += s; }

private:
protected:
	int Connect(std::string ipAddr, int ipPort);
	int SYDE_SendData(const std::string& str);
	SOCKET client_socket;
	std::string m_data;
};