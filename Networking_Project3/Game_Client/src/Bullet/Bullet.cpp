#include "Bullet.h"

Bullet::Bullet()
{
	model = new Model();
	phyObj = new PhysicsObject();
}

void Bullet::CreateInstance(Model& model)
{

	this->model->CopyFromModel(model);

	phyObj->isEnabled = false;
	phyObj->Initialize(this->model, SPHERE, DYNAMIC,TRIGGER);
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
}
