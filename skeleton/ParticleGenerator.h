#pragma once
#include "Particle.h"
#include <random>
#include <list>
class ParticleSystem;
class ParticleGenerator
{
private:
	
	std::random_device rd1;
	std::random_device rd2; 
	std::uniform_real_distribution<double> distribution{ 0.0, 1.0 };
	std::uniform_real_distribution<double> randomVel{ 0.0, 50.0 };
	std::uniform_real_distribution<double> randomVel2{ 0.0, 5.0 };

	int type;
protected:
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


	ParticleGenerator(std::string name,Particle* emitter,int numParticles,float frecuency,int type, ParticleSystem* pS);
	virtual ~ParticleGenerator();

	bool finished() { return actualParticles >= numParticles; }
    virtual void update(double t);
};

