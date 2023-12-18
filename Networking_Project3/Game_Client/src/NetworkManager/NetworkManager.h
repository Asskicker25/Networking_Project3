#pragma once

#include "../GameObject/GameObject.h"
#include <UDP_Client.h>
#include "../Player/Player.h"

class NetworkManager : public GameObject
{

public:
	NetworkManager();

	UDP_Client* client;

	void Initialize(int clientId);


private:

	int clientId;

	void OnCommandRecv(int id, Multiplayer::CommandAndData commandData);
	void UpdateGameObjectValue(Player* gameObject, const  Multiplayer::Player& player, const Multiplayer::Bullet& bullet);

	// Inherited via GameObject
	Transform* GetTransform() override;
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

