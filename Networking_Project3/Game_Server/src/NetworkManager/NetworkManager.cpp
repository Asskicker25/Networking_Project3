#include "NetworkManager.h"
#include <Graphics/Timer.h>

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
	timeStep += Timer::GetInstance().deltaTime;

	if (timeStep > broadcastInterval)
	{
		timeStep = 0;
		BroadcastToClients();
	}

}

void NetworkManager::OnClientConnected(int id)
{
	Multiplayer::Player* player = gameScene.add_players();
	gameManager->AddPlayer(id);
	AddPlayerToList(id, player);
}

void NetworkManager::BroadcastToClients()
{

	std::unordered_map<int, GameObject*>::iterator it;

	for (it = gameManager->listOfPlayers.begin(); it != gameManager->listOfPlayers.end(); ++it)
	{

		Multiplayer::Player* player = listOfPlayers[it->first];

		player->set_state(0);
		player->set_clientid(it->first);
		player->set_allocated_position((GetVector3(it->second->model->transform.position)));
		player->set_allocated_rotation((GetVector3(it->second->model->transform.rotation)));
		player->set_allocated_color(GetVector3(it->second->model->meshes[0]->material->AsMaterial()->GetBaseColor()));
		player->set_allocated_velocity((GetVector3(it->second->phyObj->velocity)));

	}

	for (it = gameManager->listOfPlayers.begin(); it != gameManager->listOfPlayers.end(); ++it)
	{
		server->SendCommand(it->first, GAME_SCENE, gameScene);
	}

}


void NetworkManager::OnCommandRecv(int id, Multiplayer::CommandAndData commandData)
{
	Multiplayer::UserInput input;
	input.ParseFromString(commandData.data());

	std::cout << input.input() << std::endl;

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

void NetworkManager::AddPlayerToList(int id, Multiplayer::Player* player)
{
	listOfPlayers[id] = player;
}

bool NetworkManager::CheckIfPlayerExists(int id)
{
	std::unordered_map<int, Multiplayer::Player*>::iterator it = listOfPlayers.find(id);

	if (it == listOfPlayers.end())
	{
		return false;
	}
	return true;
}

