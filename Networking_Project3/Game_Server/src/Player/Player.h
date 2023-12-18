#pragma once

#include "../GameObject/GameObject.h"
#include <UDP_Server.h>

#include "../Bullet/Bullet.h"

class Player : public GameObject
{
public:

	int clientID = -1;
	bool isActive = true;

	glm::vec3 spawnPos = glm::vec3(0);

	Bullet* bullet = nullptr;

	Player();

	void CreateInstance(Model& model);
	Transform* GetTransform() override;

	void UpdateInput(const InputAction& action, const PlayerInput& input);

	std::function<void(int)> OnBulletHit;


private:

	float speed = 1;
	float spawnInterval = 2;
	float bulletSpawnOffset = 0.2f;

	float timeStep = 0;

	bool bulletSpawned = false;

	glm::vec3 currentVelocity;

	void OnBulletDestroy(int clientID);


	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

