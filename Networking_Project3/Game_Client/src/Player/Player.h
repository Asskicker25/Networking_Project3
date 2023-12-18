#pragma once

#include "../GameObject/GameObject.h"
#include "../Bullet/Bullet.h"

class Player : public GameObject
{
public:
	
	int clientId = -1;
	Bullet* bullet = nullptr;


	Player();
	void CreateInstance(Model& model);
	Transform* GetTransform() override;

	glm::vec3 moveDir = glm::vec3(0);

private:

	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

