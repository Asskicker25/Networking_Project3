#include "UDP_Server.h"



UDP_Server::UDP_Server()
{
}

UDP_Server::~UDP_Server()
{
}

void UDP_Server::InitializeAndRunServer(const std::string& ipAddress, const int& port)
{
	this->ipAddress = ipAddress;
	this->port = port;

#pragma region Startup

	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		std::cout << " Server : Winsock initialization failed with error : " << result << std::endl;
		system("Pause");
		return;
	}

	serverInitialized = true;

#pragma endregion

#pragma region SocketCreation


	listenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (listenSocket == INVALID_SOCKET)
	{
		std::cout << "Server : Socket creation failed with error : " << WSAGetLastError() << std::endl;
		cleanupEvents.Addfunction("WSACleanup", WSACleanup);
		cleanupEvents.Invoke();
		return;
	}

	std::cout << "Server : Socket created Successfully" << std::endl;

#pragma endregion

#pragma region Bind

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());

	std::cout << "Address : " << addr.sin_addr.s_addr << std::endl;
	std::cout << "Port : " << addr.sin_port << std::endl;

	result = bind(listenSocket, (SOCKADDR*)&addr, sizeof(addr));
	if (result == SOCKET_ERROR)
	{
		std::cout << "Server : Binding socked failed with error : " << WSAGetLastError() << std::endl;
		cleanupEvents.Addfunction("Close Socket", [this]()
			{
				closesocket(listenSocket);
			});
		cleanupEvents.Invoke();
		return;
	}

	std::cout << "Server : Binding socket successful " << std::endl;

#pragma endregion

#pragma region Threads

	std::thread handleRecvCommand([this]()
		{
			HandleCommandRecv();
		});

	handleRecvCommand.detach();

	std::thread sendMessagesToClient([this]()
		{
			HandleCommandSend();
		});

	sendMessagesToClient.detach();

#pragma endregion


	while (true)
	{
	}

	cleanupEvents.Invoke();

	return;
}

void UDP_Server::HandleCommandRecv()
{
	int result, error;

	const int bufferSize = 10;

	while (true)
	{
		char buffer[bufferSize] = "";

		sockaddr_in clientInfo;

		result = recvfrom(listenSocket, buffer, bufferSize, 0, (SOCKADDR*)&clientInfo, &clientInfoLength);

		if (result == SOCKET_ERROR)
		{
			error = WSAGetLastError();
			std::cout << "Server : Receiving message from Client failed with error : " << error << std::endl;
		}
		else
		{
			if (result > 0)
			{
				Multiplayer::CommandAndData commandData;
				commandData.ParseFromArray(buffer, bufferSize);

				if (!ClientExists(commandData.clientid()))
				{
					listOfClients[commandData.clientid()] = clientInfo;
					OnClientAdded(commandData.clientid());
				}

				OnCommandReceived(commandData.clientid(), commandData);
			}
			else
			{
				std::cout << "Server : Message Parsing failed " << std::endl;
			}
		}
			

	}
}

void UDP_Server::HandleCommandSend()
{
	int result, error;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		if (listOfMessagesToSend.size() > 0)
		{
			ServerToClientMessages message = listOfMessagesToSend.front();
			listOfMessagesToSend.pop();

			sockaddr_in clientInfo = listOfClients[message.id];

			result = sendto(listenSocket, message.message.message.c_str(), message.message.message.size(), 0, (SOCKADDR*)&clientInfo, clientInfoLength);

			if (result == SOCKET_ERROR)
			{
				std::cout << "Server : Sending message to Client failed with error : " << WSAGetLastError() << std::endl;
			}
		}
	}
}

bool UDP_Server::ClientExists(int id)
{
	std::unordered_map<int, sockaddr_in>::iterator it = listOfClients.find(id);

	if (it == listOfClients.end())
	{
		return false;
	}
	return true;
}

void UDP_Server::SendCommand(int id, const Command& command, const google::protobuf::Message& message)
{
	LengthPrefixedMessage serializedString = SerializeWithCommandAndLengthPrefix(id, command, message);

	listOfMessagesToSend.push(ServerToClientMessages{ id,serializedString });
}

