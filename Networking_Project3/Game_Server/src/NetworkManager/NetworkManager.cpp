#include "NetworkManager.h"


NetworkManager::NetworkManager()
{
	model = new Model();
	phyObj = new PhysicsObject();
	server = new UDP_Server();

	InitializeEntity(this);

	server->OnCommandReceived = [this](int id, Multiplayer::CommandAndData command)
		{
			OnCommandRecv(id, command);
		};

	server->OnClientAdded = [this](int id)
		{
			OnClientConnected(id);
		};
}

void NetworkManager::Initialize()
{
	std::thread serverRecvThread([this]()
		{
			server->InitializeAndRunServer("127.0.0.1", 8412);
		});

	serverRecvThread.detach();
}

void NetworkManager::Start()
{
}

void NetworkManager::Update(float deltaTime)
{
}

void NetworkManager::OnCommandRecv(int id, Multiplayer::CommandAndData commandData)
{
	int result;

#pragma region Player

	if (commandData.command() == PLAYER)
	{
		Multiplayer::Player player;
		player.ParseFromString(commandData.data());

		PlayerData playerData;
		playerData.state = (PlayerState)player.state();
		playerData.pos = glm::vec3(player.position().x(), player.position().y(), player.position().z());
		playerData.rot = glm::vec3(player.rotation().x(), player.rotation().y(), player.rotation().z());
		playerData.vel = glm::vec3(player.velocity().x(), player.velocity().y(), player.velocity().z());

		AddPlayerToList(id, playerData);

		Debugger::Print("Player Pos :", playerData.pos);
	}

#pragma endregion

}

void NetworkManager::OnClientConnected(int id)
{
	gameManager->AddPlayer(id);
}


Transform* NetworkManager::GetTransform()
{
	return model->GetTransform();
}

void NetworkManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void NetworkManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}



void NetworkManager::AddPlayerToList(int id, const PlayerData& playerData)
{
	listOfPlayers[id] = playerData;
}

bool NetworkManager::CheckIfPlayerExists(int id)
{
	std::unordered_map<int, PlayerData>::iterator it = listOfPlayers.find(id);

	if (it == listOfPlayers.end())
	{
		return false;
	}
	return true;
}

