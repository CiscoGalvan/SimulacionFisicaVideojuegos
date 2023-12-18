#pragma once
#include "ForceGenerator.h"
#include <map>
#include "Bola.h"

using namespace std;

typedef pair <ForceGenerator*, RigidBody> solidPair;
typedef pair <ForceGenerator*, Bola> bolaPair;
class BolaForceRegistry : public multimap<ForceGenerator*, Bola>
{
private:

public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fG, Bola rb);
	void deleteForceRegistry(ForceGenerator* fG);
};
class RigidForceRegistry :public multimap<ForceGenerator*, RigidBody>
{
private:

public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fG, RigidBody rb);
	void deleteSolidRegistry(RigidBody rb);
	void deleteForceRegistry(ForceGenerator* fG);
};

