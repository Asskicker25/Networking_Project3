#include "Player.h"
#include "../Bullet/BulletManager.h"

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
			bullet = BulletManager::GetInstance().CreateBullet(pos, forward, bulletSpawnOffset);
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

