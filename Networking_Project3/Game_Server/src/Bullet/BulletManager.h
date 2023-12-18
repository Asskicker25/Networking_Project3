#pragma once

#include "BulletFactory.h"
#include "../EntityManager/Entity.h"

class BulletManager : public Entity
{

public:
	BulletFactory* factory;

	BulletManager();
	static BulletManager& GetInstance();

	Bullet* CreateBullet(const glm::vec3 pos,  const glm::vec3& dir, const float& offset);

	void Print();

private:
	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

