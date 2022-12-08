#pragma once
#include <glm/glm.hpp>
#include "../MeshObj/cMeshObj.h"

class cParticle
{
public:
	cParticle();
	~cParticle();

	glm::vec3 startLocation;
	glm::vec3 endLocation;
	glm::vec3 curPos;
	int traveltime;
	int damage;
	cMeshObj* meshObj_;

private:

};

