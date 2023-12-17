#pragma once

// WinSock2 Windows Sockets
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <conio.h>
#include <map>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <thread>
#include <queue>

#include "Events.h"
#include "MessageUtilities.h"

// Need to link Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "8412"

struct ServerToClientMessages
{
	int id = -1;
	LengthPrefixedMessage message;
};

class UDP_Server
{
private:

	int result;
	bool serverInitialized = false;

	std::string ipAddress;
	int port;

	WSAData wsaData;
	SOCKET listenSocket;

	Events cleanupEvents;

	int clientInfoLength = sizeof(sockaddr_in);

	std::unordered_map<int, sockaddr_in> listOfClients;
	std::queue<ServerToClientMessages> listOfMessagesToSend;

	void HandleCommandRecv();
	void HandleCommandSend();
	bool ClientExists(int id);

public:

	UDP_Server();
	~UDP_Server();

	void InitializeAndRunServer(const std::string& ipAddress, const int& port);
	void SendCommand(int id, const Command& command, const google::protobuf::Message& message);


	std::function<void(int, Multiplayer::CommandAndData)> OnCommandReceived = nullptr;
	std::function<void(int)> OnClientAdded = nullptr;

};

