#pragma once

#include "Player.h"

class PlayerFactory
{
public:
	PlayerFactory();
	Player* CreatePlayer();
	void AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

private:

	int playerCount = 0;

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	Model* player;
};

