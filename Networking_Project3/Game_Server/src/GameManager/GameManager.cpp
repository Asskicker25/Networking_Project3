#include "GameManager.h"

glm::vec3 GameManager::position[4] = {
	glm::vec3(-1,0,0),
	glm::vec3(-1,0,1),
	glm::vec3(1,0,0),
	glm::vec3(1,0,1),
};

glm::vec4 GameManager::colors[4] = {
	glm::vec4(0.8,0,0,1),
	glm::vec4(0,0.8,0,1),
	glm::vec4(0,0,0.8,1),
	glm::vec4(0.5,0.5,0.5,1),
};

GameManager::GameManager()
{
	InitializeEntity(this);
}

void GameManager::AddPlayer(int id)
{
	Player* player = PlayerManager::GetInstance().CreatePlayer();
	player->GetTransform()->SetPosition(position[currentPlayerCount]);
	player->model->meshes[0]->material->AsMaterial()->SetBaseColor(colors[currentPlayerCount]);
	player->clientID = id;
	player->spawnPos = position[currentPlayerCount];
	player->OnBulletHit = [this](int id)
		{
			OnPlayerDestroy(id);
		};

	listOfPlayers[id] = player;

	currentPlayerCount++;
}

void GameManager::OnPlayerDestroy(int clientId)
{
	listOfPlayers[clientId]->model->isActive = false;
	listOfPlayers[clientId]->isActive = false;
}

void GameManager::Start()
{
}

void GameManager::Update(float deltaTime)
{
}

void GameManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void GameManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
