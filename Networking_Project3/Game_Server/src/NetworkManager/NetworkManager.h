#pragma once

#include "../GameObject/GameObject.h"
#include <UDP_Server.h>
#include "../GameManager/GameManager.h"

enum PlayerState
{
	ACTIVE = 0,
	NOT_ACTIVE = 1
};

struct PlayerData
{
	PlayerState state;
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 vel;
};


class NetworkManager : public GameObject
{

public:
	
	UDP_Server* server;
	GameManager* gameManager;

	NetworkManager();
	void Initialize();

private:

	std::unordered_map<int, PlayerData> listOfPlayers;

	void AddPlayerToList(int id, const PlayerData& playerData);
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

