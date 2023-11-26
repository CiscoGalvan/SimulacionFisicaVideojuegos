#pragma once
#include "GaussianGenerator.h"
#include "Firework.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "ParticleDragGenerator.h"
#include "GeneradorTorbellino.h"
#include "ExplosionGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "GomaElastica.h"
#include "BuoyancyForceGenerator.h"
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
	

	Particle* windZone;
	Particle* waterZone = nullptr;

	bool affectedByGenerator = false, windAffected = false;;
	float timeAlive = 0;
	float delay = 10;
	float explosionTime = 0;
	bool quitExplosion = false;
	ParticleDragGenerator* wind;
	GeneradorTorbellino* torbellino;
	GravityForceGenerator* gravedad;
	GravityForceGenerator* temporaryGravity;
	AnchoredSpringFG* f3 = nullptr;
	ExplosionGenerator* explosion_tai;

	bool showSquare = true;
	bool registered = true;
	bool showSquare2 = true;
	bool registered2= true;
	bool shot = false;


	bool temporaryGravedad = false;
	float gravityTime = 1000;
	std::random_device rd1;
	std::uniform_real_distribution<double> randomVel{ 0.0, 50.0 };
	
	bool generateParticles = false;
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
	void generateSpringDemo();
	void generateWater();
	inline void setGenerator() { affectedByGenerator = !affectedByGenerator; }



	inline void biggerK() { if(f3 != nullptr) f3->biggerK(); }
	inline void smallerK() { if (f3 != nullptr) f3->smallerK(); }
	inline ParticleForceRegistry* getRegistry() { return pfR; }
	inline list<ForceGenerator*> getForces() { return fG; }
	inline void showSquareFunction2() { if(waterZone != nullptr )showSquare2 = !showSquare2; }
	inline void showSquareFunction() { showSquare = !showSquare; }
	void generaParticula(physx::PxTransform pos, Vector3 vel, Vector3 acel,float masa, Vector3 gravity);
	void allowWind();
	void denyWind();

	void generateSlinky();
	void temporalGravity(Vector3 v);
	void allowTorbellino();
	void denyTorbellino();

	inline void setGeneration() { generateParticles = !generateParticles; }

	void explode();
};

