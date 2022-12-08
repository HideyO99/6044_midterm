#include "cBattleGame.h"


float RandomFloat(float a, float b);

cBattleGame::cBattleGame()
{
	mapNametoMeshObj_ = nullptr;
	drawInfo_ = nullptr;
	pTerrain_ = nullptr;
}

cBattleGame::~cBattleGame()
{
}

void cBattleGame::gameUpdate()
{
	for (size_t i = 0; i < MAXROBOT; i++)
	{
		vRobot_[i]->pWeaponObj->position = glm::vec3(vRobot_[i]->pMeshObj->position.x, vRobot_[i]->pMeshObj->position.y+5, vRobot_[i]->pMeshObj->position.z);
	}
}

void cBattleGame::gameInit(std::map<std::string, cMeshObj*>& mapInstanceNametoMeshObj, cModelDrawInfo& drawInfo)
{
	//create weapon
	cWeapon* Bomb_ = new cWeapon();
	Bomb_->damage_ = BOMB_DAMAGE;
	Bomb_->reloadSec = BOMB_RELOAD;
	Bomb_->travelTime = BOMB_TRAVEL;
	Bomb_->radius = BOMB_RADIUS;

	cWeapon* Laser_ = new cWeapon();
	Laser_->damage_ = LASER_DAMAGE;
	Laser_->reloadSec = LASER_RELOAD;
	Laser_->travelTime = LASER_TRAVEL;
	Laser_->radius = LASER_RADIUS;

	cWeapon* Bullets = new cWeapon();
	Bullets->damage_ =	BULLETS_DAMAGE;
	Bullets->reloadSec = BULLETS_RELOAD;
	Bullets->travelTime = BULLETS_TRAVEL;
	Bullets->radius = BULLETS_RADIUS;

	//create robot
	for (size_t i = 0; i < MAXROBOT; i++)
	{
		cRobot* robot = new cRobot();
		cMeshObj* pCurrmeshObj = new cMeshObj();
		cMeshObj* pWeapon = new cMeshObj();
		cMeshObj* pPaticle = new cMeshObj();

		float x = RandomFloat(pTerrain_->pDrawInfo->minX, pTerrain_->pDrawInfo->maxX);
		float z = RandomFloat(pTerrain_->pDrawInfo->minZ, pTerrain_->pDrawInfo->maxZ);
		float y = pTerrain_->findHeightFromXZ(x, z);

		robot->pMeshObj = pCurrmeshObj;
		pCurrmeshObj->meshName = "robot";
		pCurrmeshObj->position = glm::vec3(x, y, z);
		pCurrmeshObj->instanceName = robot->name;
		pCurrmeshObj->bDoNotLight = false;
		pCurrmeshObj->color_RGBA = glm::vec4(0.f, 0.f, 1.f, 1.f);
		pCurrmeshObj->isWireframe = false;
		pCurrmeshObj->specular_colour_and_power = glm::vec4(1.f, 1.f, 1.f, 1.f);

		robot->pWeaponObj = pWeapon;
		pWeapon->meshName = "cube";
		pWeapon->position = glm::vec3(x, y+5, z);
		pWeapon->instanceName = robot->name+" weapon";
		pWeapon->bDoNotLight = false;
		switch (robot->weaponType_)
		{
		case cRobot::TYPE_BOMB :
			pWeapon->color_RGBA = glm::vec4(0.f, 0.f, 1.f, 1.f);
			robot->pWeapon = Bomb_;
			break;
		case cRobot::TYPE_BULLETS:
			pWeapon->color_RGBA = glm::vec4(0.f, 1.f, 0.f, 1.f);
			robot->pWeapon = Bullets;
			break;
		case cRobot::TYPE_LASER:
			pWeapon->color_RGBA = glm::vec4(1.f, 0.f, 0.f, 1.f);
			robot->pWeapon = Laser_;
			break;
		default:
			break;
		}
		//pWeapon->color_RGBA = glm::vec4(0.f, 0.f, 1.f, 1.f);
		pWeapon->isWireframe = false;
		pWeapon->specular_colour_and_power = glm::vec4(1.f, 1.f, 1.f, 1.f);

		pPaticle->meshName = "cube";
		pPaticle->position = pWeapon->position;
		pPaticle->instanceName = robot->name + " bullet";
		pPaticle->bDoNotLight = false;
		pPaticle->isWireframe = false;
		pPaticle->specular_colour_and_power = glm::vec4(1.f, 1.f, 1.f, 1.f);
		pPaticle->color_RGBA = pWeapon->color_RGBA;

		vRobot_.push_back(robot);
		mapInstanceNametoMeshObj.emplace(pCurrmeshObj->instanceName, pCurrmeshObj);
		mapInstanceNametoMeshObj.emplace(pWeapon->instanceName, pWeapon);
		mapInstanceNametoMeshObj.emplace(pPaticle->instanceName, pPaticle);
		pVecInstanceMeshObj->push_back(pCurrmeshObj);
	}
}

float RandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

