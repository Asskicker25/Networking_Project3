#include "NetworkManager.h"
#include "../Player/PlayerManager.h"

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

void NetworkManager::Initialize(int clientId)
{
	this->clientId = clientId;

	std::thread serverRecvThread([this]()
		{
			client->InitializeClient(this->clientId, "127.0.0.1", 8412);
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

	Multiplayer::GameScene gameScene;
	gameScene.ParseFromString(commandData.data());

	if (gameScene.players_size() > 0)
	{
		for (int i = 0; i < gameScene.players_size(); i++)
		{
			const Multiplayer::Player& player = gameScene.players(i);
			const Multiplayer::Bullet& bullet = gameScene.bullets(i);

			PlayerManager::GetInstance().AddPlayer(player.clientid());

			PlayerManager::GetInstance().UpdatePlayerState(player.clientid(), player);
			PlayerManager::GetInstance().UpdateBulletState(player.clientid(), bullet);

			UpdateGameObjectValue(
				PlayerManager::GetInstance().GetPlayer(player.clientid()), player, bullet);
		}
	}

}


void NetworkManager::UpdateGameObjectValue(Player* gameObject, const  Multiplayer::Player& player,
	const Multiplayer::Bullet& bullet)
{
	gameObject->model->isActive = player.state() == 0 ? true : false;
	gameObject->model->transform.SetPosition(GetGlmVector3(player.position()));
	gameObject->model->transform.SetRotation(GetGlmVector3(player.rotation()));
	gameObject->moveDir = GetGlmVector3(player.velocity());
	gameObject->model->meshes[0]->material->AsMaterial()->SetBaseColor(
		glm::vec4(GetGlmVector3(player.color()), 1.0f));

	if (bullet.state() == INACTIVE)
	{
		gameObject->bullet->model->isActive = false;
	}
	else
	{
		gameObject->bullet->model->isActive = true;
		gameObject->bullet->model->transform.SetPosition(GetGlmVector3(bullet.position()));
		gameObject->bullet->model->transform.SetRotation(GetGlmVector3(bullet.rotation()));
		gameObject->bullet->moveDir = GetGlmVector3(bullet.velocity());
		gameObject->bullet->model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(GetGlmVector3(player.color()), 1.0f));
	}
}


Transform* NetworkManager::GetTransform()
{
	return model->GetTransform();
}

