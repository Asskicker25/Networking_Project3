#include "Player.h"
#include "../Bullet/BulletManager.h"
#include <Graphics/Timer.h>

Player::Player()
{
	model = new Model();
	phyObj = new PhysicsObject();
}

void Player::CreateInstance(Model& model)
{
	this->model->CopyFromModel(model);
	this->phyObj->Initialize(this->model, AABB, DYNAMIC);
	phyObj->userData = this;
}

Transform* Player::GetTransform()
{
	return model->GetTransform();
}

void Player::UpdateInput(const InputAction& action, const PlayerInput& input)
{

	if (!isActive)
	{
		if (input == FIRE)
		{
			model->transform.SetPosition(spawnPos);
			isActive = true;
			model->isActive = true;
			phyObj->isEnabled = true;
		}

		return;
	}

#pragma region PRESSED

	glm::vec3 forward = model->transform.GetForward();
	glm::vec3 pos = model->transform.position;
	glm::vec3 moveDir = glm::normalize(currentVelocity);
	float length = glm::length(moveDir);

	if (action == PRESSED)
	{
		if (input == BACKWARD)
		{
			if (length <= 0.0f)
			{
				//currentVelocity.z = speed;
				currentVelocity = model->transform.GetForward() * speed;
			}
			else
			{
				//currentVelocity.z = speed;
				currentVelocity = model->transform.GetForward() * speed;
			}
		}

		if (input == FORWARD)
		{
			if (length >= 0.0f)
			{
				//currentVelocity.z = -speed;
				currentVelocity = model->transform.GetForward() * -speed;
			}
			else
			{
				//currentVelocity.z = -speed;
				currentVelocity = model->transform.GetForward() * -speed;
			}
		}

		if (input == TURN_RIGHT)
		{
			model->transform.SetRotation(glm::vec3(model->transform.rotation.x,
				model->transform.rotation.y - 90, model->transform.rotation.z));
		}

		if (input == TURN_LEFT)
		{
			model->transform.SetRotation(glm::vec3(model->transform.rotation.x,
				model->transform.rotation.y + 90, model->transform.rotation.z));
		}

		if (input == FIRE)
		{
			if (bulletSpawned) return;

			bullet = BulletManager::GetInstance().CreateBullet(pos, forward, bulletSpawnOffset);
			bullet->OnBulletDestroy = [this](int clientId)
				{
					OnBulletDestroy(clientId);
				};

			bulletSpawned = true;
			
		}
	}

#pragma endregion

#pragma region RELEASED

	else if (action == RELEASED)
	{
		if (input == BACKWARD)
		{
			if (length > 0.0f)
			{
				currentVelocity = glm::vec3( 0.0f);
			}
		}

		if (input == FORWARD)
		{
			if (length > 0.0f)
			{
				currentVelocity = glm::vec3(0.0f);
			}
		}
	}

#pragma endregion


}

void Player::OnBulletDestroy(int clientId)
{
	bullet = nullptr;
	bulletSpawned = false;

	OnBulletHit(clientId);
}

void Player::Start()
{
}

void Player::Update(float deltaTime)
{
	phyObj->velocity = currentVelocity;

	if (!bulletSpawned) return;

	timeStep += Timer::GetInstance().deltaTime;

	if (timeStep >= spawnInterval)
	{
		timeStep = 0;
		bulletSpawned = false;
	}
}

void Player::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{

}

void Player::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

