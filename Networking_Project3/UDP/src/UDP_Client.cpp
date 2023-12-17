#include "UDP_Client.h"



UDP_Client::UDP_Client()
{
}

UDP_Client::~UDP_Client()
{
}

void UDP_Client::InitializeClient(const std::string& ipAddress, const int& port)
{

	this->ipAddress = ipAddress;
	this->port = port;

#pragma region StartUp

	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		std::cout << "Winsock initialization failed with error : " << result << std::endl;
		return;
	}

	std::cout << "Client : Winsock Initialized Successfully" << result << std::endl;

#pragma endregion

#pragma region SocketCreation

	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (serverSocket == INVALID_SOCKET) 
	{
		std::cout << "Client : Socket creation failed with error : " << WSAGetLastError() << std::endl;
		cleanupEvents.Addfunction("WSACleanup", WSACleanup);
		cleanupEvents.Invoke();
		return;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	addrLen = sizeof(addr);

#pragma endregion

#pragma region Threads

	std::thread serverRecvThread([this]()
		{
			HandleCommandRecv();
		});

	serverRecvThread.detach();

	std::thread serverSendThread([this]()
		{
			HandleCommandSend();
		});

	serverSendThread.detach();

#pragma endregion

	while (true)
	{
	}

	cleanupEvents.Invoke();
	return;
}

void UDP_Client::HandleCommandRecv()
{
	int result, error;

	while (true)
	{
		char buffer[5];
		int32_t messageLength;

		result = recvfrom(serverSocket, buffer, 5, 0, (SOCKADDR*)&addr, &addrLen);

		if (result == SOCKET_ERROR)
		{
			error = WSAGetLastError();
			std::cout << "Client : Receiving message from Server failed with error : " << WSAGetLastError() << std::endl;
			closesocket(serverSocket);
		}
		else
		{
			Multiplayer::LengthPrefix lengthPrefix;

			lengthPrefix.ParseFromArray(buffer, 5);

			std::string serializedMessageData(lengthPrefix.messagelength(), '\0');

			result = recvfrom(serverSocket, &serializedMessageData[0], lengthPrefix.messagelength(), 0, (SOCKADDR*)&addr, &addrLen);

			if (result > 0)
			{
				Multiplayer::CommandAndData commandData;

				if (commandData.ParseFromString(serializedMessageData))
				{
					OnCommandReceived(commandData);
				}
				else
				{
					std::cout << "Client :Message Parsing failed " << std::endl;
				}
			}
		}
	}
}

void UDP_Client::HandleCommandSend()
{
	int result, error;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		if (listOfMessagesToSend.size() > 0)
		{
			ClientToServerMessages message = listOfMessagesToSend.front();
			listOfMessagesToSend.pop();

			result = sendto(serverSocket, message.message.c_str(), message.message.size(), 0, (SOCKADDR*)&addr, addrLen);

			if (result == SOCKET_ERROR)
			{
				std::cout << "Client : Sending message to Server failed with error : " << WSAGetLastError() << std::endl;
			}
		}
	}
}

void UDP_Client::SendCommand(const Command& command, const google::protobuf::Message& message)
{
	std::string serializedString = SerializeWithCommandAndLengthPrefix(command, message);

	listOfMessagesToSend.push(ClientToServerMessages{ serializedString });
}

