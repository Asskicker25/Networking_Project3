#include "Player.h"

Player::Player()
{
    model = new Model();
    phyObj = new PhysicsObject();
}

void Player::CreateInstance(Model& model)
{
    this->model->CopyFromModel(model);
}

Transform* Player::GetTransform()
{
    return model->GetTransform();
}

void Player::Start()
{
}

void Player::Update(float deltaTime)
{
}

void Player::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    
}

void Player::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

