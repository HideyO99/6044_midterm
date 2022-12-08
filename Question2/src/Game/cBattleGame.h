#pragma once
#include <map>
#include "../MeshObj/cMeshObj.h"
#include <vector>
#include "cRobot.h"
#include "Terrain.h"
#include "../VAOManager/cModelDrawInfo.h"

#define MAXROBOT 10

class cBattleGame
{
public:
	cBattleGame();
	~cBattleGame();

	void gameUpdate();
	void gameInit(std::map<std::string, cMeshObj*>& mapNametoMeshObj, cModelDrawInfo& drawInfo);

	Terrain* pTerrain_;
	cMeshObj* pMeshObj_;
	cModelDrawInfo* drawInfo_;
	std::vector<cRobot*> vRobot_;
	std::map<std::string, cMeshObj*>* mapNametoMeshObj_;
	std::vector<cMeshObj*>* pVecInstanceMeshObj;

};

