#include "pch.h"
#include "SYDEDataSend.h"
void SYDEDataSend::SYDE_Send()
{
    SYDE_SendData(m_data);
    m_data.clear();
}

int SYDEDataSend::Connect(std::string ipAddr, int ipPort)
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (client_socket == INVALID_SOCKET) {
        //wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }


    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, (PCWSTR)(ipPort), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(27015);

    //----------------------
   // Connect to server.
    iResult = connect(client_socket, (SOCKADDR*)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR) {
        //wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        iResult = closesocket(client_socket);
        if (iResult == SOCKET_ERROR)
           // wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

   // wprintf(L"Connected to server.\n");

    iResult = closesocket(client_socket);
    if (iResult == SOCKET_ERROR) {
        //wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;

}

int SYDEDataSend::SYDE_SendData(const std::string& str)
{
    const char* data_ptr = str.data();
    std::size_t data_size = str.size();

    int bytes_sent;

    while (data_size > 0)
    {
        bytes_sent = send(client_socket, data_ptr, data_size, 0);
        if (bytes_sent == SOCKET_ERROR)
            return -1;

        data_ptr += bytes_sent;
        data_size -= bytes_sent;
    }

    return 1;
}
