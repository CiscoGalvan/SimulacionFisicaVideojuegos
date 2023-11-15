#include "ParticleForceRegistry.h"
void ParticleForceRegistry::updateForces(double duration)
{

	for (auto it = begin(); it != end(); ++it)
	{
		it->first->updateForce(it->second, duration);
	}
	
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fG, Particle* p)
{
	insert(FRPair(fG, p));
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p)
{
	auto it = begin();
	while(it != end())
	{
		if (it->second == p)
		{
			it = erase(it);
		}
		else ++it;
	}
}


void ParticleForceRegistry::deleteForceRegistry(ForceGenerator* fG)
{
	auto it = begin();
	while (it != end())
	{
		if (it->first == fG)
		{
			it = erase(it);
		}
		else it++;
	}
}