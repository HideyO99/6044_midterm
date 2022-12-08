#pragma once
#include "../VAOManager/cModelDrawInfo.h"
#include <glm/glm.hpp>

class Terrain
{
public:
	Terrain(cModelDrawInfo& drawInfo );
	~Terrain();

	cModelDrawInfo* pDrawInfo;
	glm::vec3 location;
	float** geoXZ;
	float findHeightFromXZ(float x, float z);
	bool findObstuction(int x1, int z1, int x2, int z2);
	void createGeoData();
private:
	float minX;
	float minZ;
	int sizeX;
	int sizeZ;
};

