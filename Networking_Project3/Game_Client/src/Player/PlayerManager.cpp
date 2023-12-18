#include "PlayerManager.h"
#include "../Bullet/BulletManager.h"

PlayerManager::PlayerManager()
{
	playFactory = new PlayerFactory();

	InitializeEntity(this);
}

PlayerManager& PlayerManager::GetInstance()
{
	static PlayerManager instance;
	return instance;
}

Player* PlayerManager::CreatePlayer()
{
	Player* player = playFactory->CreatePlayer();
	return player;
}

void PlayerManager::AddPlayer(int id)
{
	if (CheckIfPlayerExists(id)) return;

	Player* player = CreatePlayer();
	Bullet* bullet = BulletManager::GetInstance().CreateBullet();

	player->bullet = bullet;

	listOfPlayers[id] = player;

	if (id == clientId)
	{
		playerController->SetPlayer(player);
	}
}

bool PlayerManager::CheckIfPlayerExists(int id)
{
	std::unordered_map<int, Player*>::iterator it = listOfPlayers.find(id);

	if (it == listOfPlayers.end())
	{
		return false;
	}

	return true;
}

Player* PlayerManager::GetPlayer(int id)
{
	return listOfPlayers[id];
}

Transform* PlayerManager::GetTransform()
{
	return nullptr;
}

void PlayerManager::Print()
{
	std::cout << "Client Player Manager Init" << std::endl;
}


void PlayerManager::Start()
{
}

void PlayerManager::Update(float deltaTime)
{
}

void PlayerManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	playFactory->AssignComponents(renderer, shader, physicsEngine);
}

void PlayerManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
