#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "Particle.h"
#include "RenderUtils.hpp"
#include <list>
#include "SolidGenerator.h"
#include "RigidForceRegistry.h"
#include "GeneradorTorbellino.h"
#include "Bola.h"
#include "Palo.h"
#include "PxContactModifyCallback.h"
#include "callbacks.hpp"
#include "FuerzaInstantanea.h"
#include <math.h>
#include "ParticleGenerator.h"
#include "Firework.h"
#include "GaussianGenerator.h"
#include "ParticleGenerator.h"
#include "ExplosionGenerator.h"
#include "AnchoredSpringFG.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
using namespace physx;
enum Direcciones
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


enum Tipos
{
	PALO,
	BLANCA
};
class RigidBodySystem
{
	
private:
	ParticleForceRegistry* pfR;

	std::list<RigidBody> solids;
	list<SolidGenerator*> generators;
	list<ParticleGenerator*> generatorsParticles;

	list<Firework* >fireworks;

	SolidGenerator* Fx;
	RigidForceRegistry* rFR;


	list<ForceGenerator*>fG;


	AnchoredSpringFG* aF;

	list<Particle*> particles;
	PxPhysics* _gPhysics;
	PxScene* _gScene;
	GeneradorTorbellino* torbellino;
	ExplosionGenerator* explosion;
	RenderItem* whiteStrip;
	list<Bola*>bolas;
	Bola* blanca;
	Palo* palo;
	bool active = false;
	int posicion = 1;
	PxRigidStatic* changing;
	RenderItem* changing2;

	bool end = false;

	float segundosTrasGolpe = 0;
	bool golpeado = false;
	float lastHoldValue = 0;
	float holdValue = 0;
	bool puedeDisparar = true;
	bool FxCreated = false;
	vector<PxTransform*>posicionesSaque;
	int tirosPosibles = 5;
	int puntuacion = 0;

	bool firstMove = true;;
	float puntuacionAntesGolpe = -1;
	float puntuacionTrasGolpe = 0;
	bool explotado = false;


	int bolasRojas = 15;


public:

	RigidBodySystem(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodySystem();
	void addDynamicObject(float Cestatico, float Cdinamico, float Elastico, PxVec3 inertiaT, Vector3 dimension,
		Vector4 color, Vector3 transform, Vector3 velocity, Vector3 angularvelocity, float density, int timetoleave);
	void update(double t);


	void addSolid(RigidBody rb) { solids.push_back(rb); }
	inline list<ForceGenerator*> getForces() { return fG; }
	inline PxPhysics* getPhysics() { return _gPhysics; }
	inline PxScene* getScene() { return _gScene; }
	void addGenerator(Particle* p, int nParticles, float frecuency);
	void addGenerator2(Particle* p, int nParticles, float frecuency);
	void addGeneratorCharge(int nParticles, float frecuency);
	void allowTorbellino();
	void denyTorbellino();
	void switch2();
	void moveBlanca(const Direcciones& v);
	void configuraCamara();

	void rotatePalo();
	void setHoldValue(float newValue);
	inline void addParticle(Particle* p) { particles.push_back(p); }
	void revientaPelota();

	PxTransform* getPaloT() { return palo->getPos(); }

	inline void refreshConsole() { for (int i = 0; i < 27; i++)cout << "\n"; }
	bool poderDisparar();
	inline bool firstMoved() { return firstMove; }
	void onScoring();

	void ExplotaTodo();

	
};

