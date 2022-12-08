#pragma once
#include <string>
#include <glm/glm.hpp>

#include "cParticle.h"

#define BOMB_DAMAGE	25
#define BOMB_RELOAD	5
#define BOMB_TRAVEL 5
#define BOMB_RADIUS 5

#define BULLETS_DAMAGE 2
#define BULLETS_RELOAD 0
#define BULLETS_TRAVEL 0
#define BULLETS_RADIUS 1

#define LASER_DAMAGE 4
#define LASER_RELOAD 1
#define LASER_TRAVEL 0
#define LASER_RADIUS 1

#define ROCKET_DAMAGE 30
#define ROCKET_RELOAD 10
#define ROCKET_TRAVEL 5
#define ROCKET_RADIUS 7.5

class cWeapon
{
public:
	cWeapon();
	~cWeapon();

	enum aimType
	{
		LOS,
		BAL
	};
	std::string weaponName;
	int damage_;
	int reloadSec;
	int radius;
	int travelTime;
	cParticle ammo_;
	//void damage(cRobot& victim);

};

