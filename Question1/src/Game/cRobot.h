#pragma once
#include <glm/glm.hpp>

class cRobot
{
public:
	cRobot();
	~cRobot();
	enum weaponType
	{
		TYPE_LASER = 3,
		TYPE_BOMB = 6,
		TYPE_BULLETS = 9,
		TYPE_ROCKET = 10
	};
	int id;
	int health;
	glm::vec3 position;
	weaponType weaponType_;

};

