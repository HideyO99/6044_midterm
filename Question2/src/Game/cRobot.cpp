#include "cRobot.h"

//float RandomFloat(float a, float b);
cRobot::cRobot()
{
	pMeshObj = nullptr;
	pWeaponObj = nullptr; 
	weaponType_ = (weaponType)(std::rand()%3);
	health = 100;
	id = std::rand() % 999;
	name = "robot" + std::to_string(id);
	
}

cRobot::~cRobot()
{
}

void cRobot::teleplot(float x, float y, float z)
{
	pMeshObj->position = glm::vec3(x, y, z);
}

//float RandomFloat(float a, float b) {
//    float random = ((float)rand()) / (float)RAND_MAX;
//    float diff = b - a;
//    float r = random * diff;
//    return a + r;
//}
