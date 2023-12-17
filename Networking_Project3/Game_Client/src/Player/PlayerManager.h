#pragma once

#include "PlayerFactory.h"
#include "../GameObject/GameObject.h"

class PlayerManager : public GameObject
{

public:

	PlayerFactory* playFactory;

	PlayerManager();

	static PlayerManager& GetInstance();

	Player* CreatePlayer();

private:
	// Inherited via GameObject
	Transform* GetTransform() override;
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

