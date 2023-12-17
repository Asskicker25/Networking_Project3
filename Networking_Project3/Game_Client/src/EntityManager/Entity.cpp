#include "Entity.h"
#include "EntityManager.h"

void Entity::InitializeEntity(Entity* entity)
{
	EntityManager::GetInstance().AddEntity(entity);
}

void Entity::Destroy()
{
	//Debugger::Print("Destroy Triggered");
	EntityManager::GetInstance().RemoveEntity(entityId);
}
