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
#include <queue>

#include "Events.h"
#include "MessageUtilities.h"

#pragma comment(lib, "Ws2_32.lib")


class UDP_Client
{

private:

	SOCKET serverSocket;
	WSAData wsaData;

	//Events cleanupEvents;

	int result, error, addrLen;
	int clientID = 0;
	int port;

	static const int NUM_OF_PLAYER = 4;
	static const int PLAYER_SIZE = 129;
	static const int COMMAND_SIZE = 7;

	std::string ipAddress;
	sockaddr_in addr;


	std::queue<LengthPrefixedMessage> listOfMessagesToSend;

	void HandleCommandRecv();
	void HandleCommandSend();

public:
	UDP_Client();
	~UDP_Client();

	void InitializeClient(int clientId, const std::string& ipAddress, const int& port);

	void SendCommand(const Command& command, const google::protobuf::Message& message);

	std::function<void(int id, Multiplayer::CommandAndData)> OnCommandReceived = nullptr;
};

