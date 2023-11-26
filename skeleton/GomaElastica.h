#pragma once
#include "SpringForceGenerator.h"
class GomaElastica : public SpringForceGenerator
{
public:
	GomaElastica(float k, double Length, Particle* Other);
	virtual void updateForce(Particle* particle, double t);
	~GomaElastica() {}
};

