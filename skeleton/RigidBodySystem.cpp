#include "RigidBodySystem.h"
RigidBodySystem::RigidBodySystem(PxPhysics* gPhysics, PxScene* gScene)
{
	_gPhysics = gPhysics;
	_gScene = gScene;

	
	
	rFR = new RigidForceRegistry();

	PxVec3 cam = GetCamera()->getTransform().p;
	floor2 = gPhysics->createRigidStatic(PxTransform({ cam.x,cam.y - 20,cam.z}));
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1, 500));
	floor2->attachShape(*shape);
	gScene->addActor(*floor2);
	RenderItem* item;
	item = new RenderItem(shape, floor2, { 0,0,0,1 });

}

RigidBodySystem::~RigidBodySystem() {

	
}


void RigidBodySystem::addDynamicObject(float Cestatico, float Cdinamico, float Elastico, PxVec3 inertiaT, Vector3 dimension,Vector4 color, Vector3 transform, Vector3 velocity, Vector3 angularvelocity, float density, int timetoleave)
{
	RigidBody solid;
	PxRigidDynamic* new_solid;
	
	PxMaterial* gMaterial =  _gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);

	
	new_solid = _gPhysics->createRigidDynamic(PxTransform(transform));

	new_solid->setLinearVelocity(velocity);
	new_solid->setAngularVelocity(angularvelocity);

	solid.shape = CreateShape(PxBoxGeometry(dimension.x, dimension.y, dimension.z), gMaterial);
	new_solid->attachShape(*solid.shape);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, density);

	solid.item = new RenderItem(solid.shape, new_solid, color);
	_gScene->addActor(*new_solid);

	solid._rb = new_solid;
	solid.timeUntilDeath = timetoleave;

	solids.push_back(solid);
}


void RigidBodySystem::update(double t)
{
	for(auto it = generators.begin(); it != generators.end();)
	{
		if((*it)->finished())
		{
			it = generators.erase(it);
		}
		else
		{
			(*it)->update(t);
			it++;
		}

	}
	//generator->update(t);
	// 
	// 
	//std::list<RigidBodyWithTime> lista = _generator->generateSolidRigid();
	//for (auto partic : lista) {
	//	_objects.push_back(partic);
	//	_sFR->addRegistry(windForceGen, partic);

	//}
	////addDynamicObject();
	
	for (auto it = solids.begin(); it != solids.end(); )
	{
		it->timeAlive += t;
		if (it->timeAlive >= it->timeUntilDeath)
		{
			rFR->deleteSolidRegistry(*it);
			_gScene->removeActor(*(it->_rb));
			it->_rb->detachShape(*it->shape);
			it->item->release();
			it->shape->release();
			it = solids.erase(it);
		}
		else
		{
			++it;
		}
	}
	//las actualizamos
	/*for (auto it = _objects.begin(); it != _objects.end(); ) {
		it->time += t;
		if (it->time >= it->tolive) {
			_sFR->deleteParticleRegistry(*(it));
			_gScene->removeActor(*(it->body));
			(it->body)->detachShape(*(it->shape));
			(it->item)->release();
			(it->body)->release();
			it = _objects.erase(it);
		}
		else {
			++it;
		}
	}
	_sFR->updateForces(t);*/

}

void RigidBodySystem::addGenerator(Particle* p, int nParticles, float frecuency)
{
	SolidGenerator* gen = new SolidGenerator(p, nParticles, frecuency, this);
	generators.push_back(gen);
}