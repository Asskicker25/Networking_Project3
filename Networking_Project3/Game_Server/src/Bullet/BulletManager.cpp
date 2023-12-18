#include "BulletManager.h"

BulletManager::BulletManager()
{
	factory = new BulletFactory();
	InitializeEntity(this);
}

BulletManager& BulletManager::GetInstance()
{
	static BulletManager instance;
	return instance;
}

Bullet* BulletManager::CreateBullet(const glm::vec3 pos, const glm::vec3& dir, const float& offset)
{
	Bullet* bullet = factory->CreateBullet();

	bullet->GetTransform()->SetPosition(pos - dir * offset);

	glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), dir);
	glm::vec3 up = glm::cross(dir, right);

	bullet->GetTransform()->SetOrientationFromDirections(up, right);

	bullet->phyObj->velocity = -dir * bullet->speed;

	return bullet;
}

void BulletManager::Print()
{
	std::cout << "BulletManager" << std::endl;
}

void BulletManager::Start()
{
}

void BulletManager::Update(float deltaTime)
{
}

void BulletManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	factory->AssignComponents(renderer, shader, physicsEngine);
}

void BulletManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
