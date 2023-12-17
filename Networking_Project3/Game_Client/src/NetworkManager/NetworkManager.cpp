#include "NetworkManager.h"


NetworkManager::NetworkManager()
{
	model = new Model();
	phyObj = new PhysicsObject();
	client = new UDP_Client();

	InitializeEntity(this);

	client->OnCommandReceived = [this](int id, Multiplayer::CommandAndData command)
		{
			OnCommandRecv(id, command);
		};
}

void NetworkManager::Initialize()
{
	std::thread serverRecvThread([this]()
		{
			client->InitializeClient("127.0.0.1", 8412);
		});

	serverRecvThread.detach();
}


void NetworkManager::Start()
{
}

void NetworkManager::Update(float deltaTime)
{
}

void NetworkManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void NetworkManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void NetworkManager::OnCommandRecv(int id, Multiplayer::CommandAndData commandData)
{
}


Transform* NetworkManager::GetTransform()
{
	return model->GetTransform();
}

