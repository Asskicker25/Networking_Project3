#include "UDP_Client.h"



UDP_Client::UDP_Client()
{
}

UDP_Client::~UDP_Client()
{
}

void UDP_Client::InitializeClient(int clientId, const std::string& ipAddress, const int& port)
{

	this->ipAddress = ipAddress;
	this->port = port;
	this->clientID = clientId;

#pragma region StartUp

	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		std::cout << "Winsock initialization failed with error : " << result << std::endl;
		return;
	}

	std::cout << "Client : Winsock Initialized Successfully" << std::endl;

#pragma endregion

#pragma region SocketCreation

	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (serverSocket == INVALID_SOCKET) 
	{
		std::cout << "Client : Socket creation failed with error : " << WSAGetLastError() << std::endl;
		//cleanupEvents.Addfunction("WSACleanup", WSACleanup);
		//cleanupEvents.Invoke();
		return;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	addrLen = sizeof(addr);

	std::cout << "Address : " << addr.sin_addr.s_addr << std::endl;
	std::cout << "Port : " << addr.sin_port << std::endl;

	Multiplayer::Empty empty;
	empty.set_empty("Empty");

	std::string serializedString = SerializeWithCommandAndLengthPrefix(clientId, EMPTY, empty);

	result = sendto(serverSocket, serializedString.c_str(), serializedString.length(), 0, (SOCKADDR*)&addr, addrLen);

	if (result == SOCKET_ERROR)
	{
		std::cout << "Client : Sending message to Server failed with error : " << WSAGetLastError() << std::endl;
	}


#pragma endregion

#pragma region Threads

	std::thread serverSendThread([this]()
		{
			HandleCommandSend();
		});

	serverSendThread.detach();

	std::thread serverRecvThread([this]()
		{
			HandleCommandRecv();
		});

	serverRecvThread.detach();
	

#pragma endregion

	while (true)
	{
	}

	//cleanupEvents.Invoke();
	return;
}

void UDP_Client::HandleCommandRecv()
{
	int result, error;

	while (true)
	{
		char buffer[5];

		sockaddr_in address;
		int length = sizeof(address);
		
		result = recvfrom(serverSocket, buffer, 5, 0, (SOCKADDR*)&address, &length);

		if (result == SOCKET_ERROR) 
		{
			error = WSAGetLastError();
			std::cout << "Client: Receiving message from Server failed with error: " << error << std::endl;
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
					OnCommandReceived(commandData.id(), commandData);
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
	std::string serializedString = SerializeWithCommandAndLengthPrefix(clientID, command, message);

	listOfMessagesToSend.push(ClientToServerMessages{ serializedString });
}

