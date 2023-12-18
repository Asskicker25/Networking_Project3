#include "BulletFactory.h"
#include "../EntityManager/EntityManager.h"

BulletFactory::BulletFactory()
{
	bullet = new Model("Assets/Models/CompleteShell.fbx");
	bullet->transform.SetScale(glm::vec3(0.002f));
	bullet->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.99,0.87,0.43,1));
}

Bullet* BulletFactory::CreateBullet()
{
	Bullet* newBullet = new Bullet();

	newBullet->CreateInstance(*bullet);

	renderer->AddModel(newBullet->model, shader);
	physicsEngine->AddPhysicsObject(newBullet->phyObj);

	EntityManager::GetInstance().AddEntity("Bullet" + std::to_string(bulletCount), newBullet);

	bulletCount++;

    return newBullet;
}

void BulletFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}
