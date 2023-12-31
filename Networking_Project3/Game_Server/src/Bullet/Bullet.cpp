#include "Bullet.h"
#include "../Player/Player.h"

Bullet::Bullet()
{
	model = new Model();
	phyObj = new PhysicsObject();
}

void Bullet::CreateInstance(Model& model)
{

	this->model->CopyFromModel(model);
	phyObj->userData = this;
	phyObj->Initialize(this->model, SPHERE, DYNAMIC, TRIGGER, true);
	phyObj->AssignCollisionCallback([this](PhysicsObject* other)
		{
			Entity* entity = (Entity*)other->userData;

			if (entity->tag == "Player")
			{
				Player* player = (Player*)entity;
				player->phyObj->isEnabled = false;

				Destroy();

				OnBulletDestroy(player->clientID);

				return;
			}
			std::cout << "Tag : " << entity->tag << std::endl;
		});
}

Transform* Bullet::GetTransform()
{
	return model->GetTransform();
}

void Bullet::Start()
{
}

void Bullet::Update(float deltaTime)
{
}

void Bullet::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void Bullet::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);
}
