#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator {
protected:
	float height, volume, liquidDensity, gravity;
	Particle* liquidParticle;

public:
	BuoyancyForceGenerator(Particle* liquidParticle, float height, float volume, float density, float gravity);

	virtual void updateForce(Particle* particle,double t);
};

