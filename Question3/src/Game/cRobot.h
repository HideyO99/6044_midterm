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
	//glm::vec3 position;
	weaponType weaponType_;
	cMeshObj* pMeshObj;
	cMeshObj* pWeaponObj;
	cWeapon* pWeapon;

	void teleplot(float x, float y, float z);
	void robotUpdate();

};

