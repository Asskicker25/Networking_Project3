#pragma once

#include "../GameObject/GameObject.h"

class PlayerController : public Entity
{
public:

	GameObject* gameObject = nullptr;

private:
	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

