#pragma once
#include "ForceGenerator.h"
#include <map>

using namespace std;

typedef pair <ForceGenerator*, Particle*>FRPair;

class ParticleForceRegistry:public multimap<ForceGenerator*,Particle*>
{
private:

public:
	void updateForces(double duration);
	
	void addRegistry(ForceGenerator* fG, Particle* p);
	void deleteParticleRegistry(Particle* p);
	void deleteForceRegistry(ForceGenerator* fG);
};

