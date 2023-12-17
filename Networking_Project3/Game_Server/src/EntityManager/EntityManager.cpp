#include "EntityManager.h"
#include <Graphics/Renderer.h>

EntityManager& EntityManager::GetInstance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::AddEntity(const std::string& entityId, Entity* entity)
{
	listOfEntities[entityId] = entity;
	entity->entityId = entityId;
	//entity->entityManager = this;

	entity->AddToRendererAndPhysics(renderer, shader, physicsEngine);
}

void EntityManager::AddEntity(Entity* entity)
{
	std::string entityId = std::to_string((int)listOfEntities.size());
	entity->entityId = entityId;

	listOfEntities[entityId] = entity;

	entity->AddToRendererAndPhysics(renderer, shader, physicsEngine);
}

void EntityManager::RemoveEntity(const std::string& entityId)
{

	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		if (it->first == entityId)
		{
			Destroy(listOfEntities[entityId]);

			entityToRemove.push_back(entityId);

			//listOfEntities.erase(it->first);
			return;
		}
	}

	//listOfEntities.erase(entityId);
}

void EntityManager::RemoveEntity(Entity* entity)
{
	/*std::unordered_map<std::string, Entity*>::iterator it;

	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		if (it->second == entity)
		{
			Destroy(it->first);
			listOfEntities.erase(it->first);
			return;
		}
	}*/
}

void EntityManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->physicsEngine = physicsEngine;
	this->shader = shader;

	/*for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->AddToRendererAndPhysics(renderer, shader, physicsEngine);
	}*/
}

bool EntityManager::ShouldRemove(const std::string& entityId)
{
	for (const std::string& id : entityToRemove)
	{
		if (id == entityId)
		{
			return true;
		}
	}
	return false;
}

void EntityManager::Start()
{
	for (it = listOfEntities.begin(); it != listOfEntities.end(); ++it)
	{
		it->second->Start();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (const std::string& id : entityToRemove)
	{
		listOfEntities[id] = nullptr;

		delete listOfEntities[id];


		listOfEntities.erase(id);
	}

	entityToRemove.clear();

	try
	{
		for (std::pair<const std::string&, Entity*> item : listOfEntities)
		{
			item.second->Update(deltaTime);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}

void EntityManager::Destroy(Entity* entity)
{
	entity->RemoveFromRendererAndPhysics(renderer, physicsEngine);
}

