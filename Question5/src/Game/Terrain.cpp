#include "Terrain.h"

Terrain::Terrain(cModelDrawInfo& drawInfo)
{
	pDrawInfo = &drawInfo;
	minX = pDrawInfo->minX;
	minZ = pDrawInfo->minZ;
	sizeX = (int)pDrawInfo->extentX+1;
	sizeZ = (int)pDrawInfo->extentZ+1;
	geoXZ = new float*[sizeZ];
	for (int i = 0; i < sizeX; i++)
	{
		geoXZ[i] = new float[sizeX];
	}
	createGeoData();
}

Terrain::~Terrain()
{
}

float Terrain::findHeightFromXZ(float x, float z)
{
	float rx = round(x);
	float rz = round(z);
	float result = 0;

	for (unsigned int i = 0; i < pDrawInfo->numberOfVertices; i++)
	{
		if (rx == round(pDrawInfo->pVertices[i].x))
		{
			if (rz == round(pDrawInfo->pVertices[i].z))
			{
				result = pDrawInfo->pVertices[i].y;
			}
		}
	}
	return result;
}

bool Terrain::findObstuction(int x1, int z1, int x2, int z2)
{
	int delX = x2 - x1;
	int delZ = z2 - z1;
	float slopeY = (geoXZ[x2][z2] - geoXZ[x1][z1]) / sqrt((delX*delX)+(delZ*delZ));
	return false;
}

void Terrain::createGeoData()
{
	for (unsigned int i = 0; i < pDrawInfo->numberOfVertices; i++)
	{
		geoXZ[(int)(round(pDrawInfo->pVertices[i].x - minX))][(int)(round(pDrawInfo->pVertices[i].z - minZ))] = pDrawInfo->pVertices[i].y;
	}
}
