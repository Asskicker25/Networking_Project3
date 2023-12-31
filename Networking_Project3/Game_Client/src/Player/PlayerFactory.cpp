#include "PlayerFactory.h"
#include "../EntityManager/EntityManager.h"

PlayerFactory::PlayerFactory()
{
    player = new Model("Assets/Models/tank.obj");
    player->transform.SetRotation(glm::vec3(0.0, 180, 0));
    player->transform.SetScale(glm::vec3(0.05f));
}

Player* PlayerFactory::CreatePlayer()
{
    Player* newPlayer = new Player();
    newPlayer->CreateInstance(*player);

    renderer->AddModel(newPlayer->model, shader);
    physicsEngine->AddPhysicsObject(newPlayer->phyObj);

    EntityManager::GetInstance().AddEntity("Player" + std::to_string(playerCount), newPlayer);

    return newPlayer;
}

void PlayerFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    this->renderer = renderer;
    this->shader = shader;
    this->physicsEngine = physicsEngine;
}
