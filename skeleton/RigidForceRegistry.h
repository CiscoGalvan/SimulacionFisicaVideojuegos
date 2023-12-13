#pragma once
#include "ForceGenerator.h"
#include <map>

using namespace std;

typedef pair <ForceGenerator*, RigidBody> solidPair;

class RigidForceRegistry :public multimap<ForceGenerator*, RigidBody>
{
private:

public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fG, RigidBody rb);
	void deleteSolidRegistry(RigidBody rb);
	void deleteForceRegistry(ForceGenerator* fG);
};

