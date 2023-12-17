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
}

void NetworkManager::Initialize()
{
	std::thread serverRecvThread([this]()
		{
			server->InitializeAndRunServer("127.0.0.1", 8017);
		});

	serverRecvThread.detach();
}

void NetworkManager::OnCommandRecv(int id, Multiplayer::CommandAndData commandData)
{
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

Transform* NetworkManager::GetTransform()
{
	return model->GetTransform();
}

