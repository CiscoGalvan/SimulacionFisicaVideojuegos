#include "RigidForceRegistry.h"
void RigidForceRegistry::updateForces(double duration)
{

	for (auto it = begin(); it != end(); ++it)
	{
		it->first->updateForce(it->second._rb, duration);
	}

}

void RigidForceRegistry::addRegistry(ForceGenerator* fG, RigidBody rb)
{
	insert(solidPair(fG, rb));
}

void RigidForceRegistry::deleteSolidRegistry(RigidBody rb)
{
	auto it = begin();
	while (it != end())
	{
		if (it->second._rb == rb._rb)
		{
			it = erase(it);
		}
		else ++it;
	}
}

void RigidForceRegistry::deleteForceRegistry(ForceGenerator* fG)
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