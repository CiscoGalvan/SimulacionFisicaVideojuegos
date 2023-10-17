#pragma once
#include "ParticleGenerator.h"
class GaussianGenerator : public ParticleGenerator
{
private:
	
	std::uniform_int_distribution<int> side{ 0,1 };

	std::default_random_engine generator;
	std::normal_distribution<double>d{ 10,15 };
public:

	GaussianGenerator(std::string name, Particle* emitter, int numParticles, float frecuency, ParticleSystem* pS);
	virtual ~GaussianGenerator();
	virtual void update(double t);
};

