#include "PlayerFactory.h"
#include "../EntityManager/EntityManager.h"

PlayerFactory::PlayerFactory()
{
    player = new Model("res/Models/DefaultSphere.fbx");
    player->transform.SetScale(glm::vec3(0.1f));
}

Player* PlayerFactory::CreatePlayer()
{
    Player* newPlayer = new Player();
    newPlayer->CreateInstance(*player);

    newPlayer->model->modelId = "Player" + std::to_string(playerCount);
    renderer->AddModel(newPlayer->model, shader);
    physicsEngine->AddPhysicsObject(newPlayer->phyObj);

    EntityManager::GetInstance().AddEntity("Player" + std::to_string(playerCount), newPlayer);

    playerCount++;

    return newPlayer;
}

void PlayerFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    this->renderer = renderer;
    this->shader = shader;
    this->physicsEngine = physicsEngine;
}
