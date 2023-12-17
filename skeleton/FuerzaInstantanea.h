#pragma once
#include "ForceGenerator.h"
#include <PxRigidBody.h>
#include "Bola.h"

class FuerzaInstantanea : public ForceGenerator
{
	PxVec3 force;
	Bola* bola;
public:
	FuerzaInstantanea(Bola* p, PxVec3 force);
	~FuerzaInstantanea();
	void updateForce(PxRigidBody* rb, double dt);
	void updateForce(Particle* p, double dt) {};
};

