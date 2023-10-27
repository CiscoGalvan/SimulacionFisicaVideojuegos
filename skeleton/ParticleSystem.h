#pragma once
#include "GaussianGenerator.h"
#include "Firework.h"
using namespace std;
class ParticleSystem
{
private:
	list<Particle*> particles;
	list<Firework*> fireworks;
	list<ParticleGenerator* >generators;
	list<GaussianGenerator* >GaussianGenerators;
	Vector3 gravity;
	float timeAlive = 0;
	float delay = 10;
	bool shot = false;
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void cleanupPhysics();
	void addGenerator(string name, Particle* particle, int numParticles, float frecuency);
	void addGaussianGenerator(string name, Particle* particle, int numParticles, float frecuency);
	void shootParticle(float vel, float radius,float liveTime, Vector3 gravity);
	void shootFirework(float vel, float radius, float liveTime, Vector3 gravity,bool gaussian);
	void addParticle(Particle* p) { particles.push_back(p); }

};

