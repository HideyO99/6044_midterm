#include "cRobot.h"
#include <chrono>
std::chrono::milliseconds msec(1000);

//float RandomFloat(float a, float b);
cRobot::cRobot()
{
	pMeshObj = nullptr;
	pWeaponObj = nullptr; 
	switch ((std::rand() % 10))
	{
	case 0:
	case 1:
	case 2:
		weaponType_ = TYPE_BOMB;
		break;
	case 3:
	case 4:
	case 5:
		weaponType_ = TYPE_BULLETS;
		break;
	case 6:
	case 7:
	case 8:
		weaponType_ = TYPE_LASER;
		break;
	default:
		weaponType_ = TYPE_ROCKET;
		break;
	}
	//weaponType_ = (weaponType)(std::rand()%10);
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
	Enermy->health -= pWeapon->damage_;
}

