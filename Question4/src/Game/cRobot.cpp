#include "cRobot.h"
#include <chrono>
std::chrono::milliseconds msec(1000);

//float RandomFloat(float a, float b);
cRobot::cRobot()
{
	pMeshObj = nullptr;
	pWeaponObj = nullptr; 
	weaponType_ = (weaponType)(std::rand()%3);
	health = 100;
	id = std::rand() % 999;
	name = "robot" + std::to_string(id);
	readyToShoot = false;
	targetLocation = glm::vec3(0);
	targetName = "";
	Enermy = nullptr;
	isAlive = true;
	//isSeeEnemy = false;
}

cRobot::~cRobot()
{
}

void cRobot::teleport(glm::vec3 newPos)
{
	pMeshObj->position = newPos;
}

void cRobot::robotUpdate()
{
	if (msec.count() == (pWeapon->reloadSec) * 1000)
	{
		readyToShoot = true;
	}
	if (readyToShoot)
	{
		shoot();
	}
	if (health <= 0)
	{
		pMeshObj->color_RGBA = glm::vec4(0.5f, 0.5f, 0.5f, 1.f);
		isAlive = false;
	}
}

void cRobot::shoot()
{
	this->Enermy->health -= this->pWeapon->damage_;
}

