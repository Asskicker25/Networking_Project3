#pragma once

#include "../EntityManager/Entity.h"
#include <unordered_map>

class CommandGroup;

class GameObject : public Entity
{
protected:
	std::unordered_map <std::string, CommandGroup*> listOfCollisionGroups;

public:

	Model* model;
	PhysicsObject* phyObj;


	void AddCollisionGroup(const std::string& tag, CommandGroup* group);


	virtual ~GameObject() {} ;
	// Inherited via Entity

	virtual Transform* GetTransform() = 0;

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) = 0;
	virtual void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) = 0;
};

