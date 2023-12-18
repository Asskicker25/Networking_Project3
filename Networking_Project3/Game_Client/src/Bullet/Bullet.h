#pragma once

#include "../GameObject/GameObject.h"

class Bullet : public GameObject
{
public:

	Bullet();

	void CreateInstance(Model& model);
	Transform* GetTransform() override;

	float speed = 0.5;

	glm::vec3 moveDir = glm::vec3(0);

private:


	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

