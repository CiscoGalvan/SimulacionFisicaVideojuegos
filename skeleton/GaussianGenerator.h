#pragma once
#include "ParticleGenerator.h"
class GaussianGenerator : public ParticleGenerator
{
private:

	std::default_random_engine generator;
	std::normal_distribution<double>d{ 10,15 };
public:

	GaussianGenerator(std::string name, Particle* emitter, int numParticles, float frecuency, ParticleSystem* pS);
	virtual ~GaussianGenerator();
	virtual void update(double t);
};

