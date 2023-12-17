#include "PlayerManager.h"

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

Transform* PlayerManager::GetTransform()
{
    return nullptr;
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
