#pragma once

#include "../GameObject/GameObject.h"
#include <UDP_Server.h>

#include "../Bullet/Bullet.h"

class Player : public GameObject
{
public:

	Bullet* bullet = nullptr;

	Player();

	void CreateInstance(Model& model);
	Transform* GetTransform() override;

	void UpdateInput(const InputAction& action, const PlayerInput& input);

private:

	float speed = 1;
	float spawnInterval = 2;
	float bulletSpawnOffset = 0.2f;

	float timeStep = 0;

	bool bulletSpawned = false;

	glm::vec3 currentVelocity;

	void OnBulletDestroy();


	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

