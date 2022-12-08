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
		if (!vRobot_[i]->isAlive)
		{
			continue;
		}


		bool result = false;
		std::string targetName = "";
		vRobot_[i]->pWeaponObj->position = glm::vec3(vRobot_[i]->pMeshObj->position.x, vRobot_[i]->pMeshObj->position.y+5, vRobot_[i]->pMeshObj->position.z);

			result = findNearestRobot(vRobot_[i]->pMeshObj->position, targetName, vRobot_[i]->targetLocation, vRobot_[i]->weaponType_ == cRobot::TYPE_BOMB);
			if (!result)
			{
				//vRobot_[i]->Enermy = nullptr;
				vRobot_[i]->teleport(randomPos());
				continue;
			}
			vRobot_[i]->targetName = targetName;
			vRobot_[i]->Enermy = findRobotFromName(targetName);
		
		vRobot_[i]->robotUpdate();
	}
}

void cBattleGame::gameInit(std::map<std::string, cMeshObj*>& mapInstanceNametoMeshObj, cModelDrawInfo& drawInfo)
{
	cWeapon* Bomb_ = new cWeapon();
	Bomb_->damage_ = BOMB_DAMAGE;
	Bomb_->reloadSec = BOMB_RELOAD;
	Bomb_->travelTime = BOMB_TRAVEL;
	Bomb_->radius = BOMB_RADIUS;

	cWeapon* Bullets = new cWeapon();
	Bullets->damage_ = BULLETS_DAMAGE;
	Bullets->reloadSec = BULLETS_RELOAD;
	Bullets->travelTime = BULLETS_TRAVEL;
	Bullets->radius = BULLETS_RADIUS;

	cWeapon* Laser_ = new cWeapon();
	Laser_->damage_ = LASER_DAMAGE;
	Laser_->reloadSec = LASER_RELOAD;
	Laser_->travelTime = LASER_TRAVEL;
	Laser_->radius = LASER_RADIUS;

	cWeapon* Rocket_ = new cWeapon();
	Rocket_->damage_ = ROCKET_DAMAGE;
	Rocket_->reloadSec = ROCKET_RELOAD;
	Rocket_->travelTime = ROCKET_TRAVEL;
	Rocket_->radius = ROCKET_RADIUS;
	//create robot
	for (size_t i = 0; i < MAXROBOT; i++)
	{
		cRobot* robot = new cRobot();
		cMeshObj* pCurrmeshObj = new cMeshObj();
		cMeshObj* pWeapon = new cMeshObj();
		cMeshObj* pPaticle = new cMeshObj();

		float x = RandomFloat(pTerrain_->pDrawInfo->minX, pTerrain_->pDrawInfo->maxX);
		float z = RandomFloat(pTerrain_->pDrawInfo->minZ, pTerrain_->pDrawInfo->maxZ);
		float y = pTerrain_->findHeightFromXZ(x,z);

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
		case cRobot::TYPE_ROCKET:
			pWeapon->color_RGBA = glm::vec4(1.f, 1.f, 0.f, 1.f);
			robot->pWeapon = Rocket_;
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
		pPaticle->isWireframe = true;
		pPaticle->specular_colour_and_power = glm::vec4(1.f, 1.f, 1.f, 1.f);
		pPaticle->color_RGBA = pWeapon->color_RGBA;

		vRobot_.push_back(robot);
		mapInstanceNametoMeshObj.emplace(pCurrmeshObj->instanceName, pCurrmeshObj);
		mapInstanceNametoMeshObj.emplace(pWeapon->instanceName, pWeapon);
		mapInstanceNametoMeshObj.emplace(pPaticle->instanceName, pPaticle);
		pVecInstanceMeshObj->push_back(pCurrmeshObj);
	}
}

bool cBattleGame::findNearestRobot(const glm::vec3 curLo, std::string& targetName,glm::vec3& targetLo, bool needLOS)
{
	float distance = 0;
	float distance_temp = glm::length(glm::vec3(pTerrain_->pDrawInfo->extentX, pTerrain_->pDrawInfo->extentY, pTerrain_->pDrawInfo->extentZ));
	
	bool findNearest = false;
	for (size_t i = 0; i < MAXROBOT; i++)
	{
		if (!vRobot_[i]->isAlive) //if dead search new robot
			continue;

		distance = glm::length((curLo - vRobot_[i]->pMeshObj->position));
		if (distance == 0)
		{
			continue;
		}
		if (!needLOS) //check line of sight
		{
			if (distance < distance_temp)
			{
				distance_temp = distance;
				targetLo = vRobot_[i]->pMeshObj->position;
				targetName = vRobot_[i]->name;
				findNearest = true;
			}
		}
		else
		{
			if (LineOfSight(curLo, vRobot_[i]->pMeshObj->position))
			{
				if (distance < distance_temp)
				{
					distance_temp = distance;
					targetLo = vRobot_[i]->pMeshObj->position;
					targetName = vRobot_[i]->name;
					findNearest = true;
				}
			}
		}
	}

	return findNearest;

}

bool cBattleGame::LineOfSight(glm::vec3 origin, glm::vec3 des)
{
	glm::vec3 TargetToRobotVector = glm::vec3(des.x - origin.x, des.y - origin.y, des.z - origin.z);
	glm::vec3 DirectiontoTarget = glm::normalize(TargetToRobotVector);
	glm::vec3 MovementPerStep = DirectiontoTarget;// *0.1f;
	glm::vec3 testPoint = origin;
	float distance_origin = glm::length(des - origin);

	while (glm::length(testPoint - origin) < distance_origin)
	{
		testPoint += MovementPerStep;
		if (testPoint.y < pTerrain_->findHeightFromXZ(testPoint.x, testPoint.z))
		{
			return false;
		}
	}
	return true;
}
glm::vec3 cBattleGame::randomPos()
{
	float x = RandomFloat(pTerrain_->pDrawInfo->minX, pTerrain_->pDrawInfo->maxX);
	float z = RandomFloat(pTerrain_->pDrawInfo->minZ, pTerrain_->pDrawInfo->maxZ);
	float y = pTerrain_->findHeightFromXZ(x, z);

	return glm::vec3(x, y, z);
}

cRobot* cBattleGame::findRobotFromName(std::string name)
{
	for (size_t i = 0; i < MAXROBOT; i++)
	{
		if (vRobot_[i]->name == name) 
		{
			return vRobot_[i];
		}
	}
}

float RandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

