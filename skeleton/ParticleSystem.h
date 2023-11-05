#pragma once
#include "GaussianGenerator.h"
#include "Firework.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
using namespace std;
class ParticleSystem
{
private:
	list<Particle*> particles;
	list<Firework*> fireworks;
	list<ParticleGenerator* >generators;
	Vector3 gravity;
	list<ForceGenerator*>fG;
	ParticleForceRegistry* pfR;
	GravityForceGenerator* gF;


	bool affectedByGenerator = false;
	float timeAlive = 0;
	float delay = 10;
	bool shot = false;
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void cleanupPhysics();
	void addGenerator(string name, Particle* particle, int numParticles, float frecuency,int type);
	void addGaussianGenerator(string name, Particle* particle, int numParticles, float frecuency);
	void shootParticle(float vel, float radius,float liveTime,float masa, Vector3 gravity);
	void shootFirework(float vel, float radius, float liveTime, float masa, Vector3 gravity,bool gaussian);
	void addParticle(Particle* p) { particles.push_back(p); }
	inline void setGenerator() { affectedByGenerator = !affectedByGenerator; }

	inline void anadeFuerza(){ fG.push_back(new GravityForceGenerator(Vector3(5, 0, 4))); }
	inline ParticleForceRegistry* getRegistry() { return pfR; }
	inline list<ForceGenerator*> getForces() { return fG; }

};

