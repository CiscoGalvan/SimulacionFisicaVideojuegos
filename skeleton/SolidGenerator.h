#pragma once
#include "Particle.h"
#include <random>
#include <list>

class RigidBodySystem;
class SolidGenerator
{
private:
	int type = 1;
	int clase = 0;
	bool solid = false;	
	std::random_device rd1;
	std::random_device rd2;
	std::uniform_real_distribution<double> distribution{ 0.0, 1.0 };
	std::uniform_real_distribution<double> randomVel2{ 0.0, 2.0 };
	std::uniform_real_distribution<double> randomVel{ 0.0, 50.0 };
	std::uniform_real_distribution<double> appear{ 0.0, 4.0 };
protected:
	Vector3 pos;
	int numParticles;
	int actualParticles;
	float frecuency;
	Particle* emitter;

	float nextRespawn = 0;
	float lastRespawn = 0;
	RigidBodySystem* rS;

public:
	SolidGenerator(Particle* emitter, int numParticles, float frecuency, RigidBodySystem* pS,bool solid,int clase);
	virtual ~SolidGenerator();

	bool finished() { return actualParticles >= numParticles; }
	virtual void update(double t);
	inline void updateFrecuency(float newFrecuency) { frecuency = newFrecuency; }
	inline void moreParticles(float newParticles) { numParticles += newParticles; }
	float getFrecuency() { return frecuency; }
};

