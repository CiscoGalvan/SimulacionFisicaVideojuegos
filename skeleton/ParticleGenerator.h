#pragma once
#include "Particle.h"
#include <list>

class ParticleSystem;
class ParticleGenerator
{
private:
	std::string name;
	Vector3 pos;
	int numParticles;
	int actualParticles;
	float frecuency;
	Particle* emitter;

	float nextRespawn = 0;
	float lastRespawn = 0;
	ParticleSystem* pS;

	
public:
	ParticleGenerator(std::string name,Particle* emitter,int numParticles,float frecuency, ParticleSystem* pS);
	~ParticleGenerator();
	void update(double t);
};

