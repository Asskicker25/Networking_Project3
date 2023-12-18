#include "PlayerManager.h"
#include "../Bullet/BulletManager.h"
#include <Graphics/Timer.h>

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
	player->clientId = id;

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

void PlayerManager::PositionPredictor()
{
	std::unordered_map<int, Player*>::iterator it;

	for (it = listOfPlayers.begin(); it != listOfPlayers.end(); ++it)
	{
		Player* player = it->second;
		Bullet* bullet = player->bullet;

		Multiplayer::Bullet bulletState = listOfBulletStates[it->first];
		if (bulletState.state() == ACTIVE)
		{
			glm::vec3 bulletTargetPos = bullet->model->transform.position +
				bullet->moveDir * bulletPredictSpeed * Timer::GetInstance().deltaTime;

			bullet->GetTransform()->SetPosition(bulletTargetPos);
		}

		if (it->first == clientId)
		{
			continue;
		}

		Multiplayer::Player playerState = listOfPlayerStates[it->first];

		glm::vec3 targetPos = player->model->transform.position + player->moveDir * predictSpeed * Timer::GetInstance().deltaTime;
		player->GetTransform()->SetPosition(targetPos);

	}
}

Transform* PlayerManager::GetTransform()
{
	return nullptr;
}

void PlayerManager::Print()
{
	std::cout << "Client Player Manager Init" << std::endl;
}

void PlayerManager::UpdatePlayerState(const int& id, const Multiplayer::Player& state)
{
	listOfPlayerStates[id] = state;
}

void PlayerManager::UpdateBulletState(const int& id, const Multiplayer::Bullet& state)
{
	listOfBulletStates[id] = state;
}


void PlayerManager::Start()
{
}

void PlayerManager::Update(float deltaTime)
{
	PositionPredictor();
}

void PlayerManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	playFactory->AssignComponents(renderer, shader, physicsEngine);
}

void PlayerManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
