#pragma once

#include "../InputManager/InputManager.h"
#include "../GameObject/GameObject.h"
#include <UDP_Client.h>

class PlayerController : public Entity, public iInputListener
{

public:

	UDP_Client* client;

	PlayerController();

	void SetPlayer(GameObject* player);
	GameObject* GetPlayer();

private:

	GameObject* player = nullptr;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via iInputListener
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;
};

