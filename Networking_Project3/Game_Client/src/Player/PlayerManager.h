#pragma once

#include "PlayerFactory.h"
#include "../GameObject/GameObject.h"
#include <UDP_Client.h>

class PlayerManager : public GameObject
{

public:

	PlayerFactory* playFactory;

	PlayerManager();

	static PlayerManager& GetInstance();
	Player* CreatePlayer();

	void AddPlayer(int id);
	bool CheckIfPlayerExists(int id);

	GameObject* GetPlayer(int id);

	void Print();

private:

	std::unordered_map<int, GameObject*> listOfPlayers;

	// Inherited via GameObject
	Transform* GetTransform() override;
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

