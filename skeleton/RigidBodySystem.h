#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "Particle.h"
#include "RenderUtils.hpp"
#include <list>
#include "SolidGenerator.h"
#include "RigidForceRegistry.h"
#include "GeneradorTorbellino.h"
using namespace physx;
class RigidBodySystem
{
	
private:
	std::list<RigidBody> solids;
	list<SolidGenerator*> generators;
	RigidForceRegistry* rFR;
	list<ForceGenerator*>fG;
	PxPhysics* _gPhysics;
	PxScene* _gScene;
	GeneradorTorbellino* torbellino;
	PxRigidStatic* floor2;
	bool active = false;
public:

	RigidBodySystem(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodySystem();
	void addDynamicObject(float Cestatico, float Cdinamico, float Elastico, PxVec3 inertiaT, Vector3 dimension,
		Vector4 color, Vector3 transform, Vector3 velocity, Vector3 angularvelocity, float density, int timetoleave);
	void addStaticObject();
	void update(double t);


	void addSolid(RigidBody rb) { solids.push_back(rb); }
	inline list<ForceGenerator*> getForces() { return fG; }
	inline PxPhysics* getPhysics() { return _gPhysics; }
	inline PxScene* getScene() { return _gScene; }
	void addGenerator(Particle* p, int nParticles, float frecuency);
	void allowTorbellino();
	void denyTorbellino();
	void switch2();
};

