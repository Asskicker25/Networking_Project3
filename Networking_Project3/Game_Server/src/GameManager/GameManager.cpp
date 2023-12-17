#include "GameManager.h"
#include "../Player/PlayerManager.h"

glm::vec3 GameManager::position[4] = {
	glm::vec3(-1,0,0),
	glm::vec3(-1,0,1),
	glm::vec3(1,0,0),
	glm::vec3(1,0,1),
};

glm::vec4 GameManager::colors[4] = {
	glm::vec4(1,0,0,1),
	glm::vec4(0,1,0,1),
	glm::vec4(0,0,1,1),
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

	listOfPlayers[id] = player;

	currentPlayerCount++;
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
