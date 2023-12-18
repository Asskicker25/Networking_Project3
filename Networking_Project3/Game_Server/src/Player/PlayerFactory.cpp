#include "PlayerFactory.h"
#include "../EntityManager/EntityManager.h"

PlayerFactory::PlayerFactory()
{
    player = new Model("Assets/Models/tank.obj");
    player->transform.SetRotation(glm::vec3(0.0,180,0));
    player->transform.SetScale(glm::vec3(0.05f));
}

Player* PlayerFactory::CreatePlayer()
{
    std::string entityId = "Player" + std::to_string(playerCount);

    Player* newPlayer = new Player();
    newPlayer->CreateInstance(*player);

    newPlayer->tag = "Player";

    newPlayer->model->modelId = "Player" + std::to_string(playerCount);
    renderer->AddModel(newPlayer->model, shader);
    physicsEngine->AddPhysicsObject(newPlayer->phyObj);

    EntityManager::GetInstance().AddEntity(entityId, newPlayer);

    playerCount++;

    return newPlayer;
}

void PlayerFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    this->renderer = renderer;
    this->shader = shader;
    this->physicsEngine = physicsEngine;
}
