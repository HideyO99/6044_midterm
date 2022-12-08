#pragma once
#include <map>
#include "../MeshObj/cMeshObj.h"
#include <vector>
#include "cRobot.h"
#include "Terrain.h"
#include "../VAOManager/cModelDrawInfo.h"
#include "cWeapon.h"

#define MAXROBOT 20

class cBattleGame
{
public:
	cBattleGame();
	~cBattleGame();

	void gameUpdate();
	void gameInit(std::map<std::string, cMeshObj*>& mapNametoMeshObj, cModelDrawInfo& drawInfo);
	bool findNearestRobot(const glm::vec3 curLo, std::string& targetName, glm::vec3& targetLo, bool isBallistic);
	bool LineOfSight(glm::vec3 origin, glm::vec3 des);
	cRobot* findRobotFromName(std::string name);
	glm::vec3 randomPos();

	Terrain* pTerrain_;
	cMeshObj* pMeshObj_;
	cModelDrawInfo* drawInfo_;
	std::vector<cRobot*> vRobot_;
	std::map<std::string, cMeshObj*>* mapNametoMeshObj_;
	std::vector<cMeshObj*>* pVecInstanceMeshObj;

};

