#pragma once
#include "ParticleGenerator.h"
using namespace std;
class ParticleSystem
{
private:
	list<Particle*> v;
	Vector3 gravity;
	float nextRespawn = 0;
	float lastRespawn = 0;
	float frecuency;
public:
	ParticleSystem(float frecuency);
	~ParticleSystem();
	void update(double t);
	void cleanupPhysics();

	void shootParticle(float vel, float radius,float liveTime, Vector3 gravity);
};

