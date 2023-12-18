#pragma once

#include "../GameObject/GameObject.h"
#include "../Bullet/Bullet.h"

class Player : public GameObject
{
public:
	Bullet* bullet = nullptr;

	Player();
	void CreateInstance(Model& model);
	Transform* GetTransform() override;

private:

	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

