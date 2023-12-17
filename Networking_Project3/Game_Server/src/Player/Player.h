#pragma once

#include "../GameObject/GameObject.h"

class Player : public GameObject
{
public:
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

