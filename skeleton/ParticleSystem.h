#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
using namespace std;
class ParticleSystem
{
private:
	list<Particle*> particles;
	list<Firework*> fireworks;
	list<ParticleGenerator* >generators;
	Vector3 gravity;
	float timeAlive = 0;
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void cleanupPhysics();
	void addGenerator(string name, Particle* particle, int numParticles, float frecuency);
	void shootParticle(float vel, float radius,float liveTime, Vector3 gravity);


	void addParticle(Particle* p) { particles.push_back(p); }

};

