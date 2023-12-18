#include "Player.h"

Player::Player()
{
    model = new Model();
    phyObj = new PhysicsObject();
}

void Player::CreateInstance(Model& model)
{
    this->model->CopyFromModel(model);
    this->phyObj->Initialize(this->model, SPHERE, DYNAMIC);
}

Transform* Player::GetTransform()
{
    return model->GetTransform();
}

void Player::UpdateInput(const InputAction& action, const PlayerInput& input)
{

#pragma region PRESSED

	if(action == PRESSED)
	{
		if (input == BACKWARD)
		{
			if (currentVelocity.z <= 0.0f)
			{
				currentVelocity.z = speed;
			}
			else
			{
				currentVelocity.z = speed;
			}
		}

		if (input == FORWARD)
		{
			if (currentVelocity.z >= 0.0f)
			{
				currentVelocity.z = -speed;
			}
			else
			{
				currentVelocity.z = -speed;
			}
		}
	}

#pragma endregion

#pragma region RELEASED

	else if (action == RELEASED)
	{
		if (input == BACKWARD)
		{
			if (currentVelocity.z > 0.0f)
			{
				currentVelocity.z = 0.0f;
			}
		}

		if (input == FORWARD)
		{
			if (currentVelocity.z < 0.0f)
			{
				currentVelocity.z = 0.0f;
			}
		}
	}

#pragma endregion


}

void Player::Start()
{
}

void Player::Update(float deltaTime)
{
	phyObj->velocity = currentVelocity;
}

void Player::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    
}

void Player::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

