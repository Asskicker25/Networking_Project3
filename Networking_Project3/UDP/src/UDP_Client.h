#pragma once


// WinSock2 Windows Sockets
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <map>
#include <vector>
#include <thread>
#include <queue>

#include "Events.h"
#include "MessageUtilities.h"

#pragma comment(lib, "Ws2_32.lib")

struct ClientToServerMessages
{
	std::string message;
};

class UDP_Client
{

private:

	SOCKET serverSocket;
	WSAData wsaData;

	//Events cleanupEvents;

	int result, error, addrLen;

	std::string ipAddress;
	int port;

	sockaddr_in addr;

	std::queue<ClientToServerMessages> listOfMessagesToSend;

	void HandleCommandRecv();
	void HandleCommandSend();

public:
	UDP_Client();
	~UDP_Client();

	void InitializeClient(const std::string& ipAddress, const int& port);

	void SendCommand(const Command& command, const google::protobuf::Message& message);

	std::function<void(int id, Multiplayer::CommandAndData)> OnCommandReceived = nullptr;
};

