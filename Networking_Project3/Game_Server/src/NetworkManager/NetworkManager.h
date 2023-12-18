#pragma once

#include "../GameObject/GameObject.h"
#include <UDP_Server.h>
#include "../GameManager/GameManager.h"


class NetworkManager : public GameObject
{

public:
	
	UDP_Server* server;
	GameManager* gameManager;
	Multiplayer::GameScene gameScene;

	NetworkManager();
	void Initialize();

	void BroadcastToClients();

private:

	float timeStep = 0;
	float broadcastInterval = 0.2f;


	std::unordered_map<int, Multiplayer::Player*> listOfPlayers;

	void AddPlayerToList(int id, Multiplayer::Player* player);
	bool CheckIfPlayerExists(int id);

	void OnCommandRecv(int id, Multiplayer::CommandAndData commandData);
	void OnClientConnected(int id);

	// Inherited via GameObject
	Transform* GetTransform() override;
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

