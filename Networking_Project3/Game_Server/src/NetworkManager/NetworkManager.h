#pragma once

#include "../GameObject/GameObject.h"
#include <UDP_Server.h>

class NetworkManager : public GameObject
{

public:
	NetworkManager();

	UDP_Server* server;

	void Initialize();

private:

	void OnCommandRecv(int id, Multiplayer::CommandAndData commandData);

	// Inherited via GameObject
	Transform* GetTransform() override;
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

