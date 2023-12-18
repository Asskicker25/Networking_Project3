#pragma once

#include "Bullet.h"


class BulletFactory
{
public:
	BulletFactory();
	Bullet* CreateBullet();
	void AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

private:
	int bulletCount = 0;

	Renderer* renderer;
	Shader* shader;
	PhysicsEngine* physicsEngine;

	Model* bullet;

};

