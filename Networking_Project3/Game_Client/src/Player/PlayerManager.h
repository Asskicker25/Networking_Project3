#pragma once

#include "PlayerFactory.h"
#include "../GameObject/GameObject.h"
#include <UDP_Client.h>
#include "PlayerController.h"

class PlayerManager : public GameObject
{

public:

	int clientId = -1;

	PlayerFactory* playFactory;
	PlayerController* playerController = nullptr;

	PlayerManager();
	static PlayerManager& GetInstance();

	Player* CreatePlayer();
	void AddPlayer(int id);
	bool CheckIfPlayerExists(int id);

	Player* GetPlayer(int id);

	void Print();

private:

	std::unordered_map<int, Player*> listOfPlayers;

	// Inherited via GameObject
	Transform* GetTransform() override;
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

