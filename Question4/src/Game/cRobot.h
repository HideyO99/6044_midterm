#pragma once
#include <glm/glm.hpp>
#include "../MeshObj/cMeshObj.h"
#include "cWeapon.h"


class cRobot
{
public:
	cRobot();
	~cRobot();
	enum weaponType
	{
		TYPE_LASER = 0,
		TYPE_BOMB,
		TYPE_BULLETS
	};
	int id;
	int health;
	std::string name;
	bool readyToShoot;
	bool isAlive;
	//bool isSeeEnemy;
	glm::vec3 targetLocation;
	std::string targetName;
	weaponType weaponType_;
	cMeshObj* pMeshObj;
	cMeshObj* pWeaponObj;
	cWeapon* pWeapon;
	cRobot* Enermy;

	void teleport(glm::vec3 newPos);
	void robotUpdate();
	void shoot();


};

