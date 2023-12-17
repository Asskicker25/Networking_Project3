#pragma once

#include "../GameObject/GameObject.h"

class GameManager : public Entity
{

public:
	GameManager();

	void AddPlayer(int id);
	std::unordered_map<int, GameObject*> listOfPlayers;

private:
	int currentPlayerCount = 0;

	static glm::vec3 position[4];
	static glm::vec4 colors[4];


	// Inherited via GameObject
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

