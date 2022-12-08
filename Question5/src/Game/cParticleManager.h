#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "cParticle.h"

class cParticleManager
{
public:
	cParticleManager();
	~cParticleManager();

	void particleUpdate();

	std::vector<cParticle*> vParticle_;

private:

};

