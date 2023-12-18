#pragma once

#include "../GameObject/GameObject.h"

class Bullet : public GameObject
{
public:

	float speed = 0.5;

	Bullet();
	void CreateInstance(Model& model);
	Transform* GetTransform() override;

	std::function<void()> OnBulletDestroy;
private:

	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};



